#ifndef DIALOGMATCH_H
#define DIALOGMATCH_H

#include <QtGui>
#include <QtWidgets>

#include "ui_DialogMatch.h"

#include "KPDGUIEnumsFunctions.h"

class KPDGUIMatch;

class DialogMatch : public QDialog, public Ui_DialogMatch
{
	Q_OBJECT

public:
	DialogMatch(QWidget * parent = 0);
	DialogMatch(KPDGUIMatch * match, QWidget *parent = 0);

};

#endif