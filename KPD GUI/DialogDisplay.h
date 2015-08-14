#ifndef DIALOGDISPLAY_H
#define DIALOGDISPLAY_H

#include <QDialog>

#include "Structs.h"
#include "ui_DisplayDialog.h"

class DisplayDialog : public QDialog, public Ui_DisplayDialog
{
	Q_OBJECT

public:
	DisplayDialog(QWidget *parent = 0);
	DisplayDialog(DisplaySettingsStruct * displaySettings, QWidget *parent = 0);
};

#endif