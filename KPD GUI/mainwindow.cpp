#include <QtGui>
#include <QtWidgets>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	//
    ui->setupUi(this);

	initializeParameters();	
	setUpKPDObjects();
	setUpLists();
	setUpActions();
	setUpMenu();
	setUpToolbar();
	
	ui->consoleWidget->addConsoleInfo("Welcome to KPDGUI - " + QDate::currentDate().toString() + " " + QTime::currentTime().toString() + "\n");	
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeParameters(){
	
	//Parameters
	maxZ = 0;
	seqNumber = 0;
	prevSliderPos = 0;
	mostRecentNodeID = -1;
	setCurrentFile("");

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

	displaySettings.arrowDisplayMode = WITHIN_SELECTION;

	//Sort Modes
	pairSortMode = 0;
	pairSortDecreasing = false;
	matchSortMode = 0;
	matchSortDecreasing = false;
}

void MainWindow::setUpKPDObjects(){

	//GraphicsScene
	kpdguiScene = new KPDGUIGraphicsScene();
	ui->graphicsView->setScene(kpdguiScene);

	connect(kpdguiScene, SIGNAL(deleteNode(int)), this, SLOT(deleteNode(int)));
	connect(kpdguiScene, SIGNAL(screenChanged()), this, SLOT(updateVisibility()));
	connect(kpdguiScene, SIGNAL(mouseReleased()), this, SLOT(checkSelections()));

	connect(ui->graphicsView, SIGNAL(zoomIn()), this, SLOT(zoomIn()));
	connect(ui->graphicsView, SIGNAL(zoomOut()), this, SLOT(zoomOut()));

	//Simulation Parameters
	kpdguiParameters = new KPDGUISimulParam();

	//Pair Record
	kpdguiRecord = new KPDGUIRecord();
}

void MainWindow::setUpLists(){

	//Pair List
	pairListWidget = new QTreeWidget();
	pairListWidget->setHeaderHidden(true);
	pairListWidget->setSelectionMode(QAbstractItemView::MultiSelection);
	pairListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	connect(pairListWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(newPairListSelectionActions(QTreeWidgetItem*)));
	ui->tabWidget->addTab(pairListWidget, "Pairs/Ads");

	//Match List
	matchListWidget = new QTreeWidget();
	matchListWidget->setHeaderHidden(true);
	matchListWidget->setSelectionMode(QAbstractItemView::MultiSelection);
	matchListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	connect(matchListWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(newMatchListSelectionActions(QTreeWidgetItem*)));
	ui->tabWidget->addTab(matchListWidget, "Matches");

	//Structure Tree
	structureTreeWidget = new QTreeWidget();
	structureTreeWidget->setHeaderHidden(true);
	structureTreeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	structureTreeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	structureTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(structureTreeWidget, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this, SLOT(newTreeSelectionActions(QTreeWidgetItem*)));
	connect(structureTreeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(structureTreeCustomMenu(QPoint)));
	ui->tabWidget->addTab(structureTreeWidget, "Structures");

	//Solution Tree
	solutionTreeWidget = new QTreeWidget();
	solutionTreeWidget->setHeaderHidden(true);
	solutionTreeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	solutionTreeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	solutionTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(solutionTreeWidget, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this, SLOT(newTreeSelectionActions(QTreeWidgetItem*)));
	connect(solutionTreeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(solutionTreeCustomMenu(QPoint)));
	ui->tabWidget->addTab(solutionTreeWidget, "Solutions");
}


void MainWindow::setUpActions(){
	
	clusterStructureAction = new QAction("Cluster Structure", this);
	connect(clusterStructureAction, SIGNAL(triggered()), this, SLOT(clusterStructure()));

	clusterSolutionAction = new QAction("Cluster Solution", this);
	connect(clusterSolutionAction, SIGNAL(triggered()), this, SLOT(clusterSolution()));

	removeSolutionAction = new QAction("Remove Solution", this);
	connect(removeSolutionAction, SIGNAL(triggered()), this, SLOT(removeSolution()));
}


void MainWindow::setUpMenu(){
	
	displayArrowsActionGroup = new QActionGroup(this);
	displayArrowsActionGroup->addAction(ui->actionDisplay_Compatibilities_Within_Selection);
	displayArrowsActionGroup->addAction(ui->actionDisplay_Selected_Compatibilities);
	displayArrowsActionGroup->addAction(ui->actionDisplay_Selected_Compatible_Donors);
	displayArrowsActionGroup->addAction(ui->actionDisplay_Selected_Compatible_Recipients);
	displayArrowsActionGroup->addAction(ui->actionDisplay_All_Compatibilities);
	displayArrowsActionGroup->addAction(ui->actionDisplay_No_Compatibilities);
}

