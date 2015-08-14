#ifndef DIALOGREADFILECONFIRM_H
#define DIALOGREADFILECONFIRM_H

#include <QtGui>
#include <QDialog>
#include <QFileDialog>

#include "ui_ReadFileConfirmDialog.h"

class ReadFileConfirmDialog : public QDialog, public Ui_ReadFileConfirmDialog
{
	Q_OBJECT

public:
	ReadFileConfirmDialog(QWidget *parent = 0);
	ReadFileConfirmDialog(QVector<QVector<QVector<QString> > > rows, QWidget *parent = 0);

private slots :
	void updateTable();

private :
	QVector<QVector<QVector<QString> > > collected_rows;
};

#endif