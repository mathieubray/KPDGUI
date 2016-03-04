#ifndef DIALOGCANDIDATE_H
#define DIALOGCANDIDATE_H

#include <QDialog>
#include <QtWidgets>

#include "ui_DialogCandidate.h"

#include "EnumsFunctions.h"


class Candidate;

class DialogCandidate : public QDialog, public Ui_DialogCandidate
{
	Q_OBJECT

public:
	DialogCandidate(QWidget *parent = 0);
	DialogCandidate(Candidate candidate, bool disableMajorEdits, QWidget *parent = 0);

	QTextEdit * commentTextEdit;

private:
	void additionalSetup();

};

#endif