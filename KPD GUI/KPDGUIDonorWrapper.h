#ifndef KPDGUIDONORWRAPPER_H
#define KPDGUIDONORWRAPPER_H

#include <QtGui>

#include "KPDGUIDonor.h"

class KPDGUIDonorWrapper : public QTreeWidgetItem
{

public:
	KPDGUIDonorWrapper(KPDGUIDonor * donor);
	~KPDGUIDonorWrapper();

	KPDGUIDonor * getDonor();
	void updateText();

private:
	KPDGUIDonor * myDonor;

	bool operator<(const QTreeWidgetItem &other) const;

};


#endif