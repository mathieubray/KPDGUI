#ifndef DIALOGCANDIDATE_H
#define DIALOGCANDIDATE_H

#include <QtGui>
#include <QtWidgets>

#include "ui_DialogCandidate.h"

#include "KPDGUIEnumsFunctions.h"

#include "KPDGUIHLASelecter.h"

class KPDGUICandidate;


class DialogCandidate : public QDialog, public Ui_DialogCandidate
{
	Q_OBJECT

public:
	DialogCandidate(QWidget * parent = 0);
	DialogCandidate(KPDGUICandidate * candidate, QWidget *parent = 0);

	QTextEdit * commentTextEdit;

private:
	void additionalSetup();

};

#endif