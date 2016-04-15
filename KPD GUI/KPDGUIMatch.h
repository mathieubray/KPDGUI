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

#ifndef KPDGUIMATCH_H
#define KPDGUIMATCH_H

#include <QGraphicsLineItem>
#include <QDebug>
#include <QPen>
#include <QPainter>

#include <math.h>

#include "KPDGUINode.h"
#include "KPDGUIDisplaySettings.h"

QT_BEGIN_NAMESPACE
class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;
QT_END_NAMESPACE

class KPDGUIMatch : public QObject, public QGraphicsLineItem
{
	Q_OBJECT;

private:

	//Nodes
	KPDGUINode * myFromNode;
	KPDGUINode * myToNode;

	int associatedDonor;
	
	//Visual Arrow Properties
	QColor myColor;	
	int myWidth;
	qreal myOpacity;
	int myZValue;

	QPolygonF arrowHead;

	//Match Properties
	double matchSuccessProbability;
	double matchUtility;

	int myPopularityInStructures;
	int myPopularityInSolutions;

	bool displayAsPartOfSolution;

public:
    //enum { Type = UserType + 4 };

	KPDGUIMatch(KPDGUINode *fromNode, KPDGUINode *toNode, int donor = 1);
	~KPDGUIMatch();

	//Nodes
	KPDGUINode *getFromNode() const { return myFromNode; }
	KPDGUINode *getToNode() const { return myToNode; }

	//Visual Arrow Properties
    QRectF boundingRect() const;
    QPainterPath shape() const;
	void updatePosition();
   	//int type() const { return Type; }

	void setArrowColor(const QColor &color) { myColor = color; }
	void setArrowWidth(int width) { myWidth = width; }
	void setArrowOpacity(qreal opacity) { myOpacity = opacity; }
	void setArrowZValue(int zValue) { myZValue = zValue; }
	
	QColor color() const { return pen().color(); }
    	
	void highlightMatch(int level);
	void clearHighlight();


	//Match Properties
	int getPopularityInStructures() const { return myPopularityInStructures; }
	int getPopularityInSolutions() const { return myPopularityInSolutions; }

	void increasePopularityInStructures();
	void increasePopularityInSolutions();
	void decreasePopularityInStructures();
	void decreasePopularityInSolutions();
	void resetPopularityInStructures();
	void resetPopularityInSolutions();

	double getMatchSuccessProbability() const { return matchSuccessProbability; }
	double getMatchUtility() const { return matchUtility; }

signals:
	void selectArrowInMatchList(bool);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
	bool checkVisibility(KPDGUIDisplaySettings * displaySettings);

	void setArrowProperties(QColor color, int width, qreal opacity, int zValue);
	
public slots:
	void updateSelection(int id, bool selected);
	void updateVisibility(KPDGUIDisplaySettings * displaySettings);
	void endDisplayAsPartOfSolution();
};

#endif