void MainWindow::setUpToolbar(){
	
	zoomSlider = new QSlider();
	zoomSlider->setMinimumSize(QSize(84, 24));
	zoomSlider->setMaximumSize(QSize(84, 24));
	zoomSlider->setMinimum(-3);
	zoomSlider->setMaximum(3);
	zoomSlider->setValue(0);
	zoomSlider->setOrientation(Qt::Horizontal);
	zoomSlider->setTickPosition(QSlider::TicksBelow);
	QObject::connect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoom(int)));

	ui->toolBar->insertWidget(ui->actionZoom_In, zoomSlider);
	ui->actionMouse_Tool->setChecked(true);
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

			statusBar()->showMessage("Opened File: " + fileName, 2000);
			ui->consoleWidget->addConsoleInfo("> Opened File: " + fileName + "\n");			
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

		double recipHeight = dialog.recipHeightSpinBox->value();
		double recipWeight = dialog.recipWeightSpinBox->value();
		c.BMI = recipWeight / recipHeight / recipHeight;
		c.weight = recipWeight;
		c.diabetes = dialog.recipDiabetesCheckBox->isChecked();
		QString recipGender = dialog.recipGenderComboBox->currentText();
		if (recipGender == "Male"){ c.genderMale = true; }
		else { c.genderMale = false; }
		c.race = dialog.recipRaceComboBox->currentText();
		c.prevTrans = dialog.recipPrevTransCheckBox->isChecked();
		c.TOD = dialog.recipTODSpinBox->value();
		c.hepC = dialog.recipHepCCheckBox->isChecked();

		double donorHeight = dialog.donorHeightSpinBox->value();
		double donorWeight = dialog.donorWeightSpinBox->value();
		d.BMI = donorWeight / donorHeight / donorHeight;
		d.weight = donorWeight;
		QString donorGender = dialog.donorGenderComboBox->currentText();
		if (donorGender == "Male"){ d.genderMale = true; }
		else { d.genderMale = false; }

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
		d.type = KPDPairType::PAIR;

		QString comment = dialog.commentTextEdit->toPlainText();

		KPDGUINode * newPair = new KPDGUINode(d, c, comment);
		connect(newPair, SIGNAL(nodeWasClicked(int, bool)), this, SLOT(clickActions(int, bool)));
		//connect(newPair, SIGNAL(nodeSelectionChanged(int, bool)), ui->consoleWidget, SLOT(changePairInfo(int, bool)));
		//connect(newPair, SIGNAL(nodeHoldStatusChanged(int, bool)), ui->consoleWidget, SLOT(changePairText(int)));
		//connect(newPair, SIGNAL(nodeEdited(int)), ui->consoleWidget, SLOT(changePairText(int)));
		connect(newPair, SIGNAL(nodeEdited(int)), this, SLOT(updateTable(int)));

		addNode(newPair, false);

		int pairID = newPair->getInternalID();
		//ui->consoleWidget->addPairInfo(pairID);

		kpdguiScene->clearSelection();
		newPair->setSelected(true);
		changeFocus(pairID);
		//ui->consoleWidget->focusOnPairScreen(pairID);

		statusBar()->showMessage("Added Pair", 2000);
		ui->consoleWidget->addConsoleInfo("> Added New Pair: " + d.name + ", " + c.name + " (" + QString::number(pairID) + ")");

		emit visibilityChanged(&displaySettings);
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
		ad.BMI = donorWeight / donorHeight / donorHeight;
		ad.weight = donorWeight;
		QString donorGender = dialog.donorGenderComboBox->currentText();
		if (donorGender == "Male"){ ad.genderMale = true; }
		else { ad.genderMale = false; }

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

		ad.type = KPDPairType::AD;

		QString comment = dialog.commentTextEdit->toPlainText();

		KPDGUINode * newAD = new KPDGUINode(ad, dummy, comment);
		connect(newAD, SIGNAL(nodeWasClicked(int, bool)), this, SLOT(clickActions(int, bool)));
		//connect(newAD, SIGNAL(nodeSelectionChanged(int, bool)), ui->consoleWidget, SLOT(changePairInfo(int, bool)));
		//connect(newAD, SIGNAL(nodeHoldStatusChanged(int, bool)), ui->consoleWidget, SLOT(changePairText(int)));
		//connect(newAD, SIGNAL(nodeEdited(int)), ui->consoleWidget, SLOT(changePairText(int)));
		connect(newAD, SIGNAL(nodeEdited(int)), this, SLOT(updateTable(int)));

		addNode(newAD, false);

		int pairID = newAD->getInternalID();
		//ui->consoleWidget->addPairInfo(pairID);

		kpdguiScene->clearSelection();
		newAD->setSelected(true);
		changeFocus(pairID);
		//ui->consoleWidget->focusOnPairScreen(pairID);

		statusBar()->showMessage("Added AD", 2000);
		ui->consoleWidget->addConsoleInfo("> Added New AD: " + ad.name + " (" + QString::number(pairID) + ")");

		emit visibilityChanged(&displaySettings);
		setWindowModified(true);
	}
}

void MainWindow::loadPairs()
{
	ReadFileDialog readFileDialog(this);

	if (readFileDialog.exec()) {
		QApplication::setOverrideCursor(Qt::WaitCursor);
		QApplication::processEvents();

		kpdguiScene->clearSelection();

		QString str = readFileDialog.pairFileLineEdit->text();

		readPairsFromFile(str);

		QApplication::restoreOverrideCursor();
		QApplication::processEvents();

		QStringList splitstr = str.split("\\");
		statusBar()->showMessage("Loaded Pairs From File: " + splitstr.last(), 2000);
		ui->consoleWidget->addConsoleInfo("> Loaded Pairs From " + splitstr.last());

		setWindowModified(true);
		emit visibilityChanged(&displaySettings);
		kpdguiParameters->setParametersSet(false);

	}
}

void MainWindow::exitProgram()
{
	qApp->closeAllWindows();
}

