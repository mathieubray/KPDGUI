#include "KPDGUIDashboard.h"

KPDGUIDashboard::KPDGUIDashboard(QWidget *parent) : QTabWidget(parent){
	QFont font;
	font.setPointSize(9);
	font.setFamily(QStringLiteral("Courier"));
	
	dashboard = new QTextBrowser();	
	dashboard->setFont(font);
	
	solution = new QTextBrowser();
	solution->setFont(font);
	
	solutionVisible = false;

	addTab(dashboard, "Dashboard");
}

KPDGUIDashboard::~KPDGUIDashboard(){
	delete dashboard;
	delete solution;
}

void KPDGUIDashboard::setRecord(KPDGUIRecord * record){
	kpdguiRecord = record;
}

void KPDGUIDashboard::appendDashboardText(QString text){
	dashboard->append("> " + text);
}


void KPDGUIDashboard::showSolution(QString text){
	solution->setText(text);

	insertTab(1, solution, "Solution Information");

	solutionVisible = true;
}

void KPDGUIDashboard::removeSolution(){
	if (solutionVisible){
		removeTab(1);
	}

	solutionVisible = false;
}

void KPDGUIDashboard::focusOnSolution(){
	
	if (solutionVisible){
		setCurrentIndex(1);
	}
}

