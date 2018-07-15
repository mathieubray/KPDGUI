#ifndef KPDGUIDONORWRAPPER_H
#define KPDGUIDONORWRAPPER_H

#include <QtGui>

#include "KPDGUIDonor.h"
#include "KPDGUINode.h"

class KPDGUIDonorWrapper : public QObject, public QTreeWidgetItem
{
	Q_OBJECT;

public:
	KPDGUIDonorWrapper(KPDGUIDonor * donor);
	~KPDGUIDonorWrapper();

	KPDGUIDonor * getDonor();

signals:
	void updateVisibilitySignal();

public slots:
	void updateText();
	
	void donorWrapperClickActions(QTreeWidgetItem * item);
	void donorWrapperDoubleClickActions(QTreeWidgetItem * item);

private:
	KPDGUIDonor * myDonor;

	bool operator<(const QTreeWidgetItem &other) const;

};


#endif