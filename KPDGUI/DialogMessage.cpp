#include "DialogMessage.h"

// Empty Message
DialogMessage::DialogMessage(QWidget * parent) : QDialog(parent)
{
	messageToPrint = "";

	setupUi(this);
}

// Set Message
DialogMessage::DialogMessage(QString message, QWidget * parent) : QDialog(parent)
{
	messageToPrint = message;

	setupUi(this);

	messageBox->setText(messageToPrint);
}

bool DialogMessage::saveMessage() {

	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Solution"), ".", tr("Text Files (*.txt)"), Q_NULLPTR, QFileDialog::DontUseNativeDialog);
	if (fileName.isEmpty()) {
		return false;
	}

	if (!fileName.endsWith(".txt")) {
		fileName.append(".txt");
	}

	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly)) {
		QMessageBox::warning(this, tr("KPD"),
			tr("Cannot write file %1:\n%2.")
			.arg(file.fileName())
			.arg(file.errorString()));
		return false;
	}

	QTextStream stream(&file);

	stream << messageToPrint;

	return true;

}