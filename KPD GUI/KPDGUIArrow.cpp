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

#include "KPDGUIArrow.h"

const qreal Pi = 3.14;

KPDGUIArrow::KPDGUIArrow(KPDGUINode *startItem, KPDGUINode *endItem)
{
	//Add Arrow to Nodes
    myStartItem = startItem;
    myEndItem = endItem;
	myStartItem->addOutArrow(this);
	myEndItem->addInArrow(this);

	connect(myStartItem, SIGNAL(nodeSelectionChanged(int, bool)), this, SLOT(changeArrowSelection(int, bool)));
	connect(myEndItem, SIGNAL(nodeSelectionChanged(int, bool)), this, SLOT(changeArrowSelection(int, bool)));
	
	//Arrow Defaults
	setZValue(-1);
	myColor = Qt::black;
	myWidth = 1;
	setOpacity(1);
    setPen(QPen(myColor, myWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

	//Reset Popularity
	myPopularityInStructures = 0;
	myPopularityInSolutions = 0;

	displayAsPartOfSolution = false;
}

KPDGUIArrow::~KPDGUIArrow()
{
    myStartItem->removeOutArrow(this);
    myEndItem->removeInArrow(this);
}

QRectF KPDGUIArrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath KPDGUIArrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

void KPDGUIArrow::updatePosition()
{
    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    setLine(line);
}

void KPDGUIArrow::clearHighlight(){
	if (!displayAsPartOfSolution){
		setColor(Qt::black);
		setWidth(1);
		setOpacity(0.25);
		setZValue(-1);
	}
}

void KPDGUIArrow::highlightConnection(){
	if (!displayAsPartOfSolution){
		qreal z = myStartItem->zValue();
		setColor(Qt::black);
		setWidth(2);
		setOpacity(1);
		setZValue(z - 1);
	}
}

void KPDGUIArrow::highlightCycle(){
	qreal z = myStartItem->zValue();
	setVisible(false);
	setColor(Qt::magenta);
	setWidth(4);
	setOpacity(1);
	setZValue(z-1);
	setVisible(true);

	displayAsPartOfSolution = true;
}

void KPDGUIArrow::increasePopularityInStructures(){
	myPopularityInStructures++;
}

void KPDGUIArrow::increasePopularityInSolutions(){
	myPopularityInSolutions++;
}

void KPDGUIArrow::decreasePopularityInStructures(){
	myPopularityInStructures--;
}

void KPDGUIArrow::decreasePopularityInSolutions(){
	myPopularityInSolutions--;
}

void KPDGUIArrow::resetPopularityInStructures(){
	myPopularityInStructures = 0;
}

void KPDGUIArrow::resetPopularityInSolutions(){
	myPopularityInSolutions = 0;
}

void KPDGUIArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	if (myStartItem->collidesWithItem(myEndItem))
		return;

	QPen myPen = pen();
	myPen.setColor(myColor);
	myPen.setWidth(myWidth);
	qreal arrowSize = 6;
	painter->setPen(myPen);
	painter->setBrush(myColor);

	QLineF centerLine(myStartItem->pos(), myEndItem->pos());
	QPolygonF endPolygon = myEndItem->boundingRect();
	QPointF p1 = endPolygon.first() + myEndItem->pos();
	QPointF p2;
	QPointF intersectPoint;
	QLineF polyLine;
	for (int i = 1; i < endPolygon.count(); ++i) {
		p2 = endPolygon.at(i) + myEndItem->pos();
		polyLine = QLineF(p1, p2);
		QLineF::IntersectType intersectType = polyLine.intersect(centerLine, &intersectPoint);
		if (intersectType == QLineF::BoundedIntersection)
			break;
		p1 = p2;
	}

	setLine(QLineF(intersectPoint, myStartItem->pos()));

	double angle = ::acos(line().dx() / line().length());
	if (line().dy() >= 0)
		angle = (Pi * 2) - angle;

	QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize, cos(angle + Pi / 3) * arrowSize);
	QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize, cos(angle + Pi - Pi / 3) * arrowSize);

	arrowHead.clear();
	arrowHead << line().p1() << arrowP1 << arrowP2;

	painter->drawLine(line());
	painter->drawPolygon(arrowHead);
	if (isSelected()) {
		painter->setPen(QPen(myColor, myWidth, Qt::DashLine));
		QLineF myLine = line();
		myLine.translate(0, 4.0);
		painter->drawLine(myLine);
		myLine.translate(0, -8.0);
		painter->drawLine(myLine);
	}
}

bool KPDGUIArrow::checkVisibility(DisplaySettingsStruct * displaySettings){
	
	if (displaySettings->showPairSubset){
		if (!displaySettings->showPairsOnHold && (myStartItem->isOnHold() || myEndItem->isOnHold())){
			return false;
		}
		if (displaySettings->showPairsOfMinPRA && (myEndItem->getRecipPRA() < displaySettings->minPRA || myStartItem->getRecipPRA() < displaySettings->minPRA)){
			return false;
		}
		if (displaySettings->showPairsOfMaxPRA && (myEndItem->getRecipPRA() > displaySettings->maxPRA || myStartItem->getRecipPRA() > displaySettings->maxPRA)){
			return false;
		}
	}
	
	else if (displaySettings->showPairsInSolutions){
		if (myEndItem->getPopularityInSolutions() == 0 || myStartItem->getPopularityInSolutions() == 0){
			return false;
		}
	}

	else if (displaySettings->showPairsInStructures){
		if (myEndItem->getPopularityInStructures() == 0 || myStartItem->getPopularityInSolutions() == 0){
			return false;
		}
	}

	return true;
}

void KPDGUIArrow::changeArrowSelection(int id, bool selected){	
	if ((startItem()->isSelected() && endItem()->getInternalID()==id) || (endItem()->isSelected() && startItem()->getInternalID()==id)){		
		emit selectArrowInMatchList(selected);
	}
}

void KPDGUIArrow::updateVisibility(DisplaySettingsStruct * displaySettings){

	if (!displayAsPartOfSolution){
		setVisible(false);
		clearHighlight();

		if (myStartItem->isSelected() && myEndItem->isSelected()){
			highlightConnection();
		}

		if (displaySettings->arrowDisplayMode == ALL_COMPATIBILITIES){
			setVisible(checkVisibility(displaySettings));
			//qDebug() << "Visibility updated :" << myStartItem->getInternalID() << "->" << myEndItem->getInternalID();
		}
		else if (displaySettings->arrowDisplayMode == SELECTED_COMPATIBILITIES){
			if (myStartItem->isSelected()){
				setVisible(checkVisibility(displaySettings));
			}
			else if (myEndItem->isSelected()){
				setVisible(checkVisibility(displaySettings));
			}
		}
		else if (displaySettings->arrowDisplayMode == COMPATIBLE_DONORS){
			if (myEndItem->isSelected()){
				setVisible(checkVisibility(displaySettings));
			}
		}
		else if (displaySettings->arrowDisplayMode == COMPATIBLE_RECIPIENTS){
			if (myStartItem->isSelected()){
				setVisible(checkVisibility(displaySettings));
			}
		}
		else if (displaySettings->arrowDisplayMode == WITHIN_SELECTION){
			if (myStartItem->isSelected() && myEndItem->isSelected()){
				setVisible(checkVisibility(displaySettings));
			}
		}
	}	
}

void KPDGUIArrow::endDisplayAsPartOfSolution(){
	displayAsPartOfSolution = false;
}

