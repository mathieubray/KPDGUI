#include "KPDGUICommandHistory.h"

KPDGUICommandHistory::KPDGUICommandHistory(QWidget *parent) : QTextBrowser(parent){

	// Set Font
	QFont font;
	font.setPointSize(9);
	font.setFamily(QStringLiteral("Courier"));	
	setFont(font);
}

KPDGUICommandHistory::~KPDGUICommandHistory(){

}

void KPDGUICommandHistory::appendCommand(QString text){

	// Format Command
	append("> " + text);
}



