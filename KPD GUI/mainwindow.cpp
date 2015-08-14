#include <QtGui>
#include <QtWidgets>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	//Parameters
	maxZ = 0;
	seqNumber = 0;
	mostRecentNodeID = -1;
	setCurrentFile("");
	prevSliderPos = ui->zoomSlider->value();

	//Visual and Storage Properties
	//Graphics Scene
	scene = new KPDGUIGraphicsScene();
	ui->graphicsView->setScene(scene);
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
	connect(scene, SIGNAL(selectionChanged()),this, SLOT(checkSelections()));
	connect(scene, SIGNAL(deleteNode(int)), this, SLOT(deleteNode(int)));
	connect(scene, SIGNAL(screenChanged()), this, SLOT(updateVisibility()));
	
	//Simulation Parameters
	simulParam = new KPDGUISimulParam();

	//Pair List
	listWidget = new QTreeWidget();
	listWidget->setHeaderHidden(true);
	listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
	listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	connect(listWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(newPairListSelectionActions(QTreeWidgetItem*)));
	ui->tabWidget->addTab(listWidget, "Pairs/Ads");

	//Match List
	matchWidget = new QTreeWidget();
	matchWidget->setHeaderHidden(true);
	matchWidget->setSelectionMode(QAbstractItemView::MultiSelection);
	matchWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	connect(matchWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(newMatchListSelectionActions(QTreeWidgetItem*)));
	ui->tabWidget->addTab(matchWidget, "Matches");
	
	//Structures
	structureTreeWidget = new QTreeWidget();
	structureTreeWidget->setHeaderHidden(true);
	structureTreeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	structureTreeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	structureTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(structureTreeWidget, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this, SLOT(newTreeSelectionActions(QTreeWidgetItem*)));
	connect(structureTreeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(cycleTreeCustomMenu(QPoint)));
	ui->tabWidget->addTab(structureTreeWidget, "Structures");
	
	//Solutions
	solutionTreeWidget = new QTreeWidget();
	solutionTreeWidget->setHeaderHidden(true);
	solutionTreeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	solutionTreeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	solutionTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(solutionTreeWidget, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this, SLOT(newTreeSelectionActions(QTreeWidgetItem*)));
	connect(solutionTreeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(solutionTreeCustomMenu(QPoint)));
	ui->tabWidget->addTab(solutionTreeWidget, "Solutions");

	//Console
	ui->consoleWidget->addConsoleInfo("Welcome to KPDGUI - " + QDate::currentDate().toString() + " " + QTime::currentTime().toString() + "\n");
	
	//Pair Record
	kpdguiRecord = new KPDGUIRecord();
	//connect(kpdguiRecord, SIGNAL(takeAdditionalDeleteNodeActions(KPDGUINode *)), this, SLOT(deleteNode(KPDGUINode *)));
	ui->consoleWidget->setRecord(kpdguiRecord);

	//Display Modes
	displaySettings.showAllPairs = true;
	displaySettings.showPairsInStructures = false;
	displaySettings.showPairsInSolutions = false;
	displaySettings.showPairSubset = false;
	displaySettings.showPairsOnHold = true;
	displaySettings.showPairsWithNoCompatibilities = true;
	displaySettings.showPairsOfMinPRA = false;
	displaySettings.showPairsOfMaxPRA = false;
	displaySettings.minPRA = 0;
	displaySettings.maxPRA = 100;
	displaySettings.arrowDisplayMode = 0;

	//Sort Modes
	pairSortMode = 0;
	pairSortDecreasing = false;
	matchSortMode = 0;
	matchSortDecreasing = false;

	//Actions
	createAdditionalActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (okToContinue()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::newFile()
{
    MainWindow *mainWin = new MainWindow;
    mainWin->show();
}

void MainWindow::open()
{
    if (okToContinue()) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open KPD"), ".", tr("KPD files (*.kpd)"));
		if (!fileName.isEmpty()){
			loadFile(fileName);
		}
    }
}

bool MainWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save KPD"), ".", tr("KPD files (*.kpd)"));
    if (fileName.isEmpty()){
        ui->consoleWidget->addConsoleInfo(tr("> Failed To Save File\n"));
		return false;
	}
		
    return saveFile(fileName);
}

void MainWindow::exitProgram()
{
	qApp->closeAllWindows();
}

void MainWindow::about()
{
	QMessageBox::about(this, tr("About KPDGUI"),
		tr("<h2>KPDGUI 1.1</h2>"
		"<p>Copyright &copy; 2014."
		"<p>Author: Mathieu Bray"));

	ui->consoleWidget->addConsoleInfo(tr("> Opened About Screen"));
}

