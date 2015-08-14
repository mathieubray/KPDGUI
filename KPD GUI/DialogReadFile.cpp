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
	this->buttonBox->buttons().first()->setEnabled(true);
}

//Changes selection status once a file and data layout are chosen
/*void ReadFileDialog::changeSelectionStatus(int index){
	if (index == 0){
		//Disables OK button if no data layout is chosen
		this->buttonBox->buttons().first()->setDisabled(true);
	}
	else {
		//Enables OK button if a data layout is chosen
		this->buttonBox->buttons().first()->setDisabled(false);
	}
}*/


