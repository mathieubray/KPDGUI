#ifndef MULTISELECTCOMPLETER_H
#define MULTISELECTCOMPLETER_H

#include <QtGui>
#include <QtWidgets>

class MultiSelectCompleter : public QCompleter
{
	Q_OBJECT

public:
	MultiSelectCompleter(const QStringList& items, QObject* parent);
	~MultiSelectCompleter();

public:
	QString pathFromIndex(const QModelIndex& index) const;
	QStringList splitPath(const QString& path) const;
};

#endif

