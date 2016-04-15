#ifndef DIALOGAD_H
#define DIALOGAD_H

#include <QDialog>
#include <QtWidgets>

#include "ui_DialogDonor.h"

#include "EnumsFunctions.h"

class KPDGUIDonorInfo;

class DialogDonor : public QDialog, public Ui_DialogDonor
{
	Q_OBJECT

public:
	DialogDonor(QWidget *parent = 0);
	DialogDonor(KPDGUIDonorInfo donor, bool disableMajorEdits, QWidget *parent = 0);

	QTextEdit * commentTextEdit;

private:
	void additionalSetup();
};

#endif