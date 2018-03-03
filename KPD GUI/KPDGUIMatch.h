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

#include "DialogMatch.h"

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
	KPDGUIDonor * myDonor;
	KPDGUICandidate * myCandidate;
		
	//Visual Arrow Properties
	QColor myColor;	
	int myWidth;
	Qt::PenStyle myPenStyle;
	qreal myOpacity;
	int myZValue;	

	QPolygonF arrowHead;

	//Match Properties

	bool includeMatch;
	KPDCrossmatchResult matchResult;

	double matchFailureProbability;

	double matchFiveYearSurvival;
	double matchTenYearSurvival;
	double matchTransplantScore;
	double matchAssignedUtility;

	int myPopularityInArrangements;
	int myPopularityInSolutions;

	bool displayAsPartOfSolution;

public:
    enum { Type = UserType + 4 };

	KPDGUIMatch();
	KPDGUIMatch(KPDGUIDonor * donor, KPDGUICandidate * candidate, KPDCrossmatchResult result, double fiveYearSurvival, double tenYearSurvival, bool difficultToTransplant);
	~KPDGUIMatch();

	//Nodes
	KPDGUIDonor * getDonor() const { return myDonor; }
	KPDGUICandidate *getCandidate() const { return myCandidate; }

	//Visual Arrow Properties
    QRectF boundingRect() const;
    QPainterPath shape() const;
	void updatePosition();
   	int type() const { return Type; }

	QColor determineArrowColor();
	Qt::PenStyle determineArrowPenStyle();

	void setArrowColor(const QColor &color) { myColor = color; }
	void setArrowWidth(int width) { myWidth = width; }
	void setArrowPenStyle(Qt::PenStyle penStyle) { myPenStyle = penStyle; }
	void setArrowOpacity(qreal opacity) { myOpacity = opacity; }
	void setArrowZValue(int zValue) { myZValue = zValue; }
	
	QColor color() const { return pen().color(); }
    	
	void highlightMatch(int level);
	void clearHighlight();

	//Match Properties

	bool getInclude() const { return includeMatch; }
	KPDCrossmatchResult getCrossmatchResult() const { return matchResult; }

	int getPopularityInArrangements() const { return myPopularityInArrangements; }
	int getPopularityInSolutions() const { return myPopularityInSolutions; }
	
	double getFailureProbability() const { return matchFailureProbability; }

	double getFiveYearSurvival() const { return matchFiveYearSurvival; }
	double getTenYearSurvival() const { return matchTenYearSurvival; }
	double getTransplantScore() const { return matchTransplantScore; }
	double getAssignedUtility() const { return matchAssignedUtility; }
	
	void setDonorAndCandidate(KPDGUIDonor * donor, KPDGUICandidate * candidate);

	void setInclude(bool include);
	void setCrossmatchResult(KPDCrossmatchResult result);

	void increasePopularity(bool solution);
	void decreasePopularity(bool solution);
	void resetPopularity(bool solution);

	void setFailureProbability(double probability);

	void setFiveYearSurvival(double fiveYearSurvival);
	void setTenYearSurvival(double tenYearSurvival);
	void setTransplantScore(double transplantScore);
	void setAssignedUtility(double assignedUtility);

public slots:
	void updateSelection(int id, bool selected);
	void updateVisibility(KPDGUIDisplaySettings * displaySettings);
	void endDisplayAsPartOfSolution();

	void edit();
	void editMatch(DialogMatch * dialog);

	void updateCrossmatchResults(KPDCrossmatchResult result, double fiveYear, double tenYear, bool difficultToMatch);

signals:
	void matchWasEdited();
	void showAdditionalMatchInformation(KPDGUIMatch *);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
	bool checkVisibility(KPDGUIDisplaySettings * displaySettings);

	void setArrowProperties(QColor color, int width, Qt::PenStyle penStyle, qreal opacity, int zValue);

	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
	

};

QDataStream &operator<<(QDataStream &out, const KPDGUIMatch & match);

QDataStream &operator>>(QDataStream &in, KPDGUIMatch & match);

#endif