void MainWindow::run()
{
	bool proceed = true;

	if (!kpdguiParameters->getParametersSet()) {
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

bool MainWindow::setSimParameters()
{
	ParamInfoStruct oldParamInfo;
	oldParamInfo.optScheme = kpdguiParameters->getOptimizationScheme();
	oldParamInfo.utilityScheme = kpdguiParameters->getUtilityScheme();
	oldParamInfo.maxChainLength = kpdguiParameters->getMaxChainLength();

	oldParamInfo.pairFailureRate = kpdguiParameters->getPairFailureRate();
	oldParamInfo.adFailureRate = kpdguiParameters->getADFailureRate();
	oldParamInfo.exogenousFailureRate = kpdguiParameters->getExogenousFailureRate();

	oldParamInfo.addAdvantageToHighPRACandidates = kpdguiParameters->getAddAdvantageToHighPRACandidates();
	oldParamInfo.praAdvantageCutoff = kpdguiParameters->getPRAAdvantageCutoff();
	oldParamInfo.praAdvantageValue = kpdguiParameters->getPRAAdvantageValue();

	oldParamInfo.numberOfSolutions = kpdguiParameters->getNumberOfSolutions();

	oldParamInfo.chainStorage = kpdguiParameters->getChainStorage();
	oldParamInfo.reserveODonorsForOCandidates = kpdguiParameters->getReserveODonorsForOCandidates();
	oldParamInfo.checkDP = kpdguiParameters->getCheckDP();
	oldParamInfo.includeCompatiblePairs = kpdguiParameters->getIncludeCompatiblePairs();
	oldParamInfo.excludeABDonorsFromSimulation = kpdguiParameters->getExcludeABDonorsFromSimulation();
	oldParamInfo.allowABBridgeDonors = kpdguiParameters->getAllowABbridgeDonors();

	SimParamDialog simParamDialog(oldParamInfo, this);

	if (simParamDialog.exec()) {
		ParamInfoStruct newParamInfo;
		newParamInfo.optScheme = KPDFunctions::dialogToOptScheme(simParamDialog.optComboBox->currentText());
		newParamInfo.utilityScheme = KPDFunctions::dialogToUtilityScheme(simParamDialog.utilComboBox->currentText());
		newParamInfo.maxChainLength = simParamDialog.chainLengthSpinBox->value();

		newParamInfo.pairFailureRate = simParamDialog.pairFailureRateSpinBox->value();
		newParamInfo.adFailureRate = simParamDialog.adFailureRateSpinBox->value();
		newParamInfo.exogenousFailureRate = simParamDialog.exogenousFailureRateSpinBox->value();

		newParamInfo.addAdvantageToHighPRACandidates = simParamDialog.praBox->isChecked();
		newParamInfo.praAdvantageCutoff = simParamDialog.praCutoffSpinBox->value();
		newParamInfo.praAdvantageValue = simParamDialog.praAdvantageSpinBox->value();

		newParamInfo.numberOfSolutions = simParamDialog.solutionsSpinBox->value();

		QString chainStorage = simParamDialog.chainStorageComboBox->currentText();
		if (chainStorage == "As They Are Found"){
			newParamInfo.chainStorage = "NONE";
		}
		else if (chainStorage == "First"){
			newParamInfo.chainStorage = "FIRST";
		}
		else if (chainStorage == "Last"){
			newParamInfo.chainStorage = "LAST";
		}

		newParamInfo.reserveODonorsForOCandidates = simParamDialog.reserveOtoOBox->isChecked();
		newParamInfo.checkDP = simParamDialog.checkDPBox->isChecked();
		newParamInfo.includeCompatiblePairs = simParamDialog.compatibleBox->isChecked();
		newParamInfo.excludeABDonorsFromSimulation = simParamDialog.excludeABDonorsBox->isChecked();
		newParamInfo.allowABBridgeDonors = simParamDialog.allowABBridgeBox->isChecked();

		kpdguiParameters->processParams(newParamInfo);

		statusBar()->showMessage("Set New Parameters", 2000);
		ui->consoleWidget->addConsoleInfo(tr("> Set New Parameters"));

		kpdguiParameters->setParametersSet(true);

		return true;
	}

	return false;
}

void MainWindow::clearSolutions(){
	int r = QMessageBox::warning(this, tr("KPD"),
		tr("Remove Solutions?"),
		QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	if (r == QMessageBox::Yes) {
		int items = solutionTreeWidget->topLevelItemCount();
		for (int i = 0; i < items; i++){
			QTreeWidgetItem * solutionToDelete = solutionTreeWidget->takeTopLevelItem(0);
			delete solutionToDelete;
		}

		kpdguiScene->clearSelection();

		sort();

		setWindowModified(true);
	}
}

void MainWindow::changePairViewMode()
{
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

	setDisplaySettings(&displaySettings);
}

void MainWindow::changeArrowViewMode_Within()
{
	displaySettings.arrowDisplayMode = WITHIN_SELECTION;
	setDisplaySettings(&displaySettings);
}

void MainWindow::changeArrowViewMode_SelectedComps()
{
	displaySettings.arrowDisplayMode = SELECTED_COMPATIBILITIES;
	setDisplaySettings(&displaySettings);
}

void MainWindow::changeArrowViewMode_Donors()
{
	displaySettings.arrowDisplayMode = COMPATIBLE_DONORS;
	setDisplaySettings(&displaySettings);
}

void MainWindow::changeArrowViewMode_Recips()
{
	displaySettings.arrowDisplayMode = COMPATIBLE_RECIPIENTS;
	setDisplaySettings(&displaySettings);
}

void MainWindow::changeArrowViewMode_All()
{
	displaySettings.arrowDisplayMode = ALL_COMPATIBILITIES;
	setDisplaySettings(&displaySettings);
}

void MainWindow::changeArrowViewMode_None()
{
	displaySettings.arrowDisplayMode = NO_COMPATIBILITIES;
	setDisplaySettings(&displaySettings);
}

void MainWindow::zoomIn(){
	int position = zoomSlider->value();

	if (position < 3){
		position++;
		zoomSlider->setValue(position);
	}
}

void MainWindow::zoomOut(){
	int position = zoomSlider->value();

	if (position > -3){
		position--;
		zoomSlider->setValue(position);
	}
}

void MainWindow::zoom(int tick){

	double scaleFactor = 1.15;
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

void MainWindow::changeToMouseMode(){
	ui->actionHand_Tool->setChecked(false);
	ui->actionMouse_Tool->setChecked(true);

	ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
	ui->graphicsView->setCursor(Qt::ArrowCursor);
	ui->graphicsView->changeMode(0);
}

void MainWindow::changeToHandMode(){
	ui->actionHand_Tool->setChecked(true);
	ui->actionMouse_Tool->setChecked(false);

	ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
	ui->graphicsView->setCursor(Qt::OpenHandCursor);
	ui->graphicsView->changeMode(1);
}

void MainWindow::sortLists(){

	SortDialog sortDialog(pairSortMode, pairSortDecreasing, matchSortMode, matchSortDecreasing, this);

	if (sortDialog.exec()) {
		QApplication::setOverrideCursor(Qt::WaitCursor);
		QApplication::processEvents();

		int pairSortSetting = sortDialog.pairsComboBox->currentIndex();
		bool pairDecreasing = sortDialog.pairsDecreasingCheckBox->isChecked();
		int matchSortSetting = sortDialog.matchesComboBox->currentIndex();
		bool matchDecreasing = sortDialog.matchesDecreasingCheckBox->isChecked();

		sort();

		QApplication::restoreOverrideCursor();
		QApplication::processEvents();

		setWindowModified(true);
	}
}

void MainWindow::about()
{
	QMessageBox::about(this, tr("About KPDGUI"),
		tr("<h2>KPDGUI 1.1</h2>"
		"<p>Copyright &copy; 2014."
		"<p>Author: Mathieu Bray"));

	ui->consoleWidget->addConsoleInfo(tr("> Opened About Screen"));
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
		else if (!(i == mostRecentNodeID)){
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

		updateVisibility();
	}

}

void MainWindow::newTreeSelectionActions(QTreeWidgetItem* item)
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	QApplication::processEvents();

	bool selected = item->isSelected();

	ui->consoleWidget->removeSolutionScreen();
	if (selectedStructures.size() > 0){
		foreach(KPDGUIStructure * structure, selectedStructures){
			structure->undoHighlights();
		}
	}
	selectedStructures.clear();

	if (selected){
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
		if (level == 0){
			KPDGUIStructureSet * structureSet = dynamic_cast<KPDGUIStructureSet *>(item);
			if (structureSet){
				kpdguiScene->clearSelection();
				structureSet->selectStructures();
				clearTable();
				updateVisibility();
				structureSet->highlight();

				foreach(KPDGUIStructure * structure, structureSet->getStructures()){
					selectedStructures.push_back(structure);
				}
				ui->consoleWidget->addSolutionInfo(structureSet->getConsoleString());
				ui->consoleWidget->focusOnSolutionScreen();
			}
		}
		else if (level == 2) {
			KPDGUIStructureWrapper * structureWrapper = dynamic_cast<KPDGUIStructureWrapper *>(item);
			if (structureWrapper){
				KPDGUIStructure * structure = structureWrapper->getStructure();
				kpdguiScene->clearSelection();
				structure->select();
				clearTable();
				updateVisibility();
				structure->highlight();
				selectedStructures.push_back(structure);
				ui->graphicsView->centerOn(QPoint(structure->centerX(), structure->centerY()));
			}
		}
		else if (level == 3){
			KPDGUINodeWrapper * nodeWrapper = dynamic_cast<KPDGUINodeWrapper *>(item);
			if (nodeWrapper){
				KPDGUINode * node = nodeWrapper->getNode();
				kpdguiScene->clearSelection();
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
			kpdguiScene->clearSelection();
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
		kpdguiScene->clearSelection();
		updateVisibility();
		clearTable();
	}

	QApplication::restoreOverrideCursor();
	QApplication::processEvents();
}

void MainWindow::structureTreeCustomMenu(QPoint pos){
	QTreeWidgetItem * item = structureTreeWidget->itemAt(pos);

	QMenu *menu = new QMenu(this);

	KPDGUIStructureWrapper * structureWrapper = dynamic_cast<KPDGUIStructureWrapper *>(item);
	if (structureWrapper){
		KPDGUIStructure * structure = structureWrapper->getStructure();
		menu->addAction(clusterStructureAction);

		rightClickStructure = structure;
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
	}
	else {
		KPDGUIStructureSet * structureSet = dynamic_cast<KPDGUIStructureSet *>(item);
		if (structureSet){
			if (structureSet->isSolutionSet()){
				menu->addAction(clusterSolutionAction);
				menu->addAction(removeSolutionAction);
				rightClickStructureSet = structureSet;
			}
		}
	}
	if (menu->actions().size() > 0){
		menu->popup(solutionTreeWidget->viewport()->mapToGlobal(pos));
	}
}

void MainWindow::deleteNode(int i)
{
	KPDGUINode * nodeToDelete = kpdguiRecord->getNode(i);
	int id = nodeToDelete->getInternalID();
	nodeToDelete->setSelected(false);
	
	QApplication::setOverrideCursor(Qt::WaitCursor);
	QApplication::processEvents();

	QSet<KPDGUINodeWrapper *> nodeWrappersToDelete;
	QSet<KPDGUIArrowWrapper *> arrowWrappersToDelete;
	QSet<KPDGUIStructureWrapper *> structureWrappersToDelete;
	QSet<KPDGUIStructure *> structuresToDelete;

	for (int i = 0; i < pairListWidget->topLevelItemCount(); i++){
		KPDGUINodeWrapper * nodeWrapper = dynamic_cast<KPDGUINodeWrapper *>(pairListWidget->topLevelItem(i));
		if (nodeWrapper){
			if (nodeWrapper->getNode()->getInternalID() == id){
				nodeWrappersToDelete.insert(nodeWrapper);
			}
		}
	}

	for (int i = 0; i < matchListWidget->topLevelItemCount(); i++){
		KPDGUIArrowWrapper * arrowWrapper = dynamic_cast<KPDGUIArrowWrapper *>(matchListWidget->topLevelItem(i));
		if (arrowWrapper){
			if (arrowWrapper->getArrow()->startItem()->getInternalID() == id){
				arrowWrappersToDelete.insert(arrowWrapper);
			}
			else if (arrowWrapper->getArrow()->endItem()->getInternalID() == id){
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

	if (nodeToDelete->getType() == KPDPairType::AD){
		ui->consoleWidget->addConsoleInfo("> Deleted AD: " + nodeToDelete->getDonorName() + " (" + QString::number(id) + ")");
	}
	else {
		ui->consoleWidget->addConsoleInfo("> Deleted Pair: " + nodeToDelete->getDonorName() + ", " + nodeToDelete->getRecipName() + " (" + QString::number(id) + ")");
	}
	//ui->consoleWidget->deletePairInfo(id);

	kpdguiRecord->deleteNodeFromRecord(id);

	delete nodeToDelete;

	setWindowModified(true);

	QApplication::restoreOverrideCursor();
	QApplication::processEvents();
}

void MainWindow::clickActions(int i, bool selected)
{
	if (selected){
		updateTable(i);
		//ui->consoleWidget->focusOnPairScreen(i);
	}
	else if (!(i==mostRecentNodeID)){
		clearTable();
	}
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
		kpdguiScene->clearSelection();

		sort();

		setWindowModified(true);
	}
}

void MainWindow::checkSelections(){
	if (kpdguiScene->selectedItems().size() == 0){
		clearTable();
	}

	//Bring to front
	++maxZ;

	QList<QGraphicsItem*> items = kpdguiScene->selectedItems();
	foreach(QGraphicsItem * item, items){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
		if (node)
			node->setZValue(maxZ);
	}

	updateVisibility();
}

void MainWindow::updateTable(int i)
{
	KPDGUINode * node = kpdguiRecord->getNode(i);

	ui->tableWidget->item(0, 0)->setData(Qt::EditRole, QString::number(i));
	ui->tableWidget->item(1, 0)->setData(Qt::EditRole, node->getDonorName());
	ui->tableWidget->item(2, 0)->setData(Qt::EditRole, QString::number(node->getDonorAge()));
	ui->tableWidget->item(3, 0)->setData(Qt::EditRole, node->getDonorBT());

	if (node->getType() == PAIR){
		ui->tableWidget->item(4, 0)->setData(Qt::EditRole, node->getRecipName());
		ui->tableWidget->item(5, 0)->setData(Qt::EditRole, QString::number(node->getRecipAge()));
		ui->tableWidget->item(6, 0)->setData(Qt::EditRole, node->getRecipBT());
		ui->tableWidget->item(7, 0)->setData(Qt::EditRole, QString::number(node->getRecipPRA()));
	}
	else if (node->getType() == AD){
		ui->tableWidget->item(4, 0)->setData(Qt::EditRole, " ");
		ui->tableWidget->item(5, 0)->setData(Qt::EditRole, " ");
		ui->tableWidget->item(6, 0)->setData(Qt::EditRole, " ");
		ui->tableWidget->item(7, 0)->setData(Qt::EditRole, " ");
	}
	
	mostRecentNodeID = i;	
}

void MainWindow::updateVisibility(){
	emit visibilityChanged(&displaySettings);
}

void MainWindow::updateStatusBar()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (okToContinue()) {
		event->accept();
	}
	else {
		event->ignore();
	}
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
	//qDebug() << "LOAD: Number" << number;

	if (number != MagicNumber) {
		QMessageBox::warning(this, tr("KPD"), tr("The file is not a KPD file."));
		return false;
	}

	qint32 baselineCode;
	qint32 size;

	in >> baselineCode >> size;
	//qDebug()  << "LOAD: Baseline Code/Size" << baselineCode << size;

	QApplication::setOverrideCursor(Qt::WaitCursor);
	QApplication::processEvents();

	//Clear Screen
	kpdguiRecord->clear();
	kpdguiScene->clear();
	pairListWidget->clear();
	matchListWidget->clear();
	structureTreeWidget->clear();
	solutionTreeWidget->clear();
	ui->consoleWidget->removeAllPairInfo();
	clearTable();

	QMap<int, KPDGUINode*> nodeMap;

	for (int i = 0; i < size; i++){
		//qDebug() << i;
		KPDGUINode * node = new KPDGUINode();
		in >> *node;
		addNode(node, true);
		connect(node, SIGNAL(nodeWasClicked(int, bool)), this, SLOT(clickActions(int, bool)));
		//connect(node, SIGNAL(nodeSelectionChanged(int, bool)), ui->consoleWidget, SLOT(changePairInfo(int, bool)));
		//connect(node, SIGNAL(nodeHoldStatusChanged(int, bool)), ui->consoleWidget, SLOT(changePairText(int)));
		//connect(node, SIGNAL(nodeEdited(int)), ui->consoleWidget, SLOT(changePairText(int)));
		connect(node, SIGNAL(nodeEdited(int)), this, SLOT(updateTable(int)));


		//ui->consoleWidget->addPairInfo(node->getInternalID());

		int internalID = node->getInternalID();
		nodeMap.insert(internalID, node);

		qint32 x;
		qint32 y;

		in >> x >> y;
		//qDebug() << "LOAD: X/Y" <<  x << y;
		node->setPos(x, y);
	}

	qint32 pairSortMode;
	bool pairSortDecreasing;
	qint32 matchSortMode;
	bool matchSortDecreasing;

	in >> pairSortMode >> pairSortDecreasing >> matchSortMode >> matchSortDecreasing;
	//qDebug() << "LOAD: Pair/Match Sort" << pairSortMode << pairSortDecreasing << matchSortMode << matchSortDecreasing;

	sort();

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
	//qDebug() << "LOAD: Visibility" << showAllPairs << showPairsInStructures << showPairsInSolutions << showPairSubset << showPairsOnHold << showPairsWithNoCompatibilities;
	in >> showPairsOfMinPRA >> minPRA >> showPairsOfMaxPRA >> maxPRA >> arrowDisplayMode;
	//qDebug() << "LOAD: Visibility" << showPairsOfMinPRA << minPRA << showPairsOfMaxPRA << maxPRA << arrowDisplayMode;
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
	newDisplaySettings.arrowDisplayMode = KPDFunctions::intToArrowDisplayMode(arrowDisplayMode);

	qint32 zoom;
	in >> zoom;
	qDebug() << "LOAD: Zoom" << zoom;


	zoomSlider->setValue(zoom);

	qint32 solutions;
	in >> solutions;
	qDebug() << "LOAD: Solutions" << solutions;

	QList<QTreeWidgetItem *> solutionItems;
	for (int i = 0; i < solutions; i++){
		KPDGUIStructureSet * solution = new KPDGUIStructureSet();
		in >> *solution;
		int numberOfStructures;
		in >> numberOfStructures;
		qDebug() << "LOAD: # Structures" << numberOfStructures;
		for (int j = 0; j < numberOfStructures; j++){
			int structureID;
			double utility;
			int numberOfNodes;
			in >> structureID >> utility >> numberOfNodes;
			qDebug() << "LOAD: Structure Info" << structureID << utility << numberOfNodes;
			QVector<KPDGUINode *> nodeList;
			for (int k = 0; k < numberOfNodes; k++){
				int id;
				in >> id;
				qDebug() << "LOAD: ID" << id;
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

	setDisplaySettings(&newDisplaySettings);
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

	//qDebug() << "SAVE: Number" << qint32(MagicNumber);
	out << qint32(MagicNumber);

	//qDebug() << "SAVE: Baseline ID Code/Size" << qint32(kpdguiRecord->getBaselineIDCode()) << qint32(kpdguiRecord->size());
	out << qint32(kpdguiRecord->getBaselineIDCode());
	out << qint32(kpdguiRecord->size());

	for (int i = 0; i < kpdguiRecord->size(); i++){
		KPDGUINode const& node = *(kpdguiRecord->getNodeFromIndex(i));
		out << node;

		int x = kpdguiRecord->getNodeFromIndex(i)->x();
		int y = kpdguiRecord->getNodeFromIndex(i)->y();

		//qDebug() << "SAVE: X/Y" << qint32(x) << qint32(y);
		out << qint32(x) << qint32(y);
	}

	//qDebug() << "SAVE: Pair/Match Sort Mode" << qint32(pairSortMode) << pairSortDecreasing << qint32(matchSortMode) << matchSortDecreasing;
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
	KPDArrowDisplayMode arrowDisplayMode = displaySettings.arrowDisplayMode;

	//qDebug() << "SAVE: Visibility" << showAllPairs << showPairsInStructures << showPairsInSolutions << showPairSubset << showPairsOnHold << showPairsWithNoCompatibilities;
	out << showAllPairs << showPairsInStructures << showPairsInSolutions << showPairSubset << showPairsOnHold << showPairsWithNoCompatibilities;
	//qDebug() << "SAVE: Visibility" << showPairsOfMinPRA << qint32(minPRA) << showPairsOfMaxPRA << qint32(maxPRA) << qint32(arrowDisplayMode);
	out << showPairsOfMinPRA << qint32(minPRA) << showPairsOfMaxPRA << qint32(maxPRA) << qint32(KPDFunctions::arrowDisplayModeToInt(arrowDisplayMode));

	int zoom = zoomSlider->value();
	qDebug() << "SAVE: Zoom" << qint32(zoom);
	out << qint32(zoom);

	int solutions = solutionTreeWidget->topLevelItemCount();
	qDebug() << "SAVE: Solutions" << qint32(solutions);
	out << qint32(solutions);

	for (int i = 0; i < solutions; i++){
		KPDGUIStructureSet * solutionPtr = dynamic_cast<KPDGUIStructureSet*>(solutionTreeWidget->topLevelItem(i));
		if (solutionPtr){
			KPDGUIStructureSet const& solution = *solutionPtr;
			out << solution;
			qDebug() << "SAVE: Size" << qint32(solutionPtr->size());
			out << qint32(solutionPtr->size());
			for (int j = 0; j < solutionPtr->childCount(); j++){
				QTreeWidgetItem * item = solutionPtr->child(j);
				for (int k = 0; k < item->childCount(); k++){
					KPDGUIStructureWrapper * structure = dynamic_cast<KPDGUIStructureWrapper *>(item->child(k));
					if (structure){
						qDebug() << "SAVE: Structure ID, Utility, Children" << qint32(structure->getStructure()->getID()) << qreal(structure->getStructure()->getUtility()) << qint32(structure->childCount());
						out << qint32(structure->getStructure()->getID());
						out << qreal(structure->getStructure()->getUtility());
						out << qint32(structure->childCount());
						for (int l = 0; l < structure->childCount(); l++){
							KPDGUINodeWrapper* node = dynamic_cast<KPDGUINodeWrapper*>(structure->child(l));
							if (node){
								qDebug() << "SAVE: ID" << qint32(node->getNode()->getInternalID());
								out << qint32(node->getNode()->getInternalID());
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

void MainWindow::setCurrentFile(const QString &fileName)
{
	curFile = fileName;
	setWindowModified(false);

	QString shownName = tr("Untitled");
	if (!curFile.isEmpty()) {
		shownName = QFileInfo(curFile).fileName();
	}

	this->setWindowTitle(tr("%1[*] - %2").arg(shownName)
		.arg(tr("KPD")));
}

void MainWindow::addNode(KPDGUINode * newNode, bool fromSavedFile){

	if (!fromSavedFile){
		int h_offset = rand() % 50 - 25;
		int v_offset = rand() % 50 - 25;
		newNode->setPos(QPoint(140 + (120 * (seqNumber % 7)) + h_offset, 160 + (80 * ((seqNumber / 7) % 9)) + v_offset));
	}

	kpdguiScene->addItem(newNode);
	++seqNumber;

	kpdguiRecord->insert(newNode, fromSavedFile);
	newNode->setText(QString::number(newNode->getInternalID()));

	KPDGUINodeWrapper * wrapper = new KPDGUINodeWrapper(newNode);
	pairListWidget->addTopLevelItem(wrapper);

	foreach(KPDGUINode *node, kpdguiRecord->getPairs()){
		if (node->getType() == PAIR){
			if (kpdguiRecord->isMatch(newNode, node, false, false)){
				addArrow(newNode, node);
			}
		}
		if (newNode->getType() == PAIR){
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
	matchListWidget->addTopLevelItem(wrapper);
	kpdguiRecord->insertArrow(link);
	link->setVisible(false);
	kpdguiScene->addItem(link);
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

		//d.id = row.at(0).at(0).toInt();
		int pairType = row.at(2).at(0).toInt();
		if (pairType == 0){
			d.type = KPDPairType::PAIR;
		}
		else if (pairType == 1){
			d.type = KPDPairType::AD;
		}
		d.name = row.at(9).at(0);
		//d.donorid = row.at(10).at(0).toInt();
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
		//c.id = (row.at(0).at(0)).toInt();
		c.name = row.at(5).at(0);
		//c.recipid = (row.at(6).at(0)).toInt();
		c.age = row.at(7).at(0).toInt();

		c.BT = row.at(8).at(0);
		if (d.type == KPDPairType::AD && c.BT != "AB"){
			d.type = KPDPairType::PAIR;
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

		/*foreach(QString donorToExclude, row.at(4)){
		if (!donorToExclude.isNull()){
		c.excludedDonors.push_back(donorToExclude.toInt());
		}
		}*/

		bool sensitized = false;
		if ((row.at(3).at(0)).toInt() == 1){
			sensitized = true;
		}

		if (sensitized == false){
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
		//connect(newNode, SIGNAL(nodeSelectionChanged(int, bool)), ui->consoleWidget, SLOT(changePairInfo(int, bool)));
		//connect(newNode, SIGNAL(nodeHoldStatusChanged(int, bool)), ui->consoleWidget, SLOT(changePairText(int)));
		//connect(newNode, SIGNAL(nodeEdited(int)), ui->consoleWidget, SLOT(changePairText(int)));
		connect(newNode, SIGNAL(nodeEdited(int)), this, SLOT(updateTable(int)));

		addNode(newNode, false);
		//ui->consoleWidget->addPairInfo(newNode->getInternalID());

		pairsAdded++;
	}
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

void MainWindow::setPairSortMode(int mode, bool decreasing){
	pairSortMode = mode;
	pairSortDecreasing = decreasing;

	QList<KPDGUINodeWrapper*> newPairList;
	int itemCount = pairListWidget->topLevelItemCount();
	for (int i = 0; i < itemCount; i++){
		KPDGUINodeWrapper * temp = dynamic_cast<KPDGUINodeWrapper *>(pairListWidget->takeTopLevelItem(0));
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
		pairListWidget->addTopLevelItem(item);
	}
}

void MainWindow::setMatchSortMode(int mode, bool decreasing){
	matchSortMode = mode;
	matchSortDecreasing = decreasing;

	QList<KPDGUIArrowWrapper*> newArrowList;
	int itemCount = matchListWidget->topLevelItemCount();
	for (int i = 0; i < itemCount; i++){
		KPDGUIArrowWrapper * temp = dynamic_cast<KPDGUIArrowWrapper *>(matchListWidget->takeTopLevelItem(0));
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
		matchListWidget->addTopLevelItem(item);
	}
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

void MainWindow::changeFocus(int i){
	KPDGUINode *node = kpdguiRecord->getNode(i);

	ui->graphicsView->centerOn(node->x(), node->y());

	setWindowModified(true);
}


void MainWindow::sort(){
	setPairSortMode(pairSortMode, pairSortDecreasing);
	setMatchSortMode(matchSortMode, matchSortDecreasing);
}

void MainWindow::runSimulation(){

	QApplication::setOverrideCursor(Qt::WaitCursor);
	QApplication::processEvents();

	//Collect Parameters
	ParamInfoStruct paramInfo;

	paramInfo.optScheme = kpdguiParameters->getOptimizationScheme();
	paramInfo.utilityScheme = kpdguiParameters->getUtilityScheme();
	paramInfo.maxChainLength = kpdguiParameters->getMaxChainLength();

	paramInfo.pairFailureRate = kpdguiParameters->getPairFailureRate();
	paramInfo.adFailureRate = kpdguiParameters->getADFailureRate();
	paramInfo.exogenousFailureRate = kpdguiParameters->getExogenousFailureRate();

	paramInfo.addAdvantageToHighPRACandidates = kpdguiParameters->getAddAdvantageToHighPRACandidates();
	paramInfo.praAdvantageCutoff = kpdguiParameters->getPRAAdvantageCutoff();
	paramInfo.praAdvantageValue = kpdguiParameters->getPRAAdvantageValue();

	paramInfo.numberOfSolutions = kpdguiParameters->getNumberOfSolutions();

	paramInfo.chainStorage = kpdguiParameters->getChainStorage();
	paramInfo.reserveODonorsForOCandidates = kpdguiParameters->getReserveODonorsForOCandidates();
	paramInfo.checkDP = kpdguiParameters->getCheckDP();
	paramInfo.includeCompatiblePairs = kpdguiParameters->getIncludeCompatiblePairs();
	paramInfo.excludeABDonorsFromSimulation = kpdguiParameters->getExcludeABDonorsFromSimulation();
	paramInfo.allowABBridgeDonors = kpdguiParameters->getAllowABbridgeDonors();

	//Generate Matrices for Simulation
	kpdguiRecord->generateMatrices(paramInfo);

	//Build New Simulation
	KPDGUISimulation *g = new KPDGUISimulation(kpdguiRecord, paramInfo);

	//Collect All Structures
	KPDOptimizationScheme optScheme = kpdguiParameters->getOptimizationScheme();

	vector<vector<int> > allStructures;
	if (optScheme == KPDOptimizationScheme::SCC){
		allStructures = g->getCurrentMatchRunComponents();
	}
	else {
		allStructures = g->getCurrentMatchRunCyclesAndChains();
	}

	//Calculate and Collect Utility Values
	vector<double> utilValues;
	if (optScheme == KPDOptimizationScheme::MUC){ utilValues = g->getUtilityForCurrentMatchRunCyclesAndChains(); }
	else if (optScheme == KPDOptimizationScheme::MEUC){ utilValues = g->getExpectedUtilityForCurrentMatchRunCyclesAndChains(); }
	else if (optScheme == KPDOptimizationScheme::MEUS){ utilValues = g->getExpectedUtilityForCurrentMatchRunSets(); }
	else if (optScheme == KPDOptimizationScheme::SCC){ utilValues = g->getExpectedUtilityForCurrentMatchRunComponents(); }

	//Run Simulation
	g->getOptimalSolution();

	//Collect Solution Set and Solution Objectives
	vector<vector<int> > solutionSet = g->returnSolutionSet();
	vector<double> solutionObjectives = g->returnSolutionObjectives();

	//Create Timestamp
	QString timestamp = QDate::currentDate().toString() + " " + QTime::currentTime().toString();
	//Get Simulation Log
	QString simLog = g->getSimLog();

	//Initialize Structure List and Collection of Solution Lists
	KPDGUIStructureSet * structureList = new KPDGUIStructureSet(paramInfo, timestamp, simLog, false);
	QVector<KPDGUIStructureSet *> solutionLists;

	int sol = 0;
	for (vector<vector<int> >::iterator it = solutionSet.begin(); it != solutionSet.end(); ++it){
		sol++;
		solutionLists.push_back(new KPDGUIStructureSet(paramInfo, timestamp, simLog, true, sol));
	}

	//Count Cycles, Chains, Components
	int numberOfCycles = 0;
	int numberOfChains = 0;
	int numberOfComponents = 0;

	//Iterate Through Structures To Add To Structure List
	for (int itStruct = 0; itStruct < allStructures.size(); itStruct++){
		//Initialize New Node List;
		QVector<KPDGUINode *> structureNodes;
		bool chain = false;

		//Iterate Through Nodes in the Structure
		for (int itNode = 0; itNode < allStructures[itStruct].size(); itNode++){
			//Get Pair ID of Node
			int id = kpdguiRecord->pairInfoVector[allStructures[itStruct][itNode]].pairID;
			//Collect Node Object based on Pair ID
			KPDGUINode * node = kpdguiRecord->getNode(id);
			if (node->getType() == KPDPairType::AD){
				chain = true;
			}
			//Add to Node List
			structureNodes.push_back(node);
		}

		//Determine ID Number of Structure
		int idnum;
		if (optScheme == KPDOptimizationScheme::SCC){
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

		//Initialize New Structure Object using Node List, Utility; Push to Structure List
		KPDGUIStructure * newStructure = new KPDGUIStructure(structureNodes, optScheme, utilValues[itStruct], idnum);
		structureList->push_back(newStructure);

		//Iterate Through Solutions
		for (int itSolution = 0; itSolution < solutionSet.size(); itSolution++){
			//If Current Structure is Found in Current Solution
			if (std::find(solutionSet[itSolution].begin(), solutionSet[itSolution].end(), itStruct) != solutionSet[itSolution].end()){
				solutionLists[itSolution]->push_back(newStructure);
			}
		}
	}

	//Collapse all Current Solutions Shown In the Widget
	solutionTreeWidget->collapseAll();

	//Reset Popularity Values in The Node List Widget and Edge List Widget
	for (int i = 0; i < pairListWidget->topLevelItemCount(); i++){
		KPDGUINodeWrapper * wrapper = dynamic_cast<KPDGUINodeWrapper *>(pairListWidget->topLevelItem(i));
		if (wrapper){
			wrapper->getNode()->resetPopularityInStructures();
		}
	}
	for (int i = 0; i < matchListWidget->topLevelItemCount(); i++){
		KPDGUIArrowWrapper * wrapper = dynamic_cast<KPDGUIArrowWrapper *>(pairListWidget->topLevelItem(i));
		if (wrapper){
			wrapper->getArrow()->resetPopularityInStructures();
		}
	}
	//Update Popularity of Structure
	structureList->updatePopularity();
	//Add Structure to Structure Widget and Expand
	structureTreeWidget->insertTopLevelItem(0, structureList);
	structureList->setExpanded(true);

	//Add Solutions to Solution Widget
	int level = 0;
	foreach(KPDGUIStructureSet * structureSet, solutionLists){
		structureSet->updatePopularity();
		solutionTreeWidget->insertTopLevelItem(level, structureSet);
		structureSet->setExpanded(true);
		level++;
	}

	//Parameters Have Not Been Set For Next Simulation
	kpdguiParameters->setParametersSet(false);

	//Switch Tab to "Solution" Tab
	ui->tabWidget->setCurrentIndex(3);

	//Sort Matches Based on Solution Popularity
	setMatchSortMode(0, true);

	delete g;

	QApplication::restoreOverrideCursor();
	QApplication::processEvents();
}

void MainWindow::readSettings()
{

}

void MainWindow::writeSettings()
{

}