void MainWindow::run()
{
	bool proceed = true;

	if (!simulParam->getParametersSet()) {
		int r = QMessageBox::warning(this, tr("KPD"),
			tr("The pool has been modified since the last time parameters were set.\n"
			"Set parameters now?"),
			QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		if (r == QMessageBox::Yes) {
			proceed = setSimParameters();
		}
		else if (r == QMessageBox::Cancel) {
			proceed = false;
		}
	}

	if (proceed) {
		runSimulation();
		statusBar()->showMessage("Run Successful", 2000);
		ui->consoleWidget->addConsoleInfo(tr("> Run Successful"));
	}
	else {
		statusBar()->showMessage("Run Aborted", 2000);
		ui->consoleWidget->addConsoleInfo(tr("> Run Aborted"));
	}
}

void MainWindow::addNewPair()
{
	PairDialog dialog(this);

	if (dialog.exec()) {
		
		Candidate c;
		Donor d;

		d.name = dialog.donorNameLineEdit->text();
		c.name = dialog.recipNameLineEdit->text();
		d.age = dialog.donorAgeSpinBox->value();
		c.age = dialog.recipAgeSpinBox->value();
		d.BT = dialog.donorBTComboBox->currentText();
		c.BT = dialog.recipBTComboBox->currentText();
		c.pra = dialog.recipPRASpinBox->value();
		c.sensitized = dialog.recipSensitizedCheckBox->isChecked();

		double recipHeight = dialog.recipHeightSpinBox->value();
		double recipWeight = dialog.recipWeightSpinBox->value();
		c.BMI =  recipWeight / recipHeight / recipHeight;
		c.weight = recipWeight;
		c.diabetes = dialog.recipDiabetesCheckBox->isChecked();
		QString recipGender = dialog.recipGenderComboBox->currentText();
		if (recipGender == "Male"){ c.genderMale = true; }
		else { c.genderMale = false;  }		
		c.race = dialog.recipRaceComboBox->currentText();
		c.prevTrans = dialog.recipPrevTransCheckBox->isChecked();
		c.TOD = dialog.recipTODSpinBox->value();
		c.hepC = dialog.recipHepCCheckBox->isChecked();

		double donorHeight = dialog.donorHeightSpinBox->value();
		double donorWeight = dialog.donorWeightSpinBox->value();
		d.BMI =  donorWeight / donorHeight / donorHeight;
		d.weight = donorWeight;
		QString donorGender = dialog.donorGenderComboBox->currentText();
		if (donorGender == "Male"){ d.genderMale = true; }
		else { d.genderMale = false; }

		d.id = -1;
		d.donorid = -1;
		c.id = -1;
		c.recipid = -1;

		QString antibodies = dialog.recipHLALineEdit->text();
		QStringList antibodyList = antibodies.split(";");

		foreach(QString antibody, antibodyList){
			c.antibodies.push_back(antibody);
		}

		d.donorA.push_back(dialog.donorA1LineEdit->text());
		d.donorA.push_back(dialog.donorA2LineEdit->text());
		d.donorB.push_back(dialog.donorB1lineEdit->text());
		d.donorB.push_back(dialog.donorB2LineEdit->text());
		d.donorCW.push_back(dialog.donorCW1LineEdit->text());
		d.donorCW.push_back(dialog.donorCW2LineEdit->text());
		d.donorDP.push_back(dialog.donorDP1LineEdit->text());
		d.donorDP.push_back(dialog.donorDP2LineEdit->text());
		d.donorDQ.push_back(dialog.donorDQ1LineEdit->text());
		d.donorDQ.push_back(dialog.donorDQ2LineEdit->text());
		d.donorDR.push_back(dialog.donorDR1LineEdit->text());
		d.donorDR.push_back(dialog.donorDR2LineEdit->text());
		d.donorBW4 = dialog.donorBW4CheckBox->isChecked();
		d.donorBW6 = dialog.donorBW6CheckBox->isChecked();
		d.donorDR51 = dialog.donorDR51CheckBox->isChecked();
		d.donorDR52 = dialog.donorDR52CheckBox->isChecked();
		d.donorDR53 = dialog.donorDR53CheckBox->isChecked();
		d.type = 0;

		QString comment = dialog.commentTextEdit->toPlainText();

		KPDGUINode * newPair = new KPDGUINode(d, c, comment);
		connect(newPair, SIGNAL(nodeWasClicked(int,bool)), this, SLOT(clickActions(int,bool)));
		connect(newPair, SIGNAL(nodeSelectionChanged(int, bool)), ui->consoleWidget, SLOT(changePairInfo(int, bool)));
		connect(newPair, SIGNAL(nodeHoldStatusChanged(int, bool)), ui->consoleWidget, SLOT(changePairText(int)));
		connect(newPair, SIGNAL(nodeEdited(int)), ui->consoleWidget, SLOT(changePairText(int)));
		connect(newPair, SIGNAL(nodeEdited(int)), this, SLOT(updateTable(int)));

		addNode(newPair, false);
		ui->consoleWidget->addPairInfo(newPair->getInternalID());

		scene->clearSelection();
		newPair->setSelected(true);
		changeFocus(newPair->getInternalID());
		ui->consoleWidget->focusOnPairScreen(newPair->getInternalID());
		
		statusBar()->showMessage("Added Pair", 2000);
		ui->consoleWidget->addConsoleInfo("> Added New Pair: " + d.name + ", " + c.name + " (" + QString::number(newPair->getInternalID()) + ")");
		
		setWindowModified(true);		
	}	
}

void MainWindow::addNewAD()
{
	AltruisticDonorDialog dialog(this);

	if (dialog.exec()) {
		
		Candidate dummy;
		Donor ad;

		ad.name = dialog.donorNameLineEdit->text();
		ad.age = dialog.donorAgeSpinBox->value();
		ad.BT = dialog.donorBTComboBox->currentText();

		double donorHeight = dialog.donorHeightSpinBox->value();
		double donorWeight = dialog.donorWeightSpinBox->value();
		ad.BMI =  donorWeight / donorHeight / donorHeight;
		ad.weight = donorWeight;
		QString donorGender = dialog.donorGenderComboBox->currentText();
		if (donorGender == "Male"){ ad.genderMale = true; }
		else { ad.genderMale = false; }

		ad.id = -1;
		ad.donorid = -1;

		ad.donorA.push_back(dialog.donorA1LineEdit->text());
		ad.donorA.push_back(dialog.donorA2LineEdit->text());
		ad.donorB.push_back(dialog.donorB1lineEdit->text());
		ad.donorB.push_back(dialog.donorB2LineEdit->text());
		ad.donorCW.push_back(dialog.donorCW1LineEdit->text());
		ad.donorCW.push_back(dialog.donorCW2LineEdit->text());
		ad.donorDP.push_back(dialog.donorDP1LineEdit->text());
		ad.donorDP.push_back(dialog.donorDP2LineEdit->text());
		ad.donorDQ.push_back(dialog.donorDQ1LineEdit->text());
		ad.donorDQ.push_back(dialog.donorDQ2LineEdit->text());
		ad.donorDR.push_back(dialog.donorDR1LineEdit->text());
		ad.donorDR.push_back(dialog.donorDR2LineEdit->text());
		ad.donorBW4 = dialog.donorBW4CheckBox->isChecked();
		ad.donorBW6 = dialog.donorBW6CheckBox->isChecked();
		ad.donorDR51 = dialog.donorDR51CheckBox->isChecked();
		ad.donorDR52 = dialog.donorDR52CheckBox->isChecked();
		ad.donorDR53 = dialog.donorDR53CheckBox->isChecked();

		ad.type = 1;

		QString comment = dialog.commentTextEdit->toPlainText();

		KPDGUINode * newAD = new KPDGUINode(ad, dummy, comment);
		connect(newAD, SIGNAL(nodeWasClicked(int, bool)), this, SLOT(clickActions(int, bool)));
		connect(newAD, SIGNAL(nodeSelectionChanged(int, bool)), ui->consoleWidget, SLOT(changePairInfo(int, bool)));
		connect(newAD, SIGNAL(nodeHoldStatusChanged(int, bool)), ui->consoleWidget, SLOT(changePairText(int)));
		connect(newAD, SIGNAL(nodeEdited(int)), ui->consoleWidget, SLOT(changePairText(int)));
		connect(newAD, SIGNAL(nodeEdited(int)), this, SLOT(updateTable(int)));

		addNode(newAD,false);
		ui->consoleWidget->addPairInfo(newAD->getInternalID());

		scene->clearSelection();
		newAD->setSelected(true);
		changeFocus(newAD->getInternalID());
		ui->consoleWidget->focusOnPairScreen(newAD->getInternalID());

		statusBar()->showMessage("Added AD", 2000);
		ui->consoleWidget->addConsoleInfo("> Added New AD: " + ad.name + " (" + QString::number(newAD->getInternalID()) + ")");

		setWindowModified(true);
	}
}

void MainWindow::loadPairs()
{
	ReadFileDialog readFileDialog(this);

	if (readFileDialog.exec()) {
		QApplication::setOverrideCursor(Qt::WaitCursor);
		QApplication::processEvents();

		scene->clearSelection();

		QString str = readFileDialog.pairFileLineEdit->text();

		readPairsFromFile(str);
		//int pairsAdded = kpdguiRecord->loadPairs(str);
		/*for (int i = kpdguiRecord->size() - 1; i >= kpdguiRecord->size() - pairsAdded; i--){
			connect(kpdguiRecord->getNodeFromIndex(i), SIGNAL(nodeWasClicked(int, bool)), this, SLOT(clickActions(int, bool)));
			connect(kpdguiRecord->getNodeFromIndex(i), SIGNAL(nodeSelectionChanged(int, bool)), ui->consoleWidget, SLOT(changePairInfo(int, bool)));
			connect(kpdguiRecord->getNodeFromIndex(i), SIGNAL(nodeHoldStatusChanged(int, bool)), ui->consoleWidget, SLOT(changePairText(int)));
			connect(kpdguiRecord->getNodeFromIndex(i), SIGNAL(nodeEdited(int)), ui->consoleWidget, SLOT(changePairText(int)));
			connect(kpdguiRecord->getNodeFromIndex(i), SIGNAL(nodeEdited(int)), this, SLOT(updateTable(int)));

			ui->consoleWidget->addPairInfo(kpdguiRecord->getNodeFromIndex(i)->getInternalID());
		}*/

		QStringList splitstr = str.split("\\");
		statusBar()->showMessage("Loaded Pairs From File: " + splitstr.last(), 2000);
		ui->consoleWidget->addConsoleInfo("> Loaded Pairs From " + splitstr.last());

		setWindowModified(true);
		simulParam->setParametersSet(false);

		QApplication::restoreOverrideCursor();
		QApplication::processEvents();
		
		updateVisibility();
	}
}

void MainWindow::deleteNode(int i)
{
	KPDGUINode * nodeToDelete = kpdguiRecord->getNode(i);
	nodeToDelete->setSelected(false);
	
	QApplication::setOverrideCursor(Qt::WaitCursor);
	QApplication::processEvents();

	QSet<KPDGUINodeWrapper *> nodeWrappersToDelete;
	QSet<KPDGUIArrowWrapper *> arrowWrappersToDelete;
	QSet<KPDGUIStructureWrapper *> structureWrappersToDelete;
	QSet<KPDGUIStructure *> structuresToDelete;

	for (int i = 0; i < listWidget->topLevelItemCount(); i++){
		KPDGUINodeWrapper * nodeWrapper = dynamic_cast<KPDGUINodeWrapper *>(listWidget->topLevelItem(i));
		if (nodeWrapper){
			if (nodeWrapper->getNode()->getInternalID() == nodeToDelete->getInternalID()){
				nodeWrappersToDelete.insert(nodeWrapper);
			}
		}
	}

	for (int i = 0; i < matchWidget->topLevelItemCount(); i++){
		KPDGUIArrowWrapper * arrowWrapper = dynamic_cast<KPDGUIArrowWrapper *>(matchWidget->topLevelItem(i));
		if (arrowWrapper){
			if (arrowWrapper->getArrow()->startItem()->getInternalID() == nodeToDelete->getInternalID()){
				arrowWrappersToDelete.insert(arrowWrapper);
			}
			else if (arrowWrapper->getArrow()->endItem()->getInternalID() == nodeToDelete->getInternalID()){
				arrowWrappersToDelete.insert(arrowWrapper);
			}
		}
	}	

	for (int i = 0; i < structureTreeWidget->topLevelItemCount(); i++){
		KPDGUIStructureSet * structureSet = dynamic_cast<KPDGUIStructureSet *>(structureTreeWidget->topLevelItem(i));
		if (structureSet){
			for (int j = structureSet->childCount() - 1; j >= 0; j--){
				KPDGUIStructureWrapper * structureWrapper = dynamic_cast<KPDGUIStructureWrapper *>(structureSet->child(j));
				if (structureWrapper){
					if (structureWrapper->getStructure()->contains(nodeToDelete)){
						structuresToDelete.insert(structureWrapper->getStructure());
						structureSet->removeChild(structureSet->child(j));
						structureSet->removeStructure(structureWrapper->getStructure());
						structureWrappersToDelete.insert(structureWrapper);
					}
				}
			}
		}
	}

	for (int i = 0; i < solutionTreeWidget->topLevelItemCount(); i++){
		KPDGUIStructureSet * structureSet = dynamic_cast<KPDGUIStructureSet *>(solutionTreeWidget->topLevelItem(i));
		if (structureSet){
			for (int j = structureSet->childCount() - 1; j >= 0; j--){
				KPDGUIStructureWrapper * structureWrapper = dynamic_cast<KPDGUIStructureWrapper *>(structureSet->child(j));
				if (structureWrapper){
					if (structureWrapper->getStructure()->contains(nodeToDelete)){
						structuresToDelete.insert(structureWrapper->getStructure());
						structureSet->removeChild(structureSet->child(j));
						structureSet->removeStructure(structureWrapper->getStructure());
						structureWrappersToDelete.insert(structureWrapper);
					}
				}
			}
		}
	}

	foreach(KPDGUINodeWrapper * nodeWrapper, nodeWrappersToDelete){
		delete nodeWrapper;
	}

	foreach(KPDGUIArrowWrapper * arrowWrapper, arrowWrappersToDelete){
		delete arrowWrapper;
	}

	foreach(KPDGUIStructureWrapper * structureWrapper, structureWrappersToDelete){
		delete structureWrapper;
	}

	foreach(KPDGUIStructure * structureToDelete, structuresToDelete){
		delete structureToDelete;
	}

	if (nodeToDelete->getType() == 1){
		ui->consoleWidget->addConsoleInfo("> Deleted AD: " + nodeToDelete->getDonorName() + " (" + QString::number(nodeToDelete->getInternalID()) + ")");
	}
	else {
		ui->consoleWidget->addConsoleInfo("> Deleted Pair: " + nodeToDelete->getDonorName() + ", " + nodeToDelete->getRecipName() + " (" + QString::number(nodeToDelete->getInternalID()) + ")");
	}
	ui->consoleWidget->deletePairInfo(nodeToDelete->getInternalID());

	delete nodeToDelete;

	setWindowModified(true);

	QApplication::restoreOverrideCursor();
	QApplication::processEvents();
}

void MainWindow::clickActions(int i, bool selected)
{
	//KPDGUINode * node = kpdguiRecord->getNode(i);
	
	//node->setSelected(true);
	if (selected){
		updateTable(i);
		ui->consoleWidget->focusOnPairScreen(i);
	}
	else if (!(i==mostRecentNodeID)){
		clearTable();
	}
}

void MainWindow::newPairListSelectionActions(QTreeWidgetItem* item)
{
	KPDGUINodeWrapper * node = dynamic_cast<KPDGUINodeWrapper *>(item);
	if (node){
		int i = node->getNode()->getInternalID();

		bool selected = item->isSelected();
		KPDGUINode * node = kpdguiRecord->getNode(i);
		node->setSelected(selected);

		if (selected){
			ui->graphicsView->centerOn(QPointF(node->x(), node->y()));
		}

		if (selected){
			updateTable(i);
		}
		else if (!(i==mostRecentNodeID)){
			clearTable();
		}

		updateVisibility();
	}
}

void MainWindow::newMatchListSelectionActions(QTreeWidgetItem* item)
{	
	KPDGUIArrowWrapper * arrow = dynamic_cast<KPDGUIArrowWrapper *>(item);
	if (arrow){
		KPDGUIArrow * link = arrow->getArrow();
		
		bool selected = item->isSelected();
		link->startItem()->setSelected(selected);
		link->endItem()->setSelected(selected);
		
	}	
}

void MainWindow::newTreeSelectionActions(QTreeWidgetItem* item)
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	QApplication::processEvents();

	bool selected = item->isSelected();
	//////qDebug() << selected;
	
	//KPDGUIStructureSet * structureSet = dynamic_cast<KPDGUIStructureSet *>(item);
	//KPDGUIStructureWrapper * structureWrapper = dynamic_cast<KPDGUIStructureWrapper *>(item);
	//KPDGUINodeWrapper * nodeWrapper = dynamic_cast<KPDGUINodeWrapper *>(item);
	
	//kpdguiRecord->undoHighlights();
	////qDebug() << "A";
	ui->consoleWidget->removeSolutionScreen();
	////qDebug() << "B";
	if (selectedStructures.size() > 0){
		foreach(KPDGUIStructure * structure, selectedStructures){
			structure->undoHighlights();
		}
	}
	////qDebug() << "C";
	selectedStructures.clear();
	
	if (selected){
		
		////qDebug() << "D";
		int level;
		if (!item->parent()){
			level = 0;
		}
		else if (!item->parent()->parent()){
			level = 1;
		}
		else if (!item->parent()->parent()->parent()){
			level = 2;
		}
		else {
			level = 3;
		}

		if (level==0){
			////qDebug() << "E";
			KPDGUIStructureSet * structureSet = dynamic_cast<KPDGUIStructureSet *>(item);
			if (structureSet){
				////qDebug() << "F";
				scene->clearSelection();
				////qDebug() << "G";
				structureSet->selectStructures();
				////qDebug() << "H";
				clearTable();
				////qDebug() << "I";
				updateVisibility();
				////qDebug() << "J";
				structureSet->highlight();
				////qDebug() << "K";

				foreach(KPDGUIStructure * structure, structureSet->getStructures()){
					selectedStructures.push_back(structure);
				}
				////qDebug() << "L";
				ui->consoleWidget->addSolutionInfo(structureSet->getConsoleString());
				////qDebug() << "M";
				ui->consoleWidget->focusOnSolutionScreen();
				//ui->graphicsView->centerOn(QPoint(structureSet->centerX(), structureSet->centerY()));
			}
		}
		else if (level == 2) {
			KPDGUIStructureWrapper * structureWrapper = dynamic_cast<KPDGUIStructureWrapper *>(item);
			if (structureWrapper){
				KPDGUIStructure * structure = structureWrapper->getStructure();
				scene->clearSelection();
				structure->select();
				clearTable();
				updateVisibility();
				structure->highlight();

				selectedStructures.push_back(structure);

				ui->graphicsView->centerOn(QPoint(structure->centerX(), structure->centerY()));
			}
		}
		else if (level==3){
			KPDGUINodeWrapper * nodeWrapper = dynamic_cast<KPDGUINodeWrapper *>(item);
			if (nodeWrapper){
				KPDGUINode * node = nodeWrapper->getNode();
				scene->clearSelection();
				node->setSelected(selected);
				updateVisibility();

				ui->graphicsView->centerOn(QPoint(node->x(), node->y()));

				int i = node->getInternalID();
				if (selected){
					updateTable(i);
				}
				else {
					clearTable();
				}
			}
		}
		else {
			scene->clearSelection();
			if (item->childCount() > 0){				
				for (int j = 0; j < item->childCount(); j++){
					KPDGUIStructureWrapper * childWrapper = dynamic_cast<KPDGUIStructureWrapper *>(item->child(j));
					if (childWrapper){
						KPDGUIStructure * child = childWrapper->getStructure();

						child->select();						
						child->highlight();

						if (j == 0){
							ui->graphicsView->centerOn(QPoint(child->centerX(), child->centerY()));
						}

						selectedStructures.push_back(child);
					}
				}
				updateVisibility();
			}
			clearTable();
		}
		
	}
	else {
		scene->clearSelection();
		updateVisibility();
		clearTable();
	}
	
	QApplication::restoreOverrideCursor();
	QApplication::processEvents();
	//updateVisibility();
	//QApplication::restoreOverrideCursor();
	//QApplication::processEvents();
}


