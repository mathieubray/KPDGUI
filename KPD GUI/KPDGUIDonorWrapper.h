#ifndef KPDGUIDONORWRAPPER_H
#define KPDGUIDONORWRAPPER_H

#include <QtGui>

#include "KPDGUIDonor.h"

class KPDGUIDonorWrapper : public QObject, public QTreeWidgetItem
{
	Q_OBJECT;

public:
	KPDGUIDonorWrapper(KPDGUIDonor * donor);
	~KPDGUIDonorWrapper();

	KPDGUIDonor * getDonor();

public slots:
	void updateText();
	
	void donorWrapperDoubleClickActions(QTreeWidgetItem * item);

private:
	KPDGUIDonor * myDonor;

	bool operator<(const QTreeWidgetItem &other) const;

};


#endif