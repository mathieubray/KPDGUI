#include "DialogMessage.h"

// Empty Message
DialogMessage::DialogMessage(QWidget * parent) : QDialog(parent)
{
	setupUi(this);
}

// Set Message
DialogMessage::DialogMessage(QString message, QWidget * parent) : QDialog(parent)
{
	setupUi(this);

	messageBox->setText(message);
}
