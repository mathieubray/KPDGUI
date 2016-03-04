#include <QtGui>

#include "DialogSort.h"

//Basic Sort Options Dialog
DialogSort::DialogSort(QWidget *parent) : QDialog(parent)
{
	setupUi(this);
}

//Saved Sort Options Dialog
DialogSort::DialogSort(KPDNodeSortMode nodeSortMode, bool nodeDecreasing, KPDMatchSortMode matchSortMode, bool matchDecreasing, QWidget *parent) : QDialog(parent)
{
	setupUi(this);

	nodesComboBox->setCurrentIndex(KPDFunctions::nodeSortModeToInt(nodeSortMode));
	nodesDecreasingCheckBox->setChecked(nodeDecreasing);
	matchesComboBox->setCurrentIndex(KPDFunctions::matchSortModeToInt(matchSortMode));
	matchesDecreasingCheckBox->setChecked(matchDecreasing);
}