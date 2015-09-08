#include "KPDGUIConsolePairWidget.h"

KPDGUIConsolePairWidget::KPDGUIConsolePairWidget(){
	setupUi(this);
	
	QPalette Pal(palette());
	// set black background
	Pal.setColor(QPalette::Background, QColor(240,240,240));
	setAutoFillBackground(true);
	setPalette(Pal);
	
	connect(leftButton, SIGNAL(clicked()), this, SLOT(left()));
	connect(rightButton, SIGNAL(clicked()), this, SLOT(right()));
}

KPDGUIConsolePairWidget::~KPDGUIConsolePairWidget(){
}

void KPDGUIConsolePairWidget::addWidget(QWidget * widget){
	stack->addWidget(widget);
}

void KPDGUIConsolePairWidget::removeWidget(int i){
	stack->removeWidget(stack->widget(i));
}

void KPDGUIConsolePairWidget::setCurrentIndex(int i){
	stack->setCurrentIndex(i);
}

void KPDGUIConsolePairWidget::setVisible(int i, bool selected){
	stack->widget(i)->setVisible(selected);
	if (selected){
		visibleIndices.push_back(i);
	}
	else {
		visibleIndices.remove(visibleIndices.indexOf(i));
	}
}

void KPDGUIConsolePairWidget::updateText(int i, QString text){
	
	QTextBrowser *textBrowser = dynamic_cast<QTextBrowser *>(stack->widget(i));
	if (textBrowser){
		textBrowser->setText(text);
	}
}

int KPDGUIConsolePairWidget::visibleElements(){
	return visibleIndices.size();
}

void KPDGUIConsolePairWidget::clearPairs(){
	visibleIndices.clear();
	
	for (int i = 0; i < stack->count(); i++){
		qDebug() << "Number to remove " << stack->count();
		QTextBrowser *textBrowser = dynamic_cast<QTextBrowser *>(stack->widget(0));
		if (textBrowser){
			qDebug() << textBrowser->toPlainText();
		}
		stack->removeWidget(stack->widget(0));
		qDebug() << "SUCCESS";
	}
}

void KPDGUIConsolePairWidget::left(){
	int size = visibleIndices.size();
	int iterator = visibleIndices.indexOf(stack->currentIndex());
	
	if (iterator - 1 < 0){
		iterator = size - 1;
	}
	else {
		iterator--;
	}

	stack->setCurrentIndex(visibleIndices[iterator]);

	/*int newIndex;
	if (currentIndex - 1 < 0){
		//stack->setCurrentIndex(size - 1);
		newIndex = size - 1;
	}
	else {
		//stack->setCurrentIndex(currentIndex - 1);
		newIndex = currentIndex - 1;
	}

	while (!stack->widget(newIndex)->isVisible()){
		currentIndex = newIndex;
		if (currentIndex - 1 < 0){
			newIndex = size - 1;
		}
		else {
			newIndex = currentIndex - 1;
		}
	}

	stack->setCurrentIndex(newIndex);*/
}

void KPDGUIConsolePairWidget::right(){
	int size = visibleIndices.size();
	int iterator = visibleIndices.indexOf(stack->currentIndex());

	if (iterator + 1 == size){
		iterator = 0;
	}
	else {
		iterator++;
	}

	stack->setCurrentIndex(visibleIndices[iterator]);

	/*int size = stack->count();
	int currentIndex = stack->currentIndex();
	
	int newIndex;
	if (currentIndex + 1 == size){
		//stack->setCurrentIndex(size - 1);
		newIndex = 0;
	}
	else {
		//stack->setCurrentIndex(currentIndex - 1);
		newIndex = currentIndex + 1;
	}

	while (!stack->widget(newIndex)->isVisible()){
		currentIndex = newIndex;
		if (currentIndex + 1 == size){
			newIndex = size - 1;
		}
		else {
			newIndex = currentIndex - 1;
		}
	}

	stack->setCurrentIndex(newIndex);
	//if (currentIndex + 1 == size){
	//	stack->setCurrentIndex(0);
	//}
	//else {
	//	stack->setCurrentIndex(currentIndex + 1);
	}*/
}