#include "KPDGUIConsole.h"

KPDGUIConsole::KPDGUIConsole(QWidget *parent) : QTabWidget(parent){
	QFont font;
	font.setPointSize(9);
	font.setFamily(QStringLiteral("Courier"));
	
	consoleScreen = new QTextBrowser();	
	consoleScreen->setFont(font);
	pairInfo = new KPDGUIConsolePairWidget();
	solutionInfo = new QTextBrowser();
	solutionInfo->setFont(font);
	matchInfo = new QTextBrowser();
	matchInfo->setFont(font);

	pairScreenVisible = false;
	matchScreenVisible = false;
	solutionScreenVisible = false;

	addTab(consoleScreen, "Console");
}

KPDGUIConsole::~KPDGUIConsole(){
	delete consoleScreen;
	delete pairInfo;
	delete matchInfo;
	delete solutionInfo;
}

void KPDGUIConsole::setRecord(KPDGUIRecord * record){
	kpdguiRecord = record;
}

void KPDGUIConsole::addConsoleInfo(QString text){
	consoleScreen->append(text);
}

void KPDGUIConsole::addPairInfo(int id){

	QTextBrowser * newTextBrowser = new QTextBrowser();
	QFont font;
	font.setPointSize(9);
	font.setFamily(QStringLiteral("Courier"));
	newTextBrowser->setFont(font);
	
	ids.push_back(id);
	pairInfo->addWidget(newTextBrowser);
}

void KPDGUIConsole::deletePairInfo(int id){
	
	int index = ids.indexOf(id);
	pairInfo->removeWidget(index);
	////qDebug() << id << "," << index;
	ids.remove(index);
}

void KPDGUIConsole::addMatchInfo(QString text){
	matchInfo->setText(text);

	if (!matchScreenVisible){
		if (!pairScreenVisible){
			insertTab(1, matchInfo, "Match Information");
		}
		else {
			insertTab(2, matchInfo, "Match Information");
		}
	}

	matchScreenVisible = true;
}

void KPDGUIConsole::addSolutionInfo(QString text){
	solutionInfo->setText(text);

	if (!solutionScreenVisible){
		if (!matchScreenVisible){
			if (!pairScreenVisible){
				insertTab(1, solutionInfo, "Solution Information");
			}
			else {
				insertTab(2, solutionInfo, "Solution Information");
			}
		}
		else {
			if (!pairScreenVisible){
				insertTab(2, solutionInfo, "Solution Information");
			}
			else {
				insertTab(3, solutionInfo, "Solution Information");
			}
		}
	}

	solutionScreenVisible = true;
}

void KPDGUIConsole::removePairScreen(){
	if (pairScreenVisible){
		removeTab(1);
	}

	pairScreenVisible = false;
}

void KPDGUIConsole::removeMatchScreen(){
	if (pairScreenVisible){
		if (matchScreenVisible){
			removeTab(2);
		}
	}
	else {
		if (matchScreenVisible){
			removeTab(1);
		}
	}

	matchScreenVisible = false;

}

void KPDGUIConsole::removeSolutionScreen(){
	if (pairScreenVisible){
		if (matchScreenVisible){
			if (solutionScreenVisible){
				removeTab(3);
			}
		}
		else {
			if (solutionScreenVisible){
				removeTab(2);
			}
		}
	}
	else {
		if (matchScreenVisible){
			if (solutionScreenVisible){
				removeTab(2);
			}
		}
		else {
			if (solutionScreenVisible){
				removeTab(1);
			}
		}
	}

	solutionScreenVisible = false;
}

void KPDGUIConsole::focusOnPairScreen(int id){
	if (pairScreenVisible){
		setCurrentIndex(1);

		int i = ids.indexOf(id);
		if (i != -1){
			pairInfo->setCurrentIndex(i);
		}
	}
}

void KPDGUIConsole::focusOnMatchScreen(){
	if (matchScreenVisible){
		if (pairScreenVisible){
			setCurrentIndex(2);
		}
		else {
			setCurrentIndex(1);
		}
	}
}

void KPDGUIConsole::focusOnSolutionScreen(){
	if (solutionScreenVisible){
		if (matchScreenVisible){
			if (pairScreenVisible){
				setCurrentIndex(3);
			}
			else {
				setCurrentIndex(2);
			}
		}
		else {
			if (pairScreenVisible){
				setCurrentIndex(2);
			}
			else {
				setCurrentIndex(1);
			}
		}
	}
}

void KPDGUIConsole::removeAllPairInfo(){
	pairInfo->clearPairs();

	qDebug() << "A";
	qDebug() << ids.size();

	ids.clear();
}

void KPDGUIConsole::changePairInfo(int id, bool selected){

	KPDGUINode * node = kpdguiRecord->getNode(id);
	int index = ids.indexOf(id);
	pairInfo->updateText(index, node->getConsoleString());
	pairInfo->setVisible(index, selected);	

	if (selected){
		pairInfo->setCurrentIndex(index);
		if (!pairScreenVisible){
			insertTab(1, pairInfo, "Pair Information");
			pairScreenVisible = true;
		}
	}

	if (!selected){
		if (pairInfo->visibleElements() == 0){
			removePairScreen();
		}
	}	
}

void KPDGUIConsole::changePairText(int id){
	KPDGUINode * node = kpdguiRecord->getNode(id);
	int index = ids.indexOf(id);
	pairInfo->updateText(index, node->getConsoleString());
}
