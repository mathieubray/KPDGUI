#ifndef DIALOGAD_H
#define DIALOGAD_H

#include <QDialog>

#include "Structs.h"
#include "MultiSelectCompleter.h"
#include "ui_AltruisticDonorDialog.h"

class AltruisticDonorDialog : public QDialog, public Ui_AltruisticDonorDialog
{
	Q_OBJECT

public:
	AltruisticDonorDialog(QWidget *parent = 0);
	AltruisticDonorDialog(int id, Donor *donor, QString comment, bool disableMajorEdits, QWidget *parent = 0);

	void additionalSetup();
};

#endif