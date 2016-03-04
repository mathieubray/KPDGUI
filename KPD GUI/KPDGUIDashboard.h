#ifndef KPDGUIDASHBOARD_H
#define KPDGUIDASHBOARD_H

#include <QtGui>
#include <QtWidgets>

#include "KPDGUIRecord.h"


class KPDGUIDashboard : public QTabWidget
{
	Q_OBJECT

public:
	KPDGUIDashboard(QWidget *parent = 0);
	~KPDGUIDashboard();

	void setRecord(KPDGUIRecord * record);

	void appendDashboardText(QString text);
	
	void showSolution(QString text);
	void removeSolution();

	void focusOnSolution();

public slots:
	//void changePairInfo(int id, bool selected);
	//void changePairText(int id);

private:
	KPDGUIRecord * kpdguiRecord;

	QTextBrowser * dashboard;
	QTextBrowser * solution;

	bool solutionVisible;
};

#endif