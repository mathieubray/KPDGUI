#ifndef DIALOGMESSAGE_H
#define DIALOGMESSAGE_H

#include <QtGui>
#include <QtWidgets>

#include "ui_DialogMessage.h"

class DialogMessage : public QDialog, public Ui_DialogMessage
{
	Q_OBJECT

public:
	DialogMessage(QWidget * parent = 0);
	DialogMessage(QString message, QWidget * parent = 0);
	
};

#endif