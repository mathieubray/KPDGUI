#include <QStringList>

#include "KPDGUIPairModelItem.h"

KPDGUIPairModelItem::KPDGUIPairModelItem(KPDGUIPairModelItem *parent)
{
	m_parentItem = parent;
	m_itemData = "";
	//m_itemData = data;
}

KPDGUIPairModelItem::~KPDGUIPairModelItem()
{
	qDeleteAll(m_childItems);
}

void KPDGUIPairModelItem::appendChild(KPDGUIPairModelItem *item)
{
	m_childItems.append(item);
}

KPDGUIPairModelItem *KPDGUIPairModelItem::child(int row)
{
	return m_childItems.value(row);
}

int KPDGUIPairModelItem::childCount() const
{
	return m_childItems.count();
}

int KPDGUIPairModelItem::columnCount() const
{
	return m_itemData.count();
}

QVariant KPDGUIPairModelItem::data(int column) const
{
	return m_itemData;
}

KPDGUIPairModelItem * KPDGUIPairModelItem::parentItem()
{
	return m_parentItem;
}

void KPDGUIPairModelItem::setParentItem(KPDGUIPairModelItem * parent)
{
	m_parentItem = parent;
}

void KPDGUIPairModelItem::setDataForItem(QString data)
{
	m_itemData = data;
}

int KPDGUIPairModelItem::row() const
{
	if (m_parentItem)
		return m_parentItem->m_childItems.indexOf(const_cast<KPDGUIPairModelItem*>(this));

	return 0;
}