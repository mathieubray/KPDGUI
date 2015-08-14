#include "DialogReadFileConfirm.h"

//Constructor
ReadFileConfirmDialog::ReadFileConfirmDialog(QWidget *parent) : QDialog(parent)
{
	setupUi(this);
}

ReadFileConfirmDialog::ReadFileConfirmDialog(QVector<QVector<QVector<QString> > > rows, QWidget *parent = 0) : QDialog(parent)
{
	tableWidget->insertColumn(0);
	collected_rows = rows;
	foreach(QVector<QVector<QString> > row, rows){
		QVector<QString> val = row.at(0);
		QString label = "";
		foreach(QString token, val){
			label.append(token);
			label.append("");
		}
		tableWidget->insert
	}
}

//Opens file browser
void ReadFileConfirmDialog::updateTable(){
	
}


