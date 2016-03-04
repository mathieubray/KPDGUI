#ifndef DIALOGSIMPARAM_H
#define DIALOGSIMPARAM_H

#include <QDialog>

#include "ui_DialogSimParameters.h"


class KPDGUISimParameters;

class DialogSimParameters : public QDialog, public Ui_DialogSimParameters
{
	Q_OBJECT

public:
	DialogSimParameters(QWidget *parent = 0);
	DialogSimParameters(KPDGUISimParameters *paramInfo, QWidget *parent = 0);

public slots:
	void enablePRAOptions(bool enabled);
	void enableBridgeDonorOptions(bool enabled);
	
	void changeLabel(int index);

};

#endif