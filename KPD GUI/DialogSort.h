#ifndef DIALOGSORT_H
#define DIALOGSORT_H

#include <QDialog>

#include "ui_SortDialog.h"

class SortDialog : public QDialog, public Ui_SortDialog
{
	Q_OBJECT

public:
	SortDialog(QWidget *parent = 0);
	SortDialog(int pairSortMode, bool pairDecreasing, int matchSortMode, bool matchDecreasing, QWidget *parent = 0);
};

#endif