#ifndef KPDGUIHLASELECTER_H
#define KPDGUIHLASELECTER_H

#include <QtGui>
#include <QtWidgets>

class KPDGUIHLASelecter : public QCompleter
{
	Q_OBJECT

public:
	KPDGUIHLASelecter(const QStringList &hlaList, QObject * parent);
	~KPDGUIHLASelecter();

	QString pathFromIndex(const QModelIndex &index) const;
	QStringList splitPath(const QString &path) const;
};

#endif

