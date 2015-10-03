/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef KPDGUIARROW_H
#define KPDGUIARROW_H

#include <QGraphicsLineItem>
#include <QDebug>
#include <QPen>
#include <QPainter>

#include <math.h>

#include "KPDGUINode.h"
//#include "Structs.h"

QT_BEGIN_NAMESPACE
class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;
QT_END_NAMESPACE

class KPDGUIArrow : public QObject, public QGraphicsLineItem
{
	Q_OBJECT;

public:
    enum { Type = UserType + 4 };

	KPDGUIArrow(KPDGUINode *startItem, KPDGUINode *endItem);
	~KPDGUIArrow();

	//Nodes
	KPDGUINode *startItem() const { return myStartItem; }
	KPDGUINode *endItem() const { return myEndItem; }

	//Visual Arrow Properties
    QRectF boundingRect() const;
    QPainterPath shape() const;
	void updatePosition();
   	int type() const { return Type; }
	void setColor(const QColor &color) { myColor = color; }
	void setWidth(int width) { myWidth = width; }
	QColor color() const { return pen().color(); }
    
	//QTreeWidgetItem * getListItem();
	//QTreeWidgetItem * getListItemCopy();
	
	//Highlights
	void clearHighlight();
	void highlightConnection();
	void highlightCycle();

	//Popularity
	int getPopularityInStructures() const { return myPopularityInStructures; }
	int getPopularityInSolutions() const { return myPopularityInSolutions; }

	void increasePopularityInStructures();
	void increasePopularityInSolutions();
	void decreasePopularityInStructures();
	void decreasePopularityInSolutions();

	void resetPopularityInStructures();
	void resetPopularityInSolutions();

signals:
	void selectArrowInMatchList(bool);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:

	//Helper Functions
	bool checkVisibility(DisplaySettingsStruct * displaySettings);

	//Nodes
    KPDGUINode *myStartItem;
    KPDGUINode *myEndItem;
	
	//QTreeWidgetItem * arrowListItem;
    
	//Visual Arrow Properties
	QColor myColor;
	QPolygonF arrowHead;
	int myWidth;

	//Popularity Properties
	int myPopularityInStructures;
	int myPopularityInSolutions;

	bool displayAsPartOfSolution;

public slots:
	void changeArrowSelection(int id, bool selected);
	void updateVisibility(DisplaySettingsStruct * displaySettings);
	void endDisplayAsPartOfSolution();
};

#endif
