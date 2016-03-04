#ifndef KPDGUIPAIRMODELITEM_H
#define KPDGUIPAIRMODELITEM_H

#include <QList>
#include <QVariant>

class KPDGUIPairModelItem
{
public:
	KPDGUIPairModelItem(KPDGUIPairModelItem *parentItem = 0);
	~KPDGUIPairModelItem();

	void appendChild(KPDGUIPairModelItem *child);

	KPDGUIPairModelItem *child(int row);
	int childCount() const;
	int columnCount() const;
	QVariant data(int column) const;
	int row() const;
	KPDGUIPairModelItem *parentItem();
	void setParentItem(KPDGUIPairModelItem * parent);
	void setDataForItem(QString data);

private:
	QList<KPDGUIPairModelItem*> m_childItems;
	QString m_itemData;
	KPDGUIPairModelItem *m_parentItem;
};

#endif