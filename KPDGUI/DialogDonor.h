#ifndef DIALOGDONOR_H
#define DIALOGDONOR_H

#include <QtGui>
#include <QtWidgets>

#include "ui_DialogDonor.h"

#include "KPDGUIHLASelecter.h"

#include "KPDGUIEnumsFunctions.h"

class KPDGUIDonor;

class DialogDonor : public QDialog, public Ui_DialogDonor
{
	Q_OBJECT

public:
	DialogDonor(bool showAdditionalDonorButton = false, QWidget * parent = 0);
	DialogDonor(KPDGUIDonor * donor, bool showAdditionalDonorButton = false, QWidget *parent = 0);

	QTextEdit * commentTextEdit;

	bool getAdditionalDonor();

public slots:
	void setAdditionalDonor();

	void setDefaultHeightWeight(int index);

private:
	void additionalSetup();

	bool additionalDonor;
};

#endif