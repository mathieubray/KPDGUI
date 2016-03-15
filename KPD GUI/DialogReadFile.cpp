#include "DialogReadFile.h"

//Constructor
ReadFileDialog::ReadFileDialog(QWidget *parent) : QDialog(parent)
{
	setupUi(this);

	//Disables the OK button until a file is selected
	this->buttonBox->buttons().first()->setDisabled(true);
}

//Opens file browser
void ReadFileDialog::browse(){
	QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "CSV Files (*.csv*)");
	pairFileLineEdit->setText(fileName);

	//this->buttonBox->buttons().first()->setEnabled(true);
}

void ReadFileDialog::checkValidFile(QString file){
	if (file.endsWith(".csv")){
		this->buttonBox->buttons().first()->setEnabled(true);
	}
	else {
		this->buttonBox->buttons().first()->setEnabled(false);
	}

}


