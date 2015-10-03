#ifndef DIALOGREADFILE_H
#define DIALOGREADFILE_H

#include <QtGui>
#include <QDialog>
#include <QFileDialog>

#include "ui_ReadFileDialog.h"

class ReadFileDialog : public QDialog, public Ui_ReadFileDialog 
{
	Q_OBJECT

public:
	ReadFileDialog(QWidget *parent = 0);

private slots :
	void browse();
	void checkValidFile(QString file);

};

#endif