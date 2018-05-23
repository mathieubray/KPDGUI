#ifndef DIALOGSORT_H
#define DIALOGSORT_H

#include <QDialog>

#include "ui_DialogSort.h"

#include "EnumsFunctions.h"

class DialogSort : public QDialog, public Ui_DialogSort
{
	Q_OBJECT

public:
	DialogSort(QWidget *parent = 0);
	DialogSort(KPDNodeSortMode nodeSortMode, bool pairDecreasing, KPDMatchSortMode matchSortMode, bool matchDecreasing, QWidget *parent = 0);
};

#endif