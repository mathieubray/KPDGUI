
#include "DialogReadFile.h"

//Constructor
ReadFileDialog::ReadFileDialog(bool apd, QWidget *parent) : QDialog(parent)
{
	setupUi(this);

	loadAPD = apd;

	if (apd) {

		setWindowTitle("Load APD Pool");

		loadLabel->setText("Folder");

	}

	//Disables the OK button until a file is selected
	this->buttonBox->buttons().first()->setDisabled(true);
}

//Opens file browser
void ReadFileDialog::browse(){
	
	if (loadAPD) {
		QString folderName = QFileDialog::getExistingDirectory(this, "Open Folder", "", QFileDialog::ShowDirsOnly);
		loadLineEdit->setText(folderName);
	}
	else {
		QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "CSV Files (*.csv*)");
		loadLineEdit->setText(fileName);
	}
}

//Check whether file exists and is a 'csv', or whether folder exists with requisite files inside
void ReadFileDialog::checkValid(QString path){
	QFileInfo info(path);

	if (loadAPD) {
		if (info.isDir() &&
			validAPDFilePath(path, "Comp_APD.csv") &&
			validAPDFilePath(path, "Info_APD.csv") && 
			validAPDFilePath(path, "NDD_APD.csv") && 
			validAPDFilePath(path, "SamePat_APD.csv") && 
			validAPDFilePath(path, "Weight_APD.csv")) {

			this->buttonBox->buttons().first()->setEnabled(true);
		}
		else {
			this->buttonBox->buttons().first()->setEnabled(false);
		}

	}
	else {
		if (info.isFile() && path.endsWith(".csv")) {
			this->buttonBox->buttons().first()->setEnabled(true);
		}
		else {
			this->buttonBox->buttons().first()->setEnabled(false);
		}
	}

}


bool ReadFileDialog::validAPDFilePath(QString path, QString file) {

	QFileInfo info(path + "/" + file);

	return info.isFile();

}


