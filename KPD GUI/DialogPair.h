#ifndef DIALOGPAIR_H
#define DIALOGPAIR_H

#include <QDialog>

#include "Structs.h"
#include "MultiSelectCompleter.h"
#include "ui_PairDialog.h"

class PairDialog : public QDialog, public Ui_PairDialog
{
	Q_OBJECT

public:
	PairDialog(QWidget *parent = 0);
	PairDialog(int id, Donor *donor, Candidate *candidate, QString comment, bool disableMajorEdits, QWidget *parent = 0);

	void additionalSetup();
};

#endif