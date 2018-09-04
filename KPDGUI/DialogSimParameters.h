#ifndef DIALOGSIMPARAM_H
#define DIALOGSIMPARAM_H

#include <QtGui>
#include <QtWidgets>

#include "ui_DialogSimParameters.h"


class KPDGUIParameters;

class DialogSimParameters : public QDialog, public Ui_DialogSimParameters
{
	Q_OBJECT

public:
	DialogSimParameters(QWidget *parent = 0);
	DialogSimParameters(KPDGUIParameters *paramInfo, QWidget *parent = 0);

public slots:

	void browse();

	void enableOptimizationOptions(int index);
	void enablePRAOptions(bool enabled);
	void enableBridgeDonorOptions(bool enabled);
	void enableEstimateEUOptions(bool enabled);

};

#endif