#ifndef DIALOGMATCH_H
#define DIALOGMATCH_H

#include <QDialog>
#include <QtWidgets>

#include "ui_DialogMatch.h"

#include "EnumsFunctions.h"

class KPDGUIMatch;


class DialogMatch : public QDialog, public Ui_DialogMatch
{
	Q_OBJECT

public:
	DialogMatch(QWidget * parent = 0);
	DialogMatch(KPDGUIMatch * candidate, bool disableMajorEdits, QWidget *parent = 0);

private:
	void additionalSetup();

};

#endif
