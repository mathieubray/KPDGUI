#ifndef DIALOGREADFILE_H
#define DIALOGREADFILE_H

#include <QtGui>
#include <QtWidgets>

#include "ui_DialogReadFile.h"


class ReadFileDialog : public QDialog, public Ui_DialogReadFile 
{
	Q_OBJECT

public:
	ReadFileDialog(bool apd, QWidget *parent = 0);

private slots :
	void browse();
	void checkValid(QString path);

private :
	bool loadAPD;

	bool validAPDFilePath(QString path, QString file);

};

#endif