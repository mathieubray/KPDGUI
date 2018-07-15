#ifndef DIALOGDISPLAY_H
#define DIALOGDISPLAY_H

#include <QtGui>
#include <QtWidgets>

#include "ui_DialogDisplaySettings.h"

class KPDGUIDisplaySettings;

class DialogDisplaySettings : public QDialog, public Ui_DialogDisplaySettings
{
	Q_OBJECT

public:
	DialogDisplaySettings(QWidget *parent = 0);
	DialogDisplaySettings(KPDGUIDisplaySettings *displaySettings, QWidget *parent = 0);

};

#endif