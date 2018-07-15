#ifndef KPDGUICOMMANDHISTORY_H
#define KPDGUICOMMANDHISTORY_H

#include<QtGui>
#include<QtWidgets>

class KPDGUICommandHistory : public QTextBrowser
{
	Q_OBJECT

public:
	KPDGUICommandHistory(QWidget *parent = 0);
	~KPDGUICommandHistory();
	
	void appendCommand(QString text);

private:

};

#endif