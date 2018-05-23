#ifndef DIALOGPROGRESS_H
#define DIALOGPROGRESS_H

#include <QDialog>

#include "ui_ProgressDialog.h"

class ProgressDialog : public QDialog, public Ui_ProgressDialog
{
	Q_OBJECT

public:
	ProgressDialog(QWidget *parent = 0);

	void setText(QString text);
	void setValue(int value);
};

#endif