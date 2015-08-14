#ifndef KPDGUICONSOLE_H
#define KPDGUICONSOLE_H

#include <QtGui>
#include <QtWidgets>

#include "KPDGUIRecord.h"
#include "KPDGUIConsolePairWidget.h"

class KPDGUIConsole : public QTabWidget
{
	Q_OBJECT

public:
	KPDGUIConsole(QWidget *parent = 0);
	~KPDGUIConsole();

	void setRecord(KPDGUIRecord * record);

	void addConsoleInfo(QString text);
	void addPairInfo(int id);
	void deletePairInfo(int id);
	void addMatchInfo(QString text);
	void addSolutionInfo(QString text);

	void removePairScreen();
	void removeMatchScreen();
	void removeSolutionScreen();

	void focusOnPairScreen(int id);
	void focusOnMatchScreen();
	void focusOnSolutionScreen();

	void removeAllPairInfo();

public slots:
	void changePairInfo(int id, bool selected);
	void changePairText(int id);

private:
	KPDGUIRecord * kpdguiRecord;

	QTextBrowser * consoleScreen;
	KPDGUIConsolePairWidget * pairInfo;
	QTextBrowser * matchInfo;
	QTextBrowser * solutionInfo;

	QVector<int> ids;

	bool pairScreenVisible;
	bool matchScreenVisible;
	bool solutionScreenVisible;
};

#endif