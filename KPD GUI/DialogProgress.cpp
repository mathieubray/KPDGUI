#include <QtGui>

#include "DialogProgress.h"

//Basic Sort Options Dialog
ProgressDialog::ProgressDialog(QWidget *parent) : QDialog(parent)
{
	setupUi(this);
}

void ProgressDialog::setText(QString text){
	label->setText(text);
}

void ProgressDialog::setValue(int value){
	progressBar->setValue(value);
}