void MainWindow::checkSelections(){
	if (scene->selectedItems().size() == 0){
		clearTable();
	}

	bringToFront();
	updateVisibility();
}

void MainWindow::updateStatusBar()
{

}

void MainWindow::updateTable(int i)
{
	KPDGUINode * node = kpdguiRecord->getNode(i);

		ui->tableWidget->item(0, 0)->setData(Qt::EditRole, QString::number(i));
		ui->tableWidget->item(1, 0)->setData(Qt::EditRole, node->getDonorName());
		ui->tableWidget->item(2, 0)->setData(Qt::EditRole, QString::number(node->getDonorAge()));
		ui->tableWidget->item(3, 0)->setData(Qt::EditRole, node->getDonorBT());

		if (node->getType() == 0){
			ui->tableWidget->item(4, 0)->setData(Qt::EditRole, node->getRecipName());
			ui->tableWidget->item(5, 0)->setData(Qt::EditRole, QString::number(node->getRecipAge()));
			ui->tableWidget->item(6, 0)->setData(Qt::EditRole, node->getRecipBT());
			ui->tableWidget->item(7, 0)->setData(Qt::EditRole, QString::number(node->getRecipPRA()));
			ui->tableWidget->item(8, 0)->setData(Qt::EditRole, " ");
		}
		else if (node->getType() == 1){
			ui->tableWidget->item(4, 0)->setData(Qt::EditRole, " ");
			ui->tableWidget->item(5, 0)->setData(Qt::EditRole, " ");
			ui->tableWidget->item(6, 0)->setData(Qt::EditRole, " ");
			ui->tableWidget->item(7, 0)->setData(Qt::EditRole, " ");
			ui->tableWidget->item(8, 0)->setData(Qt::EditRole, " ");
		}
	
	mostRecentNodeID = i;	
}

void MainWindow::updateVisibility(){
	emit visibilityChanged(&displaySettings);
}

void MainWindow::clusterStructure(){

	QApplication::setOverrideCursor(Qt::WaitCursor);
	QApplication::processEvents();

	rightClickStructure->cluster();
	rightClickStructure->select();
	rightClickStructure->highlight();

	QApplication::restoreOverrideCursor();
	QApplication::processEvents();

	ui->graphicsView->centerOn(QPoint(rightClickStructure->centerX(), rightClickStructure->centerY()));
}

void MainWindow::clusterSolution(){

	QApplication::setOverrideCursor(Qt::WaitCursor);
	QApplication::processEvents();

	rightClickStructureSet->cluster();
	rightClickStructureSet->selectStructures();
	rightClickStructureSet->highlight();

	QApplication::restoreOverrideCursor();
	QApplication::processEvents();

	ui->graphicsView->centerOn(QPoint(rightClickStructureSet->centerX(), rightClickStructureSet->centerY()));
}

void MainWindow::removeSolution(){
	int r = QMessageBox::warning(this, tr("KPD"),
		tr("Remove Solution?"),
		QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	if (r == QMessageBox::Yes) {
		int index = solutionTreeWidget->indexOfTopLevelItem(rightClickStructureSet);
		QTreeWidgetItem * solutionToDelete = solutionTreeWidget->takeTopLevelItem(index);
		delete solutionToDelete;
		scene->clearSelection();

		resort();

		setWindowModified(true);
	}	
}

void MainWindow::clearSolutions(){
	int r = QMessageBox::warning(this, tr("KPD"),
		tr("Remove Solutions?"),
		QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	if (r == QMessageBox::Yes) {
		int items = solutionTreeWidget->topLevelItemCount();
		for (int i = 0; i < items; i++){
			/*KPDGUIStructureSet * structureSet = dynamic_cast<KPDGUIStructureSet *>(solutionTreeWidget->takeTopLevelItem(0));
			if (structureSet){
				structureSet->resetPopularity();
			}*/
			QTreeWidgetItem * solutionToDelete = solutionTreeWidget->takeTopLevelItem(0);
			delete solutionToDelete;			
		}		
		
		scene->clearSelection();

		resort();

		setWindowModified(true);
	}	
}

void MainWindow::zoomIn(){
	int position = ui->zoomSlider->value();

	if (position < 4){
		position++;
		ui->zoomSlider->setValue(position);
	}
}

void MainWindow::zoomOut(){
	int position = ui->zoomSlider->value();

	if (position > -2){
		position--;
		ui->zoomSlider->setValue(position);
	}
}

void MainWindow::zoom(int tick){

	double scaleFactor = 1.2;
	ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

	if (tick > prevSliderPos){
		for (int i = 0; i < (tick - prevSliderPos); i++){
			ui->graphicsView->scale(scaleFactor, scaleFactor);
		}
	}
	else if (tick < prevSliderPos){
		for (int i = 0; i < (prevSliderPos - tick); i++){
			ui->graphicsView->scale(1 / scaleFactor, 1 / scaleFactor);
		}
	}
	prevSliderPos = tick;
	statusBar()->showMessage("Zoomed (" + QString::number(tick) + ")", 2000);
}

void MainWindow::sort(){

	SortDialog sortDialog(pairSortMode,pairSortDecreasing,matchSortMode,matchSortDecreasing,this);

	if (sortDialog.exec()) {
		QApplication::setOverrideCursor(Qt::WaitCursor);
		QApplication::processEvents();

		int pairSortSetting = sortDialog.pairsComboBox->currentIndex();
		bool pairDecreasing = sortDialog.pairsDecreasingCheckBox->isChecked();
		int matchSortSetting = sortDialog.matchesComboBox->currentIndex();
		bool matchDecreasing = sortDialog.matchesDecreasingCheckBox->isChecked();
		
		setPairSortMode(pairSortSetting, pairDecreasing);
		setMatchSortMode(matchSortSetting, matchDecreasing);

		QApplication::restoreOverrideCursor();
		QApplication::processEvents();

		setWindowModified(true);
	}
}

void MainWindow::changeFocus(int i){
	KPDGUINode *node = kpdguiRecord->getNode(i);

	ui->graphicsView->centerOn(node->x(), node->y());

	setWindowModified(true);
}

void MainWindow::setDisplaySettings(DisplaySettingsStruct * newDisplaySettings){

	displaySettings.showAllPairs = newDisplaySettings->showAllPairs;
	displaySettings.showPairsInStructures = newDisplaySettings->showPairsInStructures;
	displaySettings.showPairsInSolutions = newDisplaySettings->showPairsInSolutions;
	displaySettings.showPairSubset = newDisplaySettings->showPairSubset;
	displaySettings.showPairsOnHold = newDisplaySettings->showPairsOnHold;
	displaySettings.showPairsWithNoCompatibilities = newDisplaySettings->showPairsWithNoCompatibilities;
	displaySettings.showPairsOfMinPRA = newDisplaySettings->showPairsOfMinPRA;
	displaySettings.showPairsOfMaxPRA = newDisplaySettings->showPairsOfMaxPRA;
	displaySettings.minPRA = newDisplaySettings->minPRA;
	displaySettings.maxPRA = newDisplaySettings->maxPRA;
	displaySettings.arrowDisplayMode = newDisplaySettings->arrowDisplayMode;
	
	emit visibilityChanged(&displaySettings);
}

void MainWindow::resort(){
	setPairSortMode(pairSortMode, pairSortDecreasing);
	setMatchSortMode(matchSortMode, matchSortDecreasing);
}

void MainWindow::setPairSortMode(int mode, bool decreasing){
	pairSortMode = mode;
	pairSortDecreasing = decreasing;

	QList<KPDGUINodeWrapper*> newPairList;
	int itemCount = listWidget->topLevelItemCount();
	for (int i = 0; i < itemCount; i++){
		KPDGUINodeWrapper * temp = dynamic_cast<KPDGUINodeWrapper *>(listWidget->takeTopLevelItem(0));
		if (temp){
			newPairList.push_back(temp);
		}
	}
	if (pairSortDecreasing){
		qSort(newPairList.begin(), newPairList.end(), KPDGUINodeGreaterThan(pairSortMode));
	}
	else {
		qSort(newPairList.begin(), newPairList.end(), KPDGUINodeLessThan(pairSortMode));
	}

	foreach(KPDGUINodeWrapper * item, newPairList){
		item->updateText(pairSortMode);
		listWidget->addTopLevelItem(item);
	}
}

void MainWindow::setMatchSortMode(int mode, bool decreasing){
	matchSortMode = mode;
	matchSortDecreasing = decreasing;

	QList<KPDGUIArrowWrapper*> newArrowList;
	int itemCount = matchWidget->topLevelItemCount();
	for (int i = 0; i < itemCount; i++){
		KPDGUIArrowWrapper * temp = dynamic_cast<KPDGUIArrowWrapper *>(matchWidget->takeTopLevelItem(0));
		if (temp){
			newArrowList.push_back(temp);
		}
	}
	if (matchSortDecreasing){
		qSort(newArrowList.begin(), newArrowList.end(), KPDGUIArrowGreaterThan(matchSortMode));
	}
	else {
		qSort(newArrowList.begin(), newArrowList.end(), KPDGUIArrowLessThan(matchSortMode));
	}

	foreach(KPDGUIArrowWrapper * item, newArrowList){
		item->updateText(matchSortMode);
		matchWidget->addTopLevelItem(item);
	}
}

bool MainWindow::setSimParameters()
{
	ParamInfoStruct oldParamInfo;
	oldParamInfo.maxChainLength = simulParam->getMaxChainLength();
	oldParamInfo.utilScheme = QString::fromStdString(simulParam->getUtilityScheme());
	if (simulParam->getMUC()){
		oldParamInfo.optScheme = "MUC";
	}
	else if (simulParam->getMEUC()){
		oldParamInfo.optScheme = "MEUC";
	}
	else if (simulParam->getMEUS()){
		oldParamInfo.optScheme = "MEUS";
	}
	else if (simulParam->getSCC()){
		oldParamInfo.optScheme = "SCC";
	}
	oldParamInfo.praAdvantage = simulParam->getPRAadvantage();
	oldParamInfo.reserveOtoO = simulParam->getReserveOtoO();
	oldParamInfo.checkDP = simulParam->getCheckDP();
	oldParamInfo.includeCompatiblePairs = simulParam->getIncludeCompatiblePairsFlag();
	oldParamInfo.includeABBridgeDonors = simulParam->getIncludeABbridgeDonorsFlag();
	oldParamInfo.numberOfSolutions = simulParam->getTiebreakIterations();

	SimParamDialog simParamDialog(oldParamInfo, this);

	if (simParamDialog.exec()) {
		ParamInfoStruct newParamInfo;
		newParamInfo.maxChainLength = simParamDialog.chainLengthSpinBox->value();
		newParamInfo.utilScheme = simParamDialog.utilComboBox->currentText();
		newParamInfo.optScheme = simParamDialog.optComboBox->currentText();
		newParamInfo.praAdvantage = simParamDialog.praBox->isChecked();
		newParamInfo.reserveOtoO = simParamDialog.reserveOtoOBox->isChecked();
		newParamInfo.checkDP = simParamDialog.checkDPBox->isChecked();
		newParamInfo.includeCompatiblePairs = simParamDialog.compatibleBox->isChecked();
		newParamInfo.includeABBridgeDonors = simParamDialog.allowABBox->isChecked();
		newParamInfo.numberOfSolutions = simParamDialog.tiebreakBox->value();

		simulParam->processParams(newParamInfo);

		statusBar()->showMessage("Set New Parameters", 2000);
		ui->consoleWidget->addConsoleInfo(tr("> Set New Parameters"));

		simulParam->setParametersSet(true);

		return true;
	}

	return false;
}

void MainWindow::changeArrowViewMode(int index)
{
	displaySettings.arrowDisplayMode = index;
	setDisplaySettings(&displaySettings);
}

void MainWindow::changePairViewMode(int index)
{
	if (index == 0){
		displaySettings.showAllPairs = true;
		displaySettings.showPairsInStructures = false;
		displaySettings.showPairsInSolutions = false;
		displaySettings.showPairSubset = false;
		displaySettings.showPairsOnHold = true;
		displaySettings.showPairsWithNoCompatibilities = true;
		displaySettings.showPairsOfMinPRA = false;
		displaySettings.minPRA = 0;
		displaySettings.showPairsOfMaxPRA = false;
		displaySettings.maxPRA = 100;
	}

	else if (index == 1){
		displaySettings.showAllPairs = false;
		displaySettings.showPairsInStructures = false;
		displaySettings.showPairsInSolutions = false;
		displaySettings.showPairSubset = true;
		displaySettings.showPairsOnHold = true;
		displaySettings.showPairsWithNoCompatibilities = false;
		displaySettings.showPairsOfMinPRA = false;
		displaySettings.minPRA = 0;
		displaySettings.showPairsOfMaxPRA = false;
		displaySettings.maxPRA = 100;
	}

	else if (index == 2){
		displaySettings.showAllPairs = false;
		displaySettings.showPairsInStructures = false;
		displaySettings.showPairsInSolutions = false;
		displaySettings.showPairSubset = true;
		displaySettings.showPairsOnHold = false;
		displaySettings.showPairsWithNoCompatibilities = true;
		displaySettings.showPairsOfMinPRA = false;
		displaySettings.minPRA = 0;
		displaySettings.showPairsOfMaxPRA = false;
		displaySettings.maxPRA = 100;
	}

	else if (index == 3){
		displaySettings.showAllPairs = false;
		displaySettings.showPairsInStructures = false;
		displaySettings.showPairsInSolutions = false;
		displaySettings.showPairSubset = true;
		displaySettings.showPairsOnHold = false;
		displaySettings.showPairsWithNoCompatibilities = false;
		displaySettings.showPairsOfMinPRA = false;
		displaySettings.minPRA = 0;
		displaySettings.showPairsOfMaxPRA = false;
		displaySettings.maxPRA = 100;
	}

	else {
		DisplayDialog displayDialog(&displaySettings, this);
		
		if (displayDialog.exec()){
			displaySettings.showAllPairs = displayDialog.allPairsButton->isChecked();
			displaySettings.showPairsInStructures = displayDialog.showStructuresRadioButton->isChecked();
			displaySettings.showPairsInSolutions = displayDialog.showSolutionsRadioButton->isChecked();
			displaySettings.showPairSubset = displayDialog.pairSubsetButton->isChecked();
			displaySettings.showPairsOnHold = displayDialog.showHoldCheckBox->isChecked();
			displaySettings.showPairsWithNoCompatibilities = displayDialog.showIncompatibleCheckBox->isChecked();
			displaySettings.showPairsOfMinPRA = displayDialog.minPRACheckBox->isChecked();
			displaySettings.minPRA = displayDialog.minPRASpinBox->value();
			displaySettings.showPairsOfMaxPRA = displayDialog.maxPRACheckBox->isChecked();
			displaySettings.maxPRA = displayDialog.maxPRASpinBox->value();
		}
	}

	setDisplaySettings(&displaySettings);
}

void MainWindow::cycleTreeCustomMenu(QPoint pos){
	QTreeWidgetItem * item = structureTreeWidget->itemAt(pos);

	QMenu *menu = new QMenu(this);

	KPDGUIStructureWrapper * structureWrapper = dynamic_cast<KPDGUIStructureWrapper *>(item);
	if (structureWrapper){
		KPDGUIStructure * structure = structureWrapper->getStructure();
		menu->addAction(clusterStructureAction);
		
		rightClickStructure = structure;
		//structuresSelected = true;
	}
	if (menu->actions().size() > 0){
		menu->popup(structureTreeWidget->viewport()->mapToGlobal(pos));
	}
}

void MainWindow::solutionTreeCustomMenu(QPoint pos){
	QTreeWidgetItem * item = solutionTreeWidget->itemAt(pos);

	QMenu *menu = new QMenu(this);

	KPDGUIStructureWrapper * structureWrapper = dynamic_cast<KPDGUIStructureWrapper *>(item);
	if (structureWrapper){
		KPDGUIStructure * structure = structureWrapper->getStructure();
		menu->addAction(clusterStructureAction);
		rightClickStructure = structure;
		//structuresSelected = true;
	}
	else {
		KPDGUIStructureSet * structureSet = dynamic_cast<KPDGUIStructureSet *>(item);
		if (structureSet){
			if (structureSet->isSolutionSet()){
				menu->addAction(clusterSolutionAction);
				menu->addAction(removeSolutionAction);
				rightClickStructureSet = structureSet;
				//structuresSelected = true;
			}
		}
	}
	if (menu->actions().size() > 0){
		menu->popup(solutionTreeWidget->viewport()->mapToGlobal(pos));
	}
}


void MainWindow::readSettings()
{

}

void MainWindow::writeSettings()
{

}

bool MainWindow::okToContinue()
{
	if (isWindowModified()) {
		int r = QMessageBox::warning(this, tr("KPD"),
			tr("The document has been modified.\n"
			"Do you want to save your changes?"),
			QMessageBox::Yes | QMessageBox::No
			| QMessageBox::Cancel);
		if (r == QMessageBox::Yes) {
			return save();
		}
		else if (r == QMessageBox::Cancel) {
			return false;
		}
	}
	return true;
}


void MainWindow::clearTable()
{
	for (int i = 0; i < ui->tableWidget->rowCount(); i++){
		ui->tableWidget->item(i, 0)->setData(Qt::EditRole, " ");
	}

	mostRecentNodeID = -1;
}

void MainWindow::runSimulation(){

	QApplication::setOverrideCursor(Qt::WaitCursor);
	QApplication::processEvents();

	QString includedPairList;

	ParamInfoStruct paramInfo;

	paramInfo.maxChainLength = simulParam->getMaxChainLength();
	paramInfo.utilScheme = QString::fromStdString(simulParam->getUtilityScheme());
	if (simulParam->getMUC()){
		paramInfo.optScheme = "MUC";
	}
	else if (simulParam->getMEUC()){
		paramInfo.optScheme = "MEUC";
	}
	else if (simulParam->getMEUS()){
		paramInfo.optScheme = "MEUS";
	}
	else if (simulParam->getSCC()){
		paramInfo.optScheme = "SCC";
	}
	paramInfo.praAdvantage = simulParam->getPRAadvantage();
	paramInfo.reserveOtoO = simulParam->getReserveOtoO();
	paramInfo.checkDP = simulParam->getCheckDP();
	paramInfo.includeCompatiblePairs = simulParam->getIncludeCompatiblePairsFlag();
	paramInfo.includeABBridgeDonors = simulParam->getIncludeABbridgeDonorsFlag();
	paramInfo.numberOfSolutions = simulParam->getTiebreakIterations();

	bool reserveOtoO = simulParam->getReserveOtoO();
	bool checkDP = simulParam->getCheckDP();
	bool includeCompatiblePairs = simulParam->getIncludeCompatiblePairsFlag();

	kpdguiRecord->generateMatrices(reserveOtoO, checkDP, includeCompatiblePairs);

	string optScheme = "";
	if (simulParam->getMUC()){ optScheme = "MUC"; }
	else if (simulParam->getMEUC()){ optScheme = "MEUC"; }
	else if (simulParam->getMEUS()){ optScheme = "MEUS"; }
	else if (simulParam->getSCC()){ optScheme = "SCC"; }

	Graph<Pair> *g = new Graph<Pair>(1, optScheme, simulParam);

	unsigned i = 1;

	while (kpdguiRecord->inTimes.size() >= i && kpdguiRecord->inTimes[i - 1] <= 1){

		g->addVertex(i, kpdguiRecord->pairVector[i]);

		for (int j = 1; j < g->getTotalNumberVertices(); j++){
			if (kpdguiRecord->incidenceMatrix[i][g->getPairID(j)] == true){
				g->addEdge(i, g->getPairID(j));
				g->addEdgeViableTransplant(i, g->getPairID(j), kpdguiRecord->viableTransplantMatrix[i][g->getPairID(j)]);
				g->addEdgeScore(i, g->getPairID(j), kpdguiRecord->scoreMatrix[i][g->getPairID(j)]);
				g->addEdge5yearSurvival(i, g->getPairID(j), kpdguiRecord->survival5yearMatrix[i][g->getPairID(j)]);
				g->addEdge10yearSurvival(i, g->getPairID(j), kpdguiRecord->survival10yearMatrix[i][g->getPairID(j)]);
				g->addEdgeProbability(i, g->getPairID(j), kpdguiRecord->probabilityMatrix[i][g->getPairID(j)]);
				g->addEdgeLabCrossmatch(i, g->getPairID(j), kpdguiRecord->labCrossmatchMatrix[i][g->getPairID(j)]);

			}
			if (kpdguiRecord->incidenceMatrix[g->getPairID(j)][i] == true){
				g->addEdge(g->getPairID(j), i);
				g->addEdgeViableTransplant(g->getPairID(j), i, kpdguiRecord->viableTransplantMatrix[g->getPairID(j)][i]);
				g->addEdgeScore(g->getPairID(j), i, kpdguiRecord->scoreMatrix[g->getPairID(j)][i]);
				g->addEdge5yearSurvival(g->getPairID(j), i, kpdguiRecord->survival5yearMatrix[g->getPairID(j)][i]);
				g->addEdge10yearSurvival(g->getPairID(j), i, kpdguiRecord->survival10yearMatrix[g->getPairID(j)][i]);
				g->addEdgeProbability(g->getPairID(j), i, kpdguiRecord->probabilityMatrix[g->getPairID(j)][i]);
				g->addEdgeLabCrossmatch(g->getPairID(j), i, kpdguiRecord->labCrossmatchMatrix[g->getPairID(j)][i]);
			}
		}
		i++;
	}
	g->setLastMonth();

	int numberOfCycles = 0;
	int numberOfChains = 0;
	int numberOfComponents = 0;

	vector<vector<int> > allStructures;
	if (optScheme == "SCC"){
		allStructures = g->getAllSCC();
	}
	else {
		allStructures = g->getAllEC();
	}

	vector<double> utilValues;
	if (optScheme.compare("MUC") == 0){ utilValues = g->getUForAllEC(); }
	else if (optScheme.compare("MEUC") == 0){ utilValues = g->getEUForAllEC(); }
	else if (optScheme.compare("MEUS") == 0){ utilValues = g->getEUForAllES(); }
	else if (optScheme.compare("SCC") == 0){ utilValues = g->getEUForAllSCC(); }

	g->getOptimalSolution(optScheme);
	vector<int> optimalSolution = g->returnOptimalSolution();
	vector<vector<int> > solutionSet = g->returnSolutionSet();
	vector<double> solutionObjectives = g->returnSolutionObjectives();

	QString simLog = QString::fromStdString(g->getSimLog());
	QString timestamp = QDate::currentDate().toString() + " " + QTime::currentTime().toString();

	/*for (int k = 0; k < solutionTreeWidget->topLevelItemCount(); k++){
		solutionTreeWidget->topLevelItem(k)->setExpanded(false);
	}*/

	KPDGUIStructureSet * structureList = new KPDGUIStructureSet(paramInfo, timestamp, QString::fromStdString(optScheme), includedPairList, simLog, false);
	QVector<KPDGUIStructureSet *> solutionLists;

	int sol = 0;
	for (vector<vector<int> >::iterator it = solutionSet.begin(); it != solutionSet.end(); ++it){
		sol++;
		solutionLists.push_back(new KPDGUIStructureSet(paramInfo, timestamp, QString::fromStdString(optScheme), includedPairList, simLog, true, sol));
	}

	for (int st = 0; st < allStructures.size(); st++){
		QVector<KPDGUINode *> structureNodes;
		bool chain = false;

		for (int index = 0; index < allStructures[st].size(); index++){
			int id = kpdguiRecord->getIDfromIndex(allStructures[st][index] - 1);
			KPDGUINode * node = kpdguiRecord->getNode(id);
			if (node->getType() != 0){
				chain = true;
			}
			structureNodes.push_back(node);
		}

		int idnum;

		if (optScheme.compare("SCC") == 0){
			numberOfComponents++;
			idnum = numberOfComponents;
		}
		else {
			if (chain){
				numberOfChains++;
				idnum = numberOfChains;
			}
			else {
				numberOfCycles++;
				idnum = numberOfCycles;
			}
		}

		KPDGUIStructure * newStructure = new KPDGUIStructure(structureNodes, QString::fromStdString(optScheme), utilValues[st], idnum);

		structureList->push_back(newStructure);
		for (int ss = 0; ss < solutionSet.size(); ss++){
			if (std::find(solutionSet[ss].begin(), solutionSet[ss].end(), st) != solutionSet[ss].end()){
				solutionLists[ss]->push_back(newStructure);
			}
		}
	}

	solutionTreeWidget->collapseAll();

	for (int i = 0; i < listWidget->topLevelItemCount(); i++){
		KPDGUINodeWrapper * wrapper = dynamic_cast<KPDGUINodeWrapper *>(listWidget->topLevelItem(i));
		if (wrapper){
			wrapper->getNode()->resetPopularityInStructures();
		}
	}
	for (int i = 0; i < matchWidget->topLevelItemCount(); i++){
		KPDGUIArrowWrapper * wrapper = dynamic_cast<KPDGUIArrowWrapper *>(listWidget->topLevelItem(i));
		if (wrapper){
			wrapper->getArrow()->resetPopularityInStructures();
		}
	}
	structureList->updatePopularity();
	structureTreeWidget->insertTopLevelItem(0, structureList);
	structureList->setExpanded(true);

	int q = 0;
	foreach(KPDGUIStructureSet * structureSet, solutionLists){
		structureSet->updatePopularity();
		solutionTreeWidget->insertTopLevelItem(q, structureSet);
		structureSet->setExpanded(true);
		q++;
	}

	//ui->consoleWidget->addSolutionInfo(structureList->printReceipt());	

	simulParam->setParametersSet(false);
	ui->tabWidget->setCurrentIndex(3);

	setMatchSortMode(0, true);

	delete g;

	QApplication::restoreOverrideCursor();
	QApplication::processEvents();
}

void MainWindow::clearScreen(){
	kpdguiRecord->clear();
	scene->clear();
	listWidget->clear();
	matchWidget->clear();
	structureTreeWidget->clear();
	solutionTreeWidget->clear();
	ui->consoleWidget->removeAllPairInfo();
	clearTable();
}

void MainWindow::addNode(KPDGUINode * newNode, bool fromSavedFile){

	kpdguiRecord->insert(newNode, fromSavedFile);

	newNode->setText(QString::number(newNode->getInternalID()));

	KPDGUINodeWrapper * wrapper = new KPDGUINodeWrapper(newNode);
	listWidget->addTopLevelItem(wrapper);

	if (!fromSavedFile){
		int h_offset = rand() % 50 - 25;
		int v_offset = rand() % 50 - 25;
		newNode->setPos(QPoint(140 + (120 * (seqNumber % 7)) + h_offset, 160 + (80 * ((seqNumber / 7) % 9)) + v_offset));
	}

	scene->addItem(newNode);
	++seqNumber;

	foreach(KPDGUINode *node, kpdguiRecord->getPairs()){
		if (node->getType() == 0){
			if (kpdguiRecord->isMatch(newNode, node, false, false)){
				addArrow(newNode, node);
			}
		}
		if (newNode->getType() == 0){
			if (kpdguiRecord->isMatch(node, newNode, false, false)){
				addArrow(node, newNode);
			}
		}
	}

	connect(this, SIGNAL(visibilityChanged(DisplaySettingsStruct *)), newNode, SLOT(updateVisibility(DisplaySettingsStruct *)));

}

void MainWindow::addArrow(KPDGUINode * fromNode, KPDGUINode * toNode){
	KPDGUIArrow *link = new KPDGUIArrow(fromNode, toNode);
	connect(this, SIGNAL(visibilityChanged(DisplaySettingsStruct *)), link, SLOT(updateVisibility(DisplaySettingsStruct *)));
	KPDGUIArrowWrapper * wrapper = new KPDGUIArrowWrapper(link);
	matchWidget->addTopLevelItem(wrapper);
	kpdguiRecord->insertArrow(link);
	link->setVisible(false);
	scene->addItem(link);
}

void MainWindow::readPairsFromFile(QString fileName)
{
	QVector<QVector<QVector<QString> > > p_rows;

	QFile iFile(fileName);
	if (!iFile.open(QIODevice::ReadOnly)){}
	QTextStream fileStream(&iFile);

	int i = 0;
	while (!fileStream.atEnd()){
		QString line = fileStream.readLine();
		QStringList lineStream = line.split(',');

		if (i > 0){

			QVector<QVector<QString> > row;
			int flag = 1;
			QVector<QString> field;

			foreach(QString token, lineStream){

				if (token.length() == 0 && flag == 1){
					field.push_back("NULL");
					row.push_back(field);
					field.clear();
				}

				else if (token.indexOf("\"") == 0){
					field.push_back(token.remove(0, 1));
					flag = 0;
				}

				else if (flag == 1){
					field.push_back(token);
					row.push_back(field);
					field.clear();
				}

				else{
					if (token.length()>0){
						if (token.indexOf("\"") == token.length() - 1){ //if equal to \";
							field.push_back(token.remove(token.length() - 1, 1));
							row.push_back(field);
							field.clear();
							flag = 1;
						}

						else {
							field.push_back(token);
						}
					}
				}
			}
			p_rows.push_back(row);
		}
		i++;
	}

	int pairsAdded = 0;

	foreach(QVector<QVector<QString> > row, p_rows){
		bool hold = false;

		if (row.at(1).at(0) != "1"){
			hold = true;
		}

		Donor d;

		d.id = row.at(0).at(0).toInt();
		d.type = row.at(2).at(0).toInt();
		d.name = row.at(9).at(0);
		d.donorid = row.at(10).at(0).toInt();
		d.age = row.at(11).at(0).toInt();

		//Donor Crossmatch Information
		d.donorA.push_back(row.at(20).at(0)); d.donorA.push_back(row.at(21).at(0));
		d.donorB.push_back(row.at(22).at(0)); d.donorB.push_back(row.at(23).at(0));

		if (row.at(24).at(0) == "BW4"){ d.donorBW4 = true; }
		else { d.donorBW4 = false; }
		if (row.at(25).at(0) == "BW6"){ d.donorBW6 = true; }
		else { d.donorBW6 = false; }

		d.donorCW.push_back(row.at(26).at(0)); d.donorCW.push_back(row.at(27).at(0));
		d.donorDQ.push_back(row.at(33).at(0)); d.donorDQ.push_back(row.at(34).at(0)); //d.donorDQ.push_back(row.at(23).at(0)); d.donorDQ.push_back(row.at(24).at(0));
		d.donorDR.push_back(row.at(28).at(0)); d.donorDR.push_back(row.at(29).at(0));

		if (row.at(30).at(0) == "DR51"){ d.donorDR51 = true; }
		else { d.donorDR51 = false; }
		if (row.at(31).at(0) == "DR52"){ d.donorDR52 = true; }
		else { d.donorDR52 = false; }
		if (row.at(32).at(0) == "DR53"){ d.donorDR53 = true; }
		else { d.donorDR53 = false; }

		d.BT = row.at(12).at(0);

		Candidate c;
		c.id = (row.at(0).at(0)).toInt();
		c.name = row.at(5).at(0);
		c.recipid = (row.at(6).at(0)).toInt();
		c.age = row.at(7).at(0).toInt();

		c.BT = row.at(8).at(0);
		if (d.type == 1 && c.BT != "AB"){
			d.type = 0;
		}

		if ((row.at(3).at(0)).toInt() == 1){
			c.sensitized = true;
		}
		else {
			c.sensitized = false;
		}

		int pra = 0;
		QString pratoken;
		QString pra1 = row.at(14).at(0);
		QStringList prass1 = pra1.split('/');

		foreach(QString praToken, prass1){
			int praInt = praToken.toInt();

			if (praInt > pra){
				pra = praInt;
			}
		}

		QString pra2 = row.at(15).at(0);
		QStringList prass2 = pra2.split('/');

		foreach(QString praToken, prass2){
			int praInt = praToken.toInt();

			if (praInt > pra){
				pra = praInt;
			}
		}

		c.pra = pra;

		foreach(QString donorToExclude, row.at(4)){
			if (!donorToExclude.isNull()){
				c.excludedDonors.push_back(donorToExclude.toInt());
			}
		}

		if (c.sensitized == false){
			foreach(QString antibody, row.at(16)){
				if (!antibody.isNull() && antibody != "NONE" && antibody != "NULL" && antibody != "NP"){
					c.antibodies.push_back(antibody);
				}
			}
			foreach(QString antibody, row.at(17)){
				if (!antibody.isNull() && antibody != "NONE" && antibody != "NULL" && antibody != "NP"){
					c.antibodies.push_back(antibody);
				}
			}
		}

		foreach(QString antibody, row.at(18)){
			if (!antibody.isNull() && antibody != "NONE" && antibody != "NULL" && antibody != "NP"){
				c.antibodies.push_back(antibody);
			}
		}

		foreach(QString antibody, row.at(19)){
			if (!antibody.isNull() && antibody != "NONE" && antibody != "NULL" && antibody != "NP"){
				c.antibodies.push_back(antibody);
			}
		}

		c.genderMale = true;
		c.BMI = 25;
		c.weight = 60;
		c.diabetes = false;
		c.race = "White";
		c.prevTrans = false;
		c.TOD = 1.5;
		c.hepC = false;

		d.genderMale = false;
		d.BMI = 25;
		d.weight = 60;

		QString comment = "";

		KPDGUINode * newNode = new KPDGUINode(d, c, comment, hold);

		connect(newNode, SIGNAL(nodeWasClicked(int, bool)), this, SLOT(clickActions(int, bool)));
		connect(newNode, SIGNAL(nodeSelectionChanged(int, bool)), ui->consoleWidget, SLOT(changePairInfo(int, bool)));
		connect(newNode, SIGNAL(nodeHoldStatusChanged(int, bool)), ui->consoleWidget, SLOT(changePairText(int)));
		connect(newNode, SIGNAL(nodeEdited(int)), ui->consoleWidget, SLOT(changePairText(int)));
		connect(newNode, SIGNAL(nodeEdited(int)), this, SLOT(updateTable(int)));

		addNode(newNode, false);
		ui->consoleWidget->addPairInfo(newNode->getInternalID());

		//addPair(newNode);
		pairsAdded++;
	}

	//return pairsAdded;
}

void MainWindow::bringToFront()
{
	++maxZ;

	QList<QGraphicsItem*> items = scene->selectedItems();
	foreach(QGraphicsItem * item, items){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
		if (node)
			node->setZValue(maxZ);
	}
}

void MainWindow::setCurrentFile(const QString &fileName)
{
	curFile = fileName;
	setWindowModified(false);

	QString shownName = tr("Untitled");
	if (!curFile.isEmpty()) {
		shownName = strippedName(curFile);
	}

	this->setWindowTitle(tr("%1[*] - %2").arg(shownName)
		.arg(tr("KPD")));
}

bool MainWindow::loadFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::warning(this, tr("KPD"),
			tr("Cannot read file %1:\n%2.")
			.arg(file.fileName())
			.arg(file.errorString()));

		ui->consoleWidget->addConsoleInfo("> Failed To Load " + fileName);
		return false;
	}
		
	QDataStream in(&file);
	in.setVersion(QDataStream::Qt_5_3);

	qint32 number;
	in >> number;

	if (number != MagicNumber) {
		QMessageBox::warning(this, tr("KPD"), tr("The file is not a KPD file."));
		return false;
	}

	qint32 baselineCode;
	qint32 size;

	in >> baselineCode >> size;

	QApplication::setOverrideCursor(Qt::WaitCursor);
	QApplication::processEvents();

	clearScreen();

	QMap<int, KPDGUINode*> nodeMap;

	for (int i = 0; i < size; i++){		
		KPDGUINode * node = new KPDGUINode();
		in >> *node;
		addNode(node, true);
		connect(node, SIGNAL(nodeWasClicked(int,bool)), this, SLOT(clickActions(int,bool)));
		connect(node, SIGNAL(nodeSelectionChanged(int, bool)), ui->consoleWidget, SLOT(changePairInfo(int, bool)));
		connect(node, SIGNAL(nodeHoldStatusChanged(int, bool)), ui->consoleWidget, SLOT(changePairText(int)));
		connect(node, SIGNAL(nodeEdited(int)), ui->consoleWidget, SLOT(changePairText(int)));
		connect(node, SIGNAL(nodeEdited(int)), this, SLOT(updateTable(int)));


		ui->consoleWidget->addPairInfo(node->getInternalID());

		int internalID = node->getInternalID();
		nodeMap.insert(internalID, node);

		qint32 x;
		qint32 y;

		in >> x >> y;
		node->setPos(x, y);
	}

	qint32 pairSortMode;
	bool pairSortDecreasing;
	qint32 matchSortMode;
	bool matchSortDecreasing;

	in >> pairSortMode >> pairSortDecreasing >> matchSortMode >> matchSortDecreasing;

	setPairSortMode(pairSortMode, pairSortDecreasing);
	setMatchSortMode(matchSortMode, matchSortDecreasing);

	bool showAllPairs;
	bool showPairsInStructures;
	bool showPairsInSolutions;
	bool showPairSubset;
	bool showPairsOnHold;
	bool showPairsWithNoCompatibilities;
	bool showPairsOfMinPRA;
	qint32 minPRA;
	bool showPairsOfMaxPRA;
	qint32 maxPRA;
	qint32 arrowDisplayMode;

	in >> showAllPairs >> showPairsInStructures >> showPairsInSolutions >> showPairSubset >> showPairsOnHold >> showPairsWithNoCompatibilities;
	in >> showPairsOfMinPRA >> minPRA >> showPairsOfMaxPRA >> maxPRA >> arrowDisplayMode;

	DisplaySettingsStruct newDisplaySettings;

	newDisplaySettings.showAllPairs = showAllPairs;
	newDisplaySettings.showPairsInStructures = showPairsInStructures;
	newDisplaySettings.showPairsInSolutions = showPairsInSolutions;
	newDisplaySettings.showPairSubset = showPairSubset;
	newDisplaySettings.showPairsOnHold = showPairsOnHold;
	newDisplaySettings.showPairsWithNoCompatibilities = showPairsWithNoCompatibilities;
	newDisplaySettings.showPairsOfMinPRA = showPairsOfMinPRA;
	newDisplaySettings.minPRA = minPRA;
	newDisplaySettings.showPairsOfMaxPRA = showPairsOfMaxPRA;
	newDisplaySettings.maxPRA = maxPRA;
	newDisplaySettings.arrowDisplayMode = arrowDisplayMode;

	setDisplaySettings(&newDisplaySettings);

	if (showAllPairs){
		ui->pairsComboBox->setCurrentIndex(0);
	}
	else if (showPairSubset && !showPairsWithNoCompatibilities){
		ui->pairsComboBox->setCurrentIndex(1);
	}
	else if (showPairSubset && !showPairsOnHold){
		ui->pairsComboBox->setCurrentIndex(2);
	}
	else if (showPairSubset && !showPairsOnHold && !showPairsWithNoCompatibilities){
		ui->pairsComboBox->setCurrentIndex(3);
	}
	else {
		ui->pairsComboBox->setCurrentIndex(4);
	}
	ui->arrowsComboBox->setCurrentIndex(arrowDisplayMode);

	qint32 zoom;
	in >> zoom;

	ui->zoomSlider->setValue(zoom);

	qint32 solutions;
	in >> solutions;

	QList<QTreeWidgetItem *> solutionItems;
	for (int i = 0; i < solutions; i++){
		KPDGUIStructureSet * solution = new KPDGUIStructureSet();
		in >> *solution;
		int numberOfStructures;
		in >> numberOfStructures;
		////qDebug() << numberOfStructures;
		for (int j = 0; j < numberOfStructures; j++){
			int structureID;
			double utility;
			int numberOfNodes;
			in >> structureID >> utility >> numberOfNodes;
			////qDebug() << structureID;
			////qDebug() << utility;
			////qDebug() << numberOfNodes;
			QVector<KPDGUINode *> nodeList;
			for (int k = 0; k < numberOfNodes; k++){
				int id;
				in >> id;
				////qDebug() << id;
				nodeList.push_back(nodeMap[id]);
			}
			KPDGUIStructure * structure = new KPDGUIStructure(nodeList, solution->getOptScheme(), utility, structureID);
			solution->push_back(structure);
		}
		solution->updatePopularity();
		solutionItems.push_back(solution);
	}
	solutionTreeWidget->addTopLevelItems(solutionItems);
	solutionTreeWidget->collapseAll();

	ui->tabWidget->setCurrentIndex(3);
	
	kpdguiRecord->setBaselineIDCode(baselineCode);

	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File loaded"), 2000);

	ui->consoleWidget->addConsoleInfo("> " + fileName + " Loaded");

	setWindowModified(false);

	QApplication::restoreOverrideCursor();
	QApplication::processEvents();

	return true;
}

bool MainWindow::saveFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly)) {
		QMessageBox::warning(this, tr("KPD"),
			tr("Cannot write file %1:\n%2.")
			.arg(file.fileName())
			.arg(file.errorString()));

		ui->consoleWidget->addConsoleInfo("> Failed To Save " + fileName);
		return false;
	}

	QDataStream out(&file);
	out.setVersion(QDataStream::Qt_5_3);

	out << qint32(MagicNumber);

	out << qint32(kpdguiRecord->getBaselineIDCode());
	out << qint32(kpdguiRecord->size());

	for (int i = 0; i < kpdguiRecord->size(); i++){
		KPDGUINode const& node = *(kpdguiRecord->getNodeFromIndex(i));
		out << node;

		int x = kpdguiRecord->getNodeFromIndex(i)->x();
		int y = kpdguiRecord->getNodeFromIndex(i)->y();

		out << qint32(x) << qint32(y);
	}

	/* pairSortMode = kpdguiRecord->getPairSortMode();
	bool pairSortDecreasing = kpdguiRecord->getPairSortDecreasing();
	int matchSortMode = kpdguiRecord->getMatchSortMode();
	bool matchSortDecreasing = kpdguiRecord->getMatchSortDecreasing();*/

	out << qint32(pairSortMode) << pairSortDecreasing << qint32(matchSortMode) << matchSortDecreasing;

	bool showAllPairs = displaySettings.showAllPairs;
	bool showPairsInStructures = displaySettings.showPairsInStructures;
	bool showPairsInSolutions = displaySettings.showPairsInSolutions;
	bool showPairSubset = displaySettings.showPairSubset;
	bool showPairsOnHold = displaySettings.showPairsOnHold;
	bool showPairsWithNoCompatibilities = displaySettings.showPairsWithNoCompatibilities;
	bool showPairsOfMinPRA = displaySettings.showPairsOfMinPRA;
	int minPRA = displaySettings.minPRA;
	bool showPairsOfMaxPRA = displaySettings.showPairsOfMaxPRA;
	int maxPRA = displaySettings.maxPRA;
	int arrowDisplayMode = displaySettings.arrowDisplayMode;

	out << showAllPairs << showPairsInStructures << showPairsInSolutions << showPairSubset << showPairsOnHold << showPairsWithNoCompatibilities;
	out << showPairsOfMinPRA << qint32(minPRA) << showPairsOfMaxPRA << qint32(maxPRA) << qint32(arrowDisplayMode);

	int zoom = ui->zoomSlider->value();
	out << qint32(zoom);
	
	int solutions = solutionTreeWidget->topLevelItemCount();
	out << qint32(solutions);
	
	for (int i = 0; i < solutions; i++){
		KPDGUIStructureSet * solutionPtr = dynamic_cast<KPDGUIStructureSet*>(solutionTreeWidget->topLevelItem(i));
		if (solutionPtr){
			KPDGUIStructureSet const& solution = *solutionPtr;
			out << solution;
			out << qint32(solutionPtr->size());
			////qDebug() << "Size: " << solutionPtr->size();
			for (int j = 0; j < solutionPtr->childCount(); j++){
				QTreeWidgetItem * item = solutionPtr->child(j);
				for (int k = 0; k < item->childCount(); k++){
					KPDGUIStructureWrapper * structure = dynamic_cast<KPDGUIStructureWrapper *>(item->child(k));
					if (structure){
						//out << item2->childCount();
						out << qint32(structure->getStructure()->getID());
						////qDebug() << "Structure ID: " << structure->getStructure()->getID();
						out << qreal(structure->getStructure()->getUtility());
						////qDebug() << "Structure Utility: " << structure->getStructure()->getUtility();
						out << qint32(structure->childCount());
						////qDebug() << "# of Nodes: " << structure->childCount();
						for (int l = 0; l < structure->childCount(); l++){
							KPDGUINodeWrapper* node = dynamic_cast<KPDGUINodeWrapper*>(structure->child(l));
							if (node){
								out << qint32(node->getNode()->getInternalID());
								////qDebug() << "ID: " << node->getNode()->getInternalID();
							}
						}
					}
				}
			}
		}
	}
	
	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File saved"), 2000);
	ui->consoleWidget->addConsoleInfo("> " + fileName + " Saved");

	return true;
}

QString MainWindow::strippedName(const QString &fullFileName)
{
	return QFileInfo(fullFileName).fileName();
}

void MainWindow::createAdditionalActions(){
	clusterStructureAction = new QAction("Cluster Structure", this);
	connect(clusterStructureAction, SIGNAL(triggered()), this, SLOT(clusterStructure()));

	clusterSolutionAction = new QAction("Cluster Solution", this);
	connect(clusterSolutionAction, SIGNAL(triggered()), this, SLOT(clusterSolution()));

	removeSolutionAction = new QAction("Remove Solution", this);
	connect(removeSolutionAction, SIGNAL(triggered()), this, SLOT(removeSolution()));
}


