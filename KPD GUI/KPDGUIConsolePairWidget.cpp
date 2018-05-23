#include "KPDGUIConsolePairWidget.h"

KPDGUIConsolePairWidget::KPDGUIConsolePairWidget(){
	setupUi(this);
	
	QPalette Pal(palette());
	// set black background
	Pal.setColor(QPalette::Background, QColor(240,240,240));
	setAutoFillBackground(true);
	setPalette(Pal);
	
	//connect(leftButton, SIGNAL(clicked()), this, SLOT(left()));
	//connect(rightButton, SIGNAL(clicked()), this, SLOT(right()));
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

}