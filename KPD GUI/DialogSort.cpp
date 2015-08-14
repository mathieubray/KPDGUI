#include <QtGui>

#include "DialogSort.h"

//Basic Sort Options Dialog
SortDialog::SortDialog(QWidget *parent) : QDialog(parent)
{
	setupUi(this);
}

//Saved Sort Options Dialog
SortDialog::SortDialog(int pairSortMode, bool pairDecreasing, int matchSortMode, bool matchDecreasing, QWidget *parent) : QDialog(parent)
{
	setupUi(this);

	pairsComboBox->setCurrentIndex(pairSortMode);
	pairsDecreasingCheckBox->setChecked(pairDecreasing);
	matchesComboBox->setCurrentIndex(matchSortMode);
	matchesDecreasingCheckBox->setChecked(matchDecreasing);
}