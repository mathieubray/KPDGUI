#ifndef KPDGUICONSOLEPAIRWIDGET_H
#define KPDGUICONSOLEPAIRWIDGET_H

#include <QtGui>
#include <QtWidgets>

#include "ui_ConsolePairWidget.h"

class KPDGUIConsolePairWidget : public QWidget, public Ui_KPDGUIConsolePairWidget
{
	Q_OBJECT

	public:
		KPDGUIConsolePairWidget();
		~KPDGUIConsolePairWidget();

		void addWidget(QWidget * widget);
		void removeWidget(int id);
		void setCurrentIndex(int i);
		void setVisible(int i, bool selected);
		void updateText(int i, QString text);
		int visibleElements();

		void clearPairs();

	public slots:
		void left();
		void right();

	private:
		QVector<int> visibleIndices;
};

#endif