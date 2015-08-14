#ifndef DIALOGSIMPARAM_H
#define DIALOGSIMPARAM_H

#include <QDialog>

#include "Structs.h"
#include "ui_SimParamDialog.h"

class SimParamDialog : public QDialog, public Ui_SimParamDialog
{
	Q_OBJECT

public:
	SimParamDialog(QWidget *parent = 0);
	SimParamDialog(ParamInfoStruct paramInfo, QWidget *parent = 0);
};

#endif