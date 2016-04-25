
#include "ui_KPDGUI.h"

#include "KPDGUI.h"

KPDGUI::KPDGUI(QWidget *parent) : QMainWindow(parent), ui(new Ui::KPDGUI)
{
    ui->setupUi(this);

	initializeParameters();	
	setUpKPDObjects();
	setUpLists();
	setUpActions();
	setUpMenu();
	setUpToolbar();
	
	ui->dashboard->appendDashboardText("Welcome to KPDGUI - " + QDate::currentDate().toString() + " " + QTime::currentTime().toString() + "\n");	
}

KPDGUI::~KPDGUI()
{
    delete ui;
}

void KPDGUI::initializeParameters(){
	
	maxZ = 0;
	nodePlacementSequenceNumber = 0;
	previousSliderPosition = 0;
	setCurrentFile("");
}

void KPDGUI::setUpKPDObjects(){

	// Graphics View
	//ui->graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
	//connect(ui->graphicsView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(screenCustomMenu(QPoint)));
	//connect(ui->graphicsView, SIGNAL(zoomIn()), this, SLOT(zoomIn()));
	//connect(ui->graphicsView, SIGNAL(zoomOut()), this, SLOT(zoomOut()));
	//connect(ui->graphicsView, SIGNAL(mouseReleased()), this, SLOT(updateVisibility()));

	//Graphics Scene
	kpdguiScene = new QGraphicsScene();
	ui->graphicsView->setScene(kpdguiScene);

	//Simulation Parameters
	kpdguiParameters = new KPDGUISimParameters();

	//Pair Record
	kpdguiRecord = new KPDGUIRecord();

	//Display Settings
	kpdguiDisplaySettings = new KPDGUIDisplaySettings();
}

void KPDGUI::setUpLists(){

	//Node List
	ui->nodeList->header()->resizeSection(0, 50);
	ui->nodeList->header()->resizeSection(1, 50);
	ui->nodeList->header()->resizeSection(2, 120);
	ui->nodeList->header()->resizeSection(3, 50);
	ui->nodeList->sortItems(0, Qt::AscendingOrder);
	ui->nodeList->setContextMenuPolicy(Qt::CustomContextMenu);
	//connect(ui->nodeList, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(clickActions(QTreeWidgetItem*)));
	//connect(ui->nodeList, SIGNAL(mouseReleased()), this, SLOT(newPairListSelectionActions()));
	//connect(ui->nodeList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(pairListCustomMenu(QPoint)));
	
	ui->donorList->header()->resizeSection(0, 50);
	ui->nodeList->header()->resizeSection(1, 50);
	ui->nodeList->header()->resizeSection(2, 120);
	ui->nodeList->header()->resizeSection(3, 50);
	ui->nodeList->sortItems(0, Qt::AscendingOrder);
	ui->nodeList->setContextMenuPolicy(Qt::CustomContextMenu);


	//Structure Tree
	ui->structureWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	//connect(ui->structureWidget, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this, SLOT(structureTreeSelectionActions(QTreeWidgetItem*)));
	connect(ui->structureWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(structureTreeCustomMenu(QPoint)));
	
	//Solution Tree
	ui->solutionWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	//connect(ui->solutionWidget, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this, SLOT(solutionTreeSelectionActions(QTreeWidgetItem*)));
	connect(ui->solutionWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(solutionTreeCustomMenu(QPoint)));
	
	ui->structureWidget->setVisible(false);
	ui->solutionWidget->setVisible(false);
}


void KPDGUI::setUpActions(){
	
	//Screen Custom Menu
	/*addAssociatedDonorAction = new QAction(tr("&Add Additional Donor"), this);
	connect(addAssociatedDonorAction, SIGNAL(triggered()), this, SLOT(addAssociatedDonor()));

	highlightStructuresAction = new QAction(tr("&Highlight Structures"), this);
	connect(highlightStructuresAction, SIGNAL(triggered()), this, SLOT(highlightRelevantStructures()));

	highlightSolutionsAction = new QAction(tr("&Highlight Solutions"), this);
	connect(highlightSolutionsAction, SIGNAL(triggered()), this, SLOT(highlightRelevantSolutions()));

	selectAllAction = new QAction(tr("&Select All"), this);
	connect(selectAllAction, SIGNAL(triggered()), this, SLOT(selectAll()));

	clearHighlightsAction = new QAction(tr("&Clear Highlights"), this);
	connect(clearHighlightsAction, SIGNAL(triggered()), this, SLOT(clearHighlights()));*/

	/*editDonorAction = new QAction(tr("&Edit Donor"), this);
	connect(editDonorAction, SIGNAL(triggered()), this, SLOT(editDonor()));

	editCandidateAction = new QAction(tr("&Edit Candidate"), this);
	connect(editCandidateAction, SIGNAL(triggered()), this, SLOT(editCandidate()));

	holdNodeAction = new QAction(tr("&Hold"), this);
	connect(holdNodeAction, SIGNAL(triggered()), this, SLOT(holdNode()));

	unholdNodeAction = new QAction(tr("&Unhold"), this);
	connect(unholdNodeAction, SIGNAL(triggered()), this, SLOT(unholdNode()));

	deleteNodeAction = new QAction(tr("&Delete"), this);
	connect(deleteNodeAction, SIGNAL(triggered()), this, SLOT(deleteNode()));

	holdMultipleNodesAction = new QAction(tr("&Hold Selected Pairs"), this);
	connect(holdMultipleNodesAction, SIGNAL(triggered()), this, SLOT(holdMultipleNodes()));

	unholdMultipleNodesAction = new QAction(tr("&Unhold Selected Pairs"), this);
	connect(unholdMultipleNodesAction, SIGNAL(triggered()), this, SLOT(unholdMultipleNodes()));

	clusterMultipleNodesAction = new QAction(tr("&Cluster Selected Pairs"), this);
	connect(clusterMultipleNodesAction, SIGNAL(triggered()), this, SLOT(clusterMultipleNodes()));

	deleteMultipleNodesAction = new QAction(tr("&Delete Selected Pairs"), this);
	connect(deleteMultipleNodesAction, SIGNAL(triggered()), this, SLOT(deleteMultipleNodes()));*/


	//Structures Custom Menu
	//clusterStructureAction = new QAction("Cluster Structure", this);
	//connect(clusterStructureAction, SIGNAL(triggered()), this, SLOT(clusterStructure()));


	//Solutions Custom Menu
	//clusterSolutionAction = new QAction("Cluster Solution", this);
	//connect(clusterSolutionAction, SIGNAL(triggered()), this, SLOT(clusterSolution()));

	//removeSolutionAction = new QAction("Remove Solution", this);
	//connect(removeSolutionAction, SIGNAL(triggered()), this, SLOT(removeSolution()));
}


void KPDGUI::setUpMenu(){
	
	displayArrowsActionGroup = new QActionGroup(this);
	displayArrowsActionGroup->addAction(ui->actionDisplay_Compatibilities_Within_Selection);
	displayArrowsActionGroup->addAction(ui->actionDisplay_Selected_Compatibilities);
	displayArrowsActionGroup->addAction(ui->actionDisplay_All_Compatibilities);
	displayArrowsActionGroup->addAction(ui->actionDisplay_No_Compatibilities);
}

void KPDGUI::setUpToolbar(){
	
	zoomSlider = new QSlider();
	zoomSlider->setMinimumSize(QSize(84, 24));
	zoomSlider->setMaximumSize(QSize(84, 24));
	zoomSlider->setMinimum(MINIMUM_SLIDER_POSITION);
	zoomSlider->setMaximum(MAXIMUM_SLIDER_POSITION);
	zoomSlider->setValue(0);
	zoomSlider->setOrientation(Qt::Horizontal);
	zoomSlider->setTickPosition(QSlider::TicksBelow);
	QObject::connect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoom(int)));

	ui->toolBar->insertWidget(ui->actionZoom_In, zoomSlider);
	ui->actionMouse_Tool->setChecked(true);
}

void KPDGUI::newKPD()
{
    KPDGUI *mainWin = new KPDGUI;
    mainWin->show();
}

void KPDGUI::openKPD()
{
    if (okToContinue()) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open KPD"), ".", tr("KPD files (*.kpd)"));
		if (!fileName.isEmpty()){
			loadFile(fileName);
			updateStatus("Opened File: " + fileName);
		}
    }
}

bool KPDGUI::saveKPD()
{
    if (currentFile.isEmpty()) {
        return saveKPDAs();
    } else {
        return saveFile(currentFile);
    }
}

bool KPDGUI::saveKPDAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save KPD"), ".", tr("KPD files (*.kpd)"));
    if (fileName.isEmpty()){
		updateStatus("Failed to load empty file");
		return false;
	}
		
    return saveFile(fileName);
}

void KPDGUI::addNewNode()
{
	DialogCandidate * dialogCandidate = new DialogCandidate(this);

	if (dialogCandidate->exec()) {

		KPDGUICandidate * candidate = new KPDGUICandidate(dialogCandidate);
		
		DialogDonor * dialogDonor = new DialogDonor(this);

		if (dialogDonor->exec()) {

			QVector<KPDGUIDonor *> associatedDonors;
			
			KPDGUIDonor * donor = new KPDGUIDonor(dialogDonor);
			associatedDonors.push_back(donor);

			int additionalDonorMessage = QMessageBox::warning(this, tr("KPD"),
				"New Pairing Contains a Single Donor. Add Another Donor to Pairing?",
				QMessageBox::Yes | QMessageBox::No);
			
			while (additionalDonorMessage == QMessageBox::Yes) {

				DialogDonor * additionalDialogDonor = new DialogDonor(this);

				if (additionalDialogDonor->exec()) {

					KPDGUIDonor * additionalDonor = new KPDGUIDonor(dialogDonor);
					associatedDonors.push_back(additionalDonor);

					additionalDonorMessage = QMessageBox::warning(this, tr("KPD"),
						"New Pairing Contains " + QString::number(associatedDonors.size()) + " Donors. Add Another Donor to Pairing?",
						QMessageBox::Yes | QMessageBox::No);
				}
			}

			//qDebug() << "Creating Node";
			KPDGUINode * newNode = new KPDGUINode(associatedDonors, candidate);
			//qDebug() << "Node Created";
			
			//newNode->setNodePosition(QPointF(0, 0));

			//qDebug() << "Add Node to Record";
			addNode(newNode, false);
			//qDebug() << "Node Added to Record" << newNode->getID() << " " << newNode->getFirstDonor()->getID();
			//kpdguiScene->clearSelection();
			//newNode->setSelected(true);
			changeFocus(newNode);

			//qDebug() << "Write to Dashboard";
			updateStatus("Added New Pairing: " + newNode->getNameString());
			//qDebug() << "Written to Dashboard";

			//emit visibilityChanged(kpdguiDisplaySettings);
			//emit poolChanged();
			setWindowModified(true);
		}

		else {
			QMessageBox::about(this, tr("About KPDGUI"),"No Donors added. Node will not be created");
		}
	}
}

void KPDGUI::addNewAD()
{
	DialogDonor * dialogAD = new DialogDonor(this);

	if (dialogAD->exec()) {

		KPDGUIDonor * altruisticDonor = new KPDGUIDonor(dialogAD);

		KPDGUINode * newNode = new KPDGUINode(altruisticDonor);

		addNode(newNode, false);

		
		//kpdguiScene->clearSelection();
		//newNode->setSelected(true);
		changeFocus(newNode);
		
		updateStatus("Added New Altrustic Donor: " + newNode->getNameString());

		//emit visibilityChanged(kpdguiDisplaySettings);
		//emit poolChanged();
		setWindowModified(true);
	}
}

/*void KPDGUI::addAssociatedDonor(int i){
	DialogDonor * dialog = new DialogDonor(this);

	if (dialog->exec()) {

		Donor associatedDonor(dialog);

		Candidate c = kpdguiRecord->getNode(i)->getCandidate();
		KPDGUINode * newDonor = new KPDGUINode(associatedDonor, c);
		////connect(newDonor, SIGNAL(nodeWasClicked(int, bool)), this, SLOT(clickActions(int, bool)));
		////connect(newDonor, SIGNAL(nodeEntered(int)), this, SLOT(updateTable(int)));
		////connect(newDonor, SIGNAL(nodeLeft(int)), this, SLOT(clearTable()));

		addNode(newDonor, false);

		int pairID = newDonor->getID();
		//ui->dashboard->addPairInfo(pairID);

		//KPDGUIMatch * link = new KPDGUIMatch(newDonor, kpdguiRecord->getNode(i), false);
		//QVector<KPDGUINode *> nodes;
		//nodes.push_back(newDonor);
		//nodes.push_back(kpdguiRecord->getNode(i));

		kpdguiScene->clearSelection();
		newDonor->setSelected(true);
		changeFocus(pairID);
		//ui->dashboard->focusOnPairScreen(pairID);

		statusBar()->showMessage("Added New Associated Donor", 2000);
		ui->dashboard->appendDashboardText("> Added New Donor: " + associatedDonor.getName() + " (" + QString::number(pairID) + ")");

		emit visibilityChanged(kpdguiDisplaySettings);
		setWindowModified(true);
	}
}*/

/*void KPDGUI::highlightRelevantStructures(int i){
	QTreeWidgetItem * item = ui->structureWidget->topLevelItem(0);

	KPDGUINode * node = kpdguiRecord->getNode(i);

	for (int i = 0; i < item->childCount(); i++){
		for (int j = 0; j < item->child(i)->childCount(); j++){
			KPDGUIStructureWrapper * structure = dynamic_cast<KPDGUIStructureWrapper *>(item->child(i)->child(j));
			if (structure){
				if (structure->getStructure()->contains(node)){
					structure->getStructure()->select();
					updateVisibility();
					structure->getStructure()->highlight();
					selectedStructures.push_back(structure->getStructure());
				}
			}
		}
	}
}*/

//void KPDGUI::highlightRelevantSolutions(int i){

//}

void KPDGUI::loadNodes()
{
	ReadFileDialog readFileDialog(this);

	if (readFileDialog.exec()) {
		QApplication::setOverrideCursor(Qt::WaitCursor);
		QApplication::processEvents();

		kpdguiScene->clearSelection();

		QString str = readFileDialog.pairFileLineEdit->text();
		QString layout = readFileDialog.layoutComboBox->currentText();

		readPairsFromFile(str,layout);

		QApplication::restoreOverrideCursor();
		QApplication::processEvents();

		QStringList splitstr = str.split("/");
		updateStatus("Loaded Pairs From " + splitstr.last());

		setWindowModified(true);
		emit visibilityChanged(kpdguiDisplaySettings);
		emit poolChanged();
		kpdguiParameters->setParametersHaveBeenUpdated(false);

	}
}

void KPDGUI::exitProgram()
{
	qApp->closeAllWindows();
}

void KPDGUI::performMatchRun()
{
	bool proceed = true;

	if (!kpdguiParameters->getParametersHaveBeenUpdated()) {
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
		updateStatus("Run Successful");
	}
	else {
		updateStatus("Run Aborted");
	}
}

bool KPDGUI::setSimParameters()
{
	DialogSimParameters * simParamDialog = new DialogSimParameters(kpdguiParameters, this);

	if (simParamDialog->exec()) {
		
		kpdguiParameters->changeParameters(simParamDialog);
		kpdguiParameters->setParametersHaveBeenUpdated(true);
		updateStatus("Set New Parameters");		

		return true;
	}

	return false;
}

void KPDGUI::clearSolutions(){
	int r = QMessageBox::warning(this, tr("KPD"),
		tr("Remove Solutions?"),
		QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	if (r == QMessageBox::Yes) {
		int items = ui->solutionWidget->topLevelItemCount();
		for (int i = 0; i < items; i++){
			QTreeWidgetItem * solutionToDelete = ui->solutionWidget->takeTopLevelItem(0);
			delete solutionToDelete;
		}

		kpdguiScene->clearSelection();
		updateStatus("Solutions Cleared");

		setWindowModified(true);
	}
}

void KPDGUI::changeNodeViewMode()
{
	DialogDisplaySettings * displayDialog = new DialogDisplaySettings(kpdguiDisplaySettings, this);

	if (displayDialog->exec()){		
		bool settingsChanged = kpdguiDisplaySettings->changeDisplaySettings(displayDialog);
		if (settingsChanged){
			updateStatus("Display Settings Changed");
		}
	}
}

void KPDGUI::changeMatchViewMode_Within()
{
	kpdguiDisplaySettings->setMatchDisplayMode(WITHIN_SELECTION);
	updateVisibility();
}

void KPDGUI::changeMatchViewMode_SelectedCompatibilities()
{
	kpdguiDisplaySettings->setMatchDisplayMode(SELECTED_COMPATIBILITIES);
	updateVisibility();
}

void KPDGUI::changeMatchViewMode_All()
{
	kpdguiDisplaySettings->setMatchDisplayMode(ALL_COMPATIBILITIES);
	updateVisibility();
}

void KPDGUI::changeMatchViewMode_None()
{
	kpdguiDisplaySettings->setMatchDisplayMode(NO_COMPATIBILITIES);
	updateVisibility();
}

void KPDGUI::zoomIn(){
	int position = zoomSlider->value();

	if (position < MAXIMUM_SLIDER_POSITION){
		position++;
		zoomSlider->setValue(position);
	}
}

void KPDGUI::zoomOut(){
	int position = zoomSlider->value();

	if (position > MINIMUM_SLIDER_POSITION){
		position--;
		zoomSlider->setValue(position);
	}
}

void KPDGUI::zoom(int tick){

	double scaleFactor = 1.15;
	ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

	if (tick > previousSliderPosition){
		for (int i = 0; i < (tick - previousSliderPosition); i++){
			ui->graphicsView->scale(scaleFactor, scaleFactor);
		}
	}
	else if (tick < previousSliderPosition){
		for (int i = 0; i < (previousSliderPosition - tick); i++){
			ui->graphicsView->scale(1 / scaleFactor, 1 / scaleFactor);
		}
	}
	previousSliderPosition = tick;
}

void KPDGUI::changeToMouseMode(){
	ui->actionHand_Tool->setChecked(false);
	ui->actionMouse_Tool->setChecked(true);

	ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
	ui->graphicsView->setCursor(Qt::ArrowCursor);
	ui->graphicsView->changeMode(0);
}

void KPDGUI::changeToHandMode(){
	ui->actionHand_Tool->setChecked(true);
	ui->actionMouse_Tool->setChecked(false);

	ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
	ui->graphicsView->setCursor(Qt::OpenHandCursor);
	ui->graphicsView->changeMode(1);
}

void KPDGUI::aboutKPD()
{
	QMessageBox::about(this, tr("About KPDGUI"),
		tr("<h2>KPDGUI 1.1</h2>"
		"<p>Copyright &copy; 2014."
		"<p>Author: Mathieu Bray"));
}


//void KPDGUI::newPairListSelectionActions(QTreeWidgetItem* item)
void KPDGUI::newNodeListSelectionActions()
{
	for (int i = 0; i < ui->nodeList->topLevelItemCount(); i++){
		QTreeWidgetItem * item = ui->nodeList->topLevelItem(i);
		KPDGUINodeWrapper * wrapper = dynamic_cast<KPDGUINodeWrapper *>(item);
		if (wrapper){
			bool selected = item->isSelected();
			KPDGUINode * node = wrapper->getNode();
			node->setSelected(selected);

			/*if (selected){
				ui->graphicsView->centerOn(QPointF(node->x(), node->y()));
			}*/			
		}
	}

	updateVisibility();
}

/*void KPDGUI::newMatchListSelectionActions(QTreeWidgetItem* item)
{
	KPDGUIMatchWrapper * arrow = dynamic_cast<KPDGUIMatchWrapper *>(item);
	if (arrow){
		KPDGUIMatch * link = arrow->getArrow();

		bool selected = item->isSelected();
		link->startItem()->setSelected(selected);
		link->endItem()->setSelected(selected);

		updateVisibility();
	}
}*/

void KPDGUI::structureTreeSelectionActions(QTreeWidgetItem* item)
{
	ui->solutionWidget->selectionModel()->clearSelection();
	highlightStructures(item);
}

void KPDGUI::solutionTreeSelectionActions(QTreeWidgetItem* item)
{
	ui->structureWidget->selectionModel()->clearSelection();
	highlightStructures(item);
}

void KPDGUI::highlightStructures(QTreeWidgetItem * item){
	QApplication::setOverrideCursor(Qt::WaitCursor);
	QApplication::processEvents();

	bool selected = item->isSelected();

	ui->dashboard->removeSolution();
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
				//clearTable();
				updateVisibility();
				structureSet->highlight();

				foreach(KPDGUIStructure * structure, structureSet->getStructures()){
					selectedStructures.push_back(structure);
				}
				ui->dashboard->showSolution(structureSet->getDashboardString());
				ui->dashboard->focusOnSolution();
			}
		}
		else if (level == 2) {
			KPDGUIStructureWrapper * structureWrapper = dynamic_cast<KPDGUIStructureWrapper *>(item);
			if (structureWrapper){
				KPDGUIStructure * structure = structureWrapper->getStructure();
				kpdguiScene->clearSelection();
				structure->select();
				//clearTable();
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

				ui->graphicsView->centerOn(node->getNodePosition());

				int i = node->getID();
				
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
			//clearTable();
		}

	}
	else {
		kpdguiScene->clearSelection();
		updateVisibility();
		//clearTable();
	}

	QApplication::restoreOverrideCursor();
	QApplication::processEvents();
}

void KPDGUI::newNodeListDoubleClickActions(QTreeWidgetItem * item)
{
	KPDGUINodeWrapper * node = dynamic_cast<KPDGUINodeWrapper *>(item);
	if (node){
		//qDebug() << "Double Click " << node->getNode()->getID();
	}
}

void KPDGUI::screenCustomMenu(QPoint pos){	

	QMenu * menu = new QMenu(this);
	QList<QGraphicsItem*> items = kpdguiScene->selectedItems();
	
	if (items.size() >= 2){
		bool allHeld = true;
		foreach(QGraphicsItem * item, items){
			KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
			if (!node->getStatus()){
				allHeld = false;
			}
		}
		menu->addAction(clusterMultipleNodesAction);
		menu->addSeparator();
		if (allHeld){
			menu->addAction(unholdMultipleNodesAction);
		}
		else {
			menu->addAction(holdMultipleNodesAction);
		}

		menu->addAction(deleteMultipleNodesAction);
	}

	else if (items.size() == 1){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(items.first());
		if (node){
			//menu->addAction(addAssociatedDonorAction);
			//menu->addAction(highlightStructuresAction);
			//menu->addAction(highlightSolutionsAction);
			menu->addAction(editDonorAction);
			if (node->getType() == PAIR){
				menu->addAction(editCandidateAction);
			}
			menu->addSeparator();
			if (node->getStatus()){
				menu->addAction(unholdNodeAction);
			}
			else {
				menu->addAction(holdNodeAction);
			}
			menu->addAction(deleteNodeAction);
		}
	}

	else {
		//menu->addAction(selectAllAction);
		//menu->addAction(clearHighlightsAction);
	}

	if (menu->actions().size() > 0){
		menu->popup(ui->graphicsView->viewport()->mapToGlobal(pos));
	}

}

void KPDGUI::nodeListCustomMenu(QPoint pos){

	//qDebug() << "Pair List Custom Menu";

	QTreeWidgetItem * item = ui->nodeList->itemAt(pos);

	QMenu *menu = new QMenu(this);

	KPDGUINodeWrapper * wrapper = dynamic_cast<KPDGUINodeWrapper *>(item);
	if (wrapper){
		KPDGUINode *node = wrapper->getNode();
		//menu->addAction(addAssociatedDonorAction);
		//menu->addAction(highlightStructuresAction);
		//menu->addAction(highlightSolutionsAction);
		menu->addAction(editDonorAction);
		if (node->getType() == PAIR){
			menu->addAction(editCandidateAction);
		}
		menu->addSeparator();
		if (node->getStatus()){
			menu->addAction(unholdNodeAction);
		}
		else {
			menu->addAction(holdNodeAction);
		}
		menu->addAction(deleteNodeAction);
	}

	if (menu->actions().size() > 0){
		menu->popup(ui->nodeList->viewport()->mapToGlobal(pos));
	}
}

void KPDGUI::structureTreeCustomMenu(QPoint pos){
	QTreeWidgetItem * item = ui->structureWidget->itemAt(pos);

	QMenu *menu = new QMenu(this);

	KPDGUIStructureWrapper * structureWrapper = dynamic_cast<KPDGUIStructureWrapper *>(item);
	if (structureWrapper){
		KPDGUIStructure * structure = structureWrapper->getStructure();
		menu->addAction(clusterStructureAction);

		rightClickStructure = structure;
	}
	if (menu->actions().size() > 0){
		menu->popup(ui->structureWidget->viewport()->mapToGlobal(pos));
	}

}

void KPDGUI::solutionTreeCustomMenu(QPoint pos){
	QTreeWidgetItem * item = ui->solutionWidget->itemAt(pos);

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
			if (structureSet->structureSetisSolutionSet()){
				menu->addAction(clusterSolutionAction);
				menu->addAction(removeSolutionAction);
				rightClickStructureSet = structureSet;
			}
		}
	}
	if (menu->actions().size() > 0){
		menu->popup(ui->solutionWidget->viewport()->mapToGlobal(pos));
	}
}

//void KPDGUI::deleteNode(int i)
//{
	////qDebug() << "Delete " << i;

	/*KPDGUINode * nodeToDelete = kpdguiRecord->getNode(i);
	int id = nodeToDelete->getID();
	nodeToDelete->setSelected(false);
	
	QApplication::setOverrideCursor(Qt::WaitCursor);
	QApplication::processEvents();

	QSet<KPDGUINodeWrapper *> nodeWrappersToDelete;
	QSet<KPDGUIMatchWrapper *> arrowWrappersToDelete;
	QSet<KPDGUIStructureWrapper *> structureWrappersToDelete;
	QSet<KPDGUIStructure *> structuresToDelete; */

/*	for (int i = 0; i < ui->nodeList->topLevelItemCount(); i++){
		KPDGUINodeWrapper * nodeWrapper = dynamic_cast<KPDGUINodeWrapper *>(ui->nodeList->topLevelItem(i));
		if (nodeWrapper){
			if (nodeWrapper->getNode()->getID() == id){
				nodeWrappersToDelete.insert(nodeWrapper);
			}
		}
	} */

	/*for (int i = 0; i < matchListWidget->topLevelItemCount(); i++){
		KPDGUIMatchWrapper * arrowWrapper = dynamic_cast<KPDGUIMatchWrapper *>(matchListWidget->topLevelItem(i));
		if (arrowWrapper){
			if (arrowWrapper->getArrow()->startItem()->getID() == id){
				arrowWrappersToDelete.insert(arrowWrapper);
			}
			else if (arrowWrapper->getArrow()->endItem()->getID() == id){
				arrowWrappersToDelete.insert(arrowWrapper);
			}
		}
	}*/	

	/*for (int i = 0; i < ui->structureWidget->topLevelItemCount(); i++){
		KPDGUIStructureSet * structureSet = dynamic_cast<KPDGUIStructureSet *>(ui->structureWidget->topLevelItem(i));
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

	for (int i = 0; i < ui->solutionWidget->topLevelItemCount(); i++){
		KPDGUIStructureSet * structureSet = dynamic_cast<KPDGUIStructureSet *>(ui->solutionWidget->topLevelItem(i));
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

	foreach(KPDGUIMatchWrapper * arrowWrapper, arrowWrappersToDelete){
		delete arrowWrapper;
	}

	foreach(KPDGUIStructureWrapper * structureWrapper, structureWrappersToDelete){
		delete structureWrapper;
	}

	foreach(KPDGUIStructure * structureToDelete, structuresToDelete){
		delete structureToDelete;
	}

	if (nodeToDelete->getType() == KPDPairType::AD){
		ui->dashboard->appendDashboardText("> Deleted AD: " + nodeToDelete->getDonorName() + " (" + QString::number(id) + ")");
	}
	else {
		ui->dashboard->appendDashboardText("> Deleted Pair: " + nodeToDelete->getDonorName() + ", " + nodeToDelete->getCandidateName() + " (" + QString::number(id) + ")");
	}
	//ui->dashboard->deletePairInfo(id);

	kpdguiRecord->deleteNodeFromRecord(id);

	delete nodeToDelete;

	setWindowModified(true);

	QApplication::restoreOverrideCursor();
	QApplication::processEvents();*/
//}

void KPDGUI::clickActions(QTreeWidgetItem * item)
{
	KPDGUINodeWrapper * wrapper = dynamic_cast<KPDGUINodeWrapper *>(item);
	if (wrapper){
		changeFocus(wrapper->getNode());
	}
}

//void KPDGUI::selectAllVisibleNodes(){
	//QApplication::setOverrideCursor(Qt::WaitCursor);
	//QApplication::processEvents();
	
	//emit selectAll();

	//QApplication::restoreOverrideCursor();
	//QApplication::processEvents();
//}

//void KPDGUI::clearAllHighlights(){
//	if (selectedStructures.size() > 0){
//		foreach(KPDGUIStructure * structure, selectedStructures){
//			structure->undoHighlights();
//		}
//	}
//	selectedStructures.clear();
//}

void KPDGUI::clusterStructure(){

	QApplication::setOverrideCursor(Qt::WaitCursor);
	QApplication::processEvents();

	rightClickStructure->cluster();
	rightClickStructure->select();
	rightClickStructure->highlight();

	QApplication::restoreOverrideCursor();
	QApplication::processEvents();

	ui->graphicsView->centerOn(QPoint(rightClickStructure->centerX(), rightClickStructure->centerY()));
}

void KPDGUI::clusterSolution(){

	QApplication::setOverrideCursor(Qt::WaitCursor);
	QApplication::processEvents();

	rightClickStructureSet->cluster();
	rightClickStructureSet->selectStructures();
	rightClickStructureSet->highlight();

	QApplication::restoreOverrideCursor();
	QApplication::processEvents();

	ui->graphicsView->centerOn(QPoint(rightClickStructureSet->centerX(), rightClickStructureSet->centerY()));
}

void KPDGUI::removeSolution(){
	int r = QMessageBox::warning(this, tr("KPD"),
		tr("Remove Solution?"),
		QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	if (r == QMessageBox::Yes) {
		int index = ui->solutionWidget->indexOfTopLevelItem(rightClickStructureSet);
		QTreeWidgetItem * solutionToDelete = ui->solutionWidget->takeTopLevelItem(index);
		delete solutionToDelete;
		kpdguiScene->clearSelection();
		
		setWindowModified(true);
	}
}

void KPDGUI::checkSelections(){
	
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

void KPDGUI::updateVisibility(){
	//qDebug() << "KPDGUI::updateVisibility";
	emit visibilityChanged(kpdguiDisplaySettings);
}

void KPDGUI::updateStatusBar()
{

}

void KPDGUI::closeEvent(QCloseEvent *event)
{
	if (okToContinue()) {
		event->accept();
	}
	else {
		event->ignore();
	}
}


bool KPDGUI::loadFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::warning(this, tr("KPD"),
			tr("Cannot read file %1:\n%2.")
			.arg(file.fileName())
			.arg(file.errorString()));

		updateStatus("Failed To Load " + fileName);
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

	//Clear Screen
	kpdguiRecord->clearRecord();
	kpdguiScene->clear();
	//ui->nodeList->clear();
	//matchListWidget->clear();
	ui->structureWidget->clear();
	ui->solutionWidget->clear();
	//clearTable();

	QMap<int, KPDGUINode*> nodeMap;

	for (int i = 0; i < size; i++){
		////qDebug() << i;
		KPDGUINode * node = new KPDGUINode();
		in >> *node;
		addNode(node, true);

		int internalID = node->getID();
		nodeMap.insert(internalID, node);

		qint32 x;
		qint32 y;

		in >> x >> y;
		node->setNodePosition(QPointF(x, y));
	}
	
	in >> *kpdguiDisplaySettings;
	
	qint32 zoom;
	in >> zoom;
	zoomSlider->setValue(zoom);

	qint32 solutions;
	in >> solutions;

	QList<QTreeWidgetItem *> solutionItems;
	for (int i = 0; i < solutions; i++){
		KPDGUIStructureSet * solution = new KPDGUIStructureSet();
		in >> *solution;
		int numberOfStructures;
		in >> numberOfStructures;
		for (int j = 0; j < numberOfStructures; j++){
			int structureID;
			double utility;
			int numberOfNodes;
			in >> structureID >> utility >> numberOfNodes;
			QVector<KPDGUINode *> nodeList;
			for (int k = 0; k < numberOfNodes; k++){
				int id;
				in >> id;
				nodeList.push_back(nodeMap[id]);
			}
			KPDGUIStructure * structure = new KPDGUIStructure(nodeList, solution->getOptScheme(), utility, structureID);
			solution->addStructure(structure);
		}
		solution->updatePopularity();
		solutionItems.push_back(solution);
	}
	ui->solutionWidget->addTopLevelItems(solutionItems);
	ui->solutionWidget->collapseAll();

	kpdguiRecord->setBaselineIDCode(baselineCode);

	setCurrentFile(fileName);
	updateStatus(fileName + " Loaded");

	setDisplaySettings(kpdguiDisplaySettings);
	setWindowModified(false);

	QApplication::restoreOverrideCursor();
	QApplication::processEvents();

	return true;
}

bool KPDGUI::saveFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly)) {
		QMessageBox::warning(this, tr("KPD"),
			tr("Cannot write file %1:\n%2.")
			.arg(file.fileName())
			.arg(file.errorString()));

		updateStatus("Failed To Save " + fileName);
		return false;
	}

	QDataStream out(&file);
	out.setVersion(QDataStream::Qt_5_3);

	out << qint32(MagicNumber);

	out << qint32(kpdguiRecord->getBaselineIDCode());
	out << qint32(kpdguiRecord->getNumberOfNodes());

	foreach(KPDGUINode * node, kpdguiRecord->getNodes()) {
		out << &node;

		int x = node->getNodePosition().x();
		int y = node->getNodePosition().y();

		out << qint32(x) << qint32(y);
	}

	out << &kpdguiDisplaySettings;

	int zoom = zoomSlider->value();
	out << qint32(zoom);

	int solutions = ui->solutionWidget->topLevelItemCount();
	out << qint32(solutions);

	for (int i = 0; i < solutions; i++){
		KPDGUIStructureSet * solutionPtr = dynamic_cast<KPDGUIStructureSet*>(ui->solutionWidget->topLevelItem(i));
		if (solutionPtr){
			KPDGUIStructureSet const& solution = *solutionPtr;
			out << solution;
			out << qint32(solutionPtr->size());
			for (int j = 0; j < solutionPtr->childCount(); j++){
				QTreeWidgetItem * item = solutionPtr->child(j);
				for (int k = 0; k < item->childCount(); k++){
					KPDGUIStructureWrapper * structure = dynamic_cast<KPDGUIStructureWrapper *>(item->child(k));
					if (structure){
						out << qint32(structure->getStructure()->getID());
						out << qreal(structure->getStructure()->getUtility());
						out << qint32(structure->childCount());
						for (int l = 0; l < structure->childCount(); l++){
							KPDGUINodeWrapper* node = dynamic_cast<KPDGUINodeWrapper*>(structure->child(l));
							if (node){
								out << qint32(node->getNode()->getID());
							}
						}
					}
				}
			}
		}
	}

	setCurrentFile(fileName);
	updateStatus(fileName + " Saved");

	return true;
}

void KPDGUI::setCurrentFile(const QString &fileName)
{
	currentFile = fileName;
	setWindowModified(false);

	QString shownName = tr("Untitled");
	if (!currentFile.isEmpty()) {
		shownName = QFileInfo(currentFile).fileName();
	}

	this->setWindowTitle(tr("%1[*] - %2").arg(shownName)
		.arg(tr("KPD")));
}

void KPDGUI::addNode(KPDGUINode * newNode, bool fromSavedFile){

	//qDebug() << "Inserting Node into Record";
	kpdguiRecord->insertNode(newNode, fromSavedFile);
	//qDebug() << "Inserted Node into Record";
	

	////qDebug() << newNode->getNodePosition();

	if (newNode->getType() == PAIR) {
		kpdguiScene->addItem(newNode->getCandidate());
	}

	foreach(KPDGUIDonor * donor, newNode->getDonors()) {
		kpdguiScene->addItem(donor);
	}
	++nodePlacementSequenceNumber;	

	checkNodeMatches(newNode);

	KPDGUINodeWrapper * wrapper = new KPDGUINodeWrapper(newNode);
	ui->nodeList->addTopLevelItem(wrapper);
	
	connect(ui->graphicsView, SIGNAL(mouseReleased()), newNode, SLOT(updateVisibility()));
	//connect(newNode, SIGNAL(nodeEntered(int)), this, SLOT(updateTable(int)));
	//connect(newNode, SIGNAL(nodeLeft(int)), this, SLOT(clearTable()));
	//connect(newNode, SIGNAL(nodeWasClicked(int, bool)), this, SLOT(clickActions(int, bool)));
	
	//connect(ui->graphicsView, SIGNAL(mouseReleased()), wrapper, SLOT(updateSelections()));
	//connect(this, SIGNAL(poolChanged()), wrapper, SLOT(updateText()));
	connect(this, SIGNAL(visibilityChanged(KPDGUIDisplaySettings *)), newNode, SLOT(updateVisibility(KPDGUIDisplaySettings *)));
	////connect(this, SIGNAL(selectAll()), newNode, SLOT(selectIfVisible()));
}

void KPDGUI::addMatch(KPDGUIDonor * donor, KPDGUICandidate * candidate){
	KPDGUIMatch * match = new KPDGUIMatch(donor, candidate);

	candidate->addMatchingDonor(match);
	donor->addMatchingCandidate(match);

	connect(this, SIGNAL(visibilityChanged(KPDGUIDisplaySettings *)), match, SLOT(updateVisibility(KPDGUIDisplaySettings *)));
	//KPDGUIMatchWrapper * wrapper = new KPDGUIMatchWrapper(link);
	//matchListWidget->addTopLevelItem(wrapper);

	kpdguiRecord->insertMatch(match);
	kpdguiScene->addItem(match);

}

void KPDGUI::readPairsFromFile(QString fileName, QString layout)
{
	QVector<QVector<QVector<QString> > > nodeInfo;

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
						if (token.indexOf("\"") == token.length() - 1){
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
			nodeInfo.push_back(row);
		}
		i++;
	}

	int nodesAdded = (int) nodeInfo.size();
	
	qreal dist = 100 + 10 * nodesAdded;
	qreal angle = (2 * PI) / nodesAdded;
	qreal nodeAngle = PI;

	int max = (int) sqrt(nodesAdded) + 1;
	int seq = 0;	

	foreach(QVector<QVector<QString> > line, nodeInfo){

		KPDGUINode * newNode;
		
		bool status = false;
		if (line.at(1).at(0) != "1"){
			status = true;
		}

		KPDGUIDonor * newDonor = new KPDGUIDonor();
		
		qDebug() << "Name: " << line.at(9).at(0);

		newDonor->setName(line.at(9).at(0));
		newDonor->setAge(line.at(11).at(0).toInt());

		//Donor Crossmatch Information
		QVector<QString> hlaA;
		hlaA.push_back(line.at(20).at(0));
		hlaA.push_back(line.at(21).at(0));
		newDonor->setA(hlaA);

		QVector<QString> hlaB;
		hlaB.push_back(line.at(22).at(0));
		hlaB.push_back(line.at(23).at(0));
		newDonor->setB(hlaB);
		
		newDonor->setBW4(line.at(24).at(0) == "BW4");
		newDonor->setBW6(line.at(25).at(0) == "BW6");

		QVector<QString> hlaCW;
		hlaCW.push_back(line.at(26).at(0));
		hlaCW.push_back(line.at(27).at(0));
		newDonor->setCW(hlaCW);

		QVector<QString> hlaDQ;
		hlaDQ.push_back(line.at(33).at(0));
		hlaDQ.push_back(line.at(34).at(0));
		newDonor->setDQ(hlaDQ);
		
		QVector<QString> hlaDR;
		hlaDR.push_back(line.at(28).at(0));
		hlaDR.push_back(line.at(29).at(0));
		newDonor->setDR(hlaDR);
		
		newDonor->setDR51(line.at(30).at(0) == "DR51");
		newDonor->setDR52(line.at(31).at(0) == "DR52");
		newDonor->setDR53(line.at(32).at(0) == "DR53");

		QString donorBT = line.at(12).at(0);
		if (donorBT == "O"){ newDonor->setBT(BT_O); }
		else if (donorBT == "A"){ newDonor->setBT(BT_A); }
		else if (donorBT == "B"){ newDonor->setBT(BT_B); }
		else if (donorBT == "AB"){ newDonor->setBT(BT_AB); }		

		//Pair
		if (line.at(2).at(0).toInt() == 0){
			
			KPDGUICandidate * newCandidate = new KPDGUICandidate();

			newCandidate->setName(line.at(5).at(0));
			newCandidate->setAge(line.at(7).at(0).toInt());

			QString candidateBT = line.at(8).at(0);
			if (candidateBT == "O"){ newCandidate->setBT(BT_O); }
			else if (candidateBT == "A"){ newCandidate->setBT(BT_A); }
			else if (candidateBT == "B"){ newCandidate->setBT(BT_B); }
			else if (candidateBT == "AB"){ newCandidate->setBT(BT_AB); }

			int pra = 0;
			
			for (int row = 14; row <= 15; row++) {
				QString praString = line.at(14).at(0);
				QStringList praList = praString.split('/');

				foreach(QString praToken, praList) {
					int praInt = praToken.toInt();

					if (praInt > pra) {
						pra = praInt;
					}
				}
			}

			newCandidate->setPRA(pra);
			
			QVector<QString> antibodies;
			bool sensitized = (line.at(3).at(0)).toInt() == 1;
			
			if (sensitized == false){
				foreach(QString antibody, line.at(16)){
					if (!antibody.isNull() && antibody != "NONE" && antibody != "NULL" && antibody != "NP"){
						antibodies.push_back(antibody);
					}
				}
				foreach(QString antibody, line.at(17)){
					if (!antibody.isNull() && antibody != "NONE" && antibody != "NULL" && antibody != "NP"){
						antibodies.push_back(antibody);
					}
				}
			}

			foreach(QString antibody, line.at(18)){
				if (!antibody.isNull() && antibody != "NONE" && antibody != "NULL" && antibody != "NP"){
					antibodies.push_back(antibody);
				}
			}

			foreach(QString antibody, line.at(19)){
				if (!antibody.isNull() && antibody != "NONE" && antibody != "NULL" && antibody != "NP"){
					antibodies.push_back(antibody);
				}
			}

			newCandidate->setHLA(antibodies);

			QVector<KPDGUIDonor *> newDonors;
			newDonors << newDonor;
			
			newNode = new KPDGUINode(newDonors, newCandidate);
		}
		else {
			newNode = new KPDGUINode(newDonor);
		}		

		if (layout == "Circle"){
			newNode->setNodePosition(QPointF(dist*cos(nodeAngle), dist*sin(nodeAngle)));
			nodeAngle += angle;
		}
		else {
			int h_offset = rand() % 20 - 10;
			int v_offset = rand() % 20 - 10;
			newNode->setNodePosition(QPointF(100 + 100 * (nodePlacementSequenceNumber % max) + h_offset, 100 + 100 * ((nodePlacementSequenceNumber / max) % max) + v_offset));
			seq++;
		}

		addNode(newNode, false);
	}	
}

void KPDGUI::setDisplaySettings(KPDGUIDisplaySettings * newDisplaySettings){

	emit visibilityChanged(kpdguiDisplaySettings);
}

bool KPDGUI::okToContinue()
{
	if (isWindowModified()) {
		int r = QMessageBox::warning(this, tr("KPD"),
			tr("The document has been modified.\n"
			"Do you want to save your changes?"),
			QMessageBox::Yes | QMessageBox::No
			| QMessageBox::Cancel);
		if (r == QMessageBox::Yes) {
			return saveKPD();
		}
		else if (r == QMessageBox::Cancel) {
			return false;
		}
	}
	return true;
}

void KPDGUI::changeFocus(KPDGUINode * node){
	ui->graphicsView->centerOn(node->getNodePosition());

	setWindowModified(true);
}

void KPDGUI::runSimulation(){

	QApplication::setOverrideCursor(Qt::WaitCursor);
	QApplication::processEvents();

	QProgressDialog * progress = new QProgressDialog("Setting Up Simulation...",QString(),0,100);
	progress->setWindowModality(Qt::WindowModal);
	progress->setWindowTitle("Simulation Progress");
	progress->setAutoClose(false);
	progress->show();
	QApplication::processEvents();

	//Generate Matrices for Simulation
	kpdguiRecord->generateMatrices(kpdguiParameters,progress);

	QString recordLog = kpdguiRecord->getRecordLog();

	//Build New Simulation
	KPDGUISimulation *g = new KPDGUISimulation(kpdguiRecord, kpdguiParameters);

	//Collect All Structures
	KPDOptimizationScheme optScheme = kpdguiParameters->getOptimizationScheme();

	vector<vector<int> > allStructures;
	if (optScheme == KPDOptimizationScheme::SCC){
		allStructures = g->getCurrentMatchRunComponentsNaive(progress);
	}
	else {
		allStructures = g->getCurrentMatchRunCyclesAndChains(progress);
	}

	//Calculate and Collect Utility Values
	vector<double> utilValues;
	if (optScheme == KPDOptimizationScheme::MUC){ utilValues = g->getUtilityForCurrentMatchRunCyclesAndChains(progress); }
	else if (optScheme == KPDOptimizationScheme::MEUC){ utilValues = g->getExpectedUtilityForCurrentMatchRunCyclesAndChains(progress); }
	else if (optScheme == KPDOptimizationScheme::MEUS){ utilValues = g->getExpectedUtilityForCurrentMatchRunSets(progress); }
	else if (optScheme == KPDOptimizationScheme::SCC){ utilValues = g->getExpectedUtilityForCurrentMatchRunComponents(progress); }

	//Run Simulation
	g->getOptimalSolutionForCurrentMatchRun(progress);

	//Collect Solution Set and Solution Objectives
	vector<vector<int> > solutionSet = g->returnSolutionSet();
	vector<double> solutionObjectives = g->returnSolutionObjectives();

	int progressBarValue = 0;
	progress->setRange(0, (int)(2 * solutionSet.size() + allStructures.size())); // +ui->nodeList->topLevelItemCount())); // + matchListWidget->topLevelItemCount()
	progress->setLabelText("Saving Structures...");
	progress->setValue(progressBarValue);
	QApplication::processEvents();

	//Create Timestamp
	QString timestamp = QDate::currentDate().toString() + " " + QTime::currentTime().toString();
	//Get Simulation Log
	QString simLog = g->getSimLog();

	//Initialize Structure List and Collection of Solution Lists
	KPDGUIStructureSet * structureList = new KPDGUIStructureSet(kpdguiParameters, timestamp, recordLog, simLog, false);
	QVector<KPDGUIStructureSet *> solutionLists;

	int sol = 0;
	for (vector<vector<int> >::iterator it = solutionSet.begin(); it != solutionSet.end(); ++it){
		sol++;
		solutionLists.push_back(new KPDGUIStructureSet(kpdguiParameters, timestamp, recordLog, simLog, true, sol));

		progressBarValue++;
		progress->setValue(progressBarValue);
		QApplication::processEvents();
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
			int id = kpdguiRecord->getNodeInfoVector()[allStructures[itStruct][itNode]].nodeID;
			//Collect Node Object based on Pair ID
			KPDGUINode * node = kpdguiRecord->getNode(id);
			if (node->getType() == AD){
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
		structureList->addStructure(newStructure);

		//Iterate Through Solutions
		for (int itSolution = 0; itSolution < solutionSet.size(); itSolution++){
			//If Current Structure is Found in Current Solution
			if (std::find(solutionSet[itSolution].begin(), solutionSet[itSolution].end(), itStruct) != solutionSet[itSolution].end()){
				solutionLists[itSolution]->addStructure(newStructure);
			}
		}

		progressBarValue++;
		progress->setValue(progressBarValue);
		QApplication::processEvents();
	}

	//Collapse all Current Solutions Shown In the Widget
	ui->solutionWidget->collapseAll();

	//Reset Popularity Values in The Node List Widget and Edge List Widget
/*	for (int i = 0; i < ui->nodeList->topLevelItemCount(); i++){
		KPDGUINodeWrapper * wrapper = dynamic_cast<KPDGUINodeWrapper *>(ui->nodeList->topLevelItem(i));
		if (wrapper){
			wrapper->getNode()->resetPopularityInStructures();
		}
		progressBarValue++;
		progress->setValue(progressBarValue);
		QApplication::processEvents();
	}*/
	/*for (int i = 0; i < matchListWidget->topLevelItemCount(); i++){
		KPDGUIMatchWrapper * wrapper = dynamic_cast<KPDGUIMatchWrapper *>(ui->nodeList->topLevelItem(i));
		if (wrapper){
			wrapper->getArrow()->resetPopularityInStructures();
		}
		progressBarValue++;
		progress->setValue(progressBarValue);
		QApplication::processEvents();
	}*/
	//Update Popularity of Structure
	structureList->updatePopularity();
	//Add Structure to Structure Widget and Expand
	ui->structureWidget->insertTopLevelItem(0, structureList);
	
	structureList->sort();
	structureList->setExpanded(true);
	

	//Add Solutions to Solution Widget
	int level = 0;
	foreach(KPDGUIStructureSet * structureSet, solutionLists){
		structureSet->updatePopularity();
		ui->solutionWidget->insertTopLevelItem(level, structureSet);
		structureSet->setExpanded(true);
		level++;

		structureSet->sort();

		progressBarValue++;
		progress->setValue(progressBarValue);
		QApplication::processEvents();
	}

	//Parameters Have Not Been Set For Next Simulation
	kpdguiParameters->setParametersHaveBeenUpdated(false);

	//Switch Tab to "Solution" Tab
	//ui->tabWidget->setCurrentIndex(3);

	//Sort Matches Based on Solution Popularity
	//setMatchSortMode(0, true);
	//matchSortMode = MATCHSORT_POPULARITY_SOLUTIONS;
	//matchSortDecreasing = true;
	//sort();

	QApplication::restoreOverrideCursor();
	QApplication::processEvents();

	progress->close();
	QApplication::processEvents();

	ui->actionView_Structures_Solutions->setChecked(true);

	delete g;
	delete progress;	

	
}


void KPDGUI::editDonor(){
	QList<QGraphicsItem*> items = kpdguiScene->selectedItems();
	if (items.size() == 1){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(items.first());
		if (node){

			DialogDonor * dialogDonor = new DialogDonor(node->getFirstDonor(), true, this);

			if (dialogDonor->exec()) {
				//qDebug() << "Edit Donor " << node->getID();
			}			
		}
	}
}

void KPDGUI::editCandidate(){
	QList<QGraphicsItem*> items = kpdguiScene->selectedItems();
	if (items.size() == 1){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(items.first());
		if (node){

			DialogCandidate * dialogCandidate = new DialogCandidate(node->getCandidate(), true, this);

			if (dialogCandidate->exec()){
				//qDebug() << "Edit Candidate " << node->getID();
			}
		}
	}
}

void KPDGUI::holdNode(){
	QList<QGraphicsItem*> items = kpdguiScene->selectedItems();
	KPDGUINode *node = dynamic_cast<KPDGUINode *>(items.first());
	if (node){
		//node->setNodeStatus(true);
		updateVisibility();
	}
}

void KPDGUI::unholdNode(){
	QList<QGraphicsItem*> items = kpdguiScene->selectedItems();
	KPDGUINode *node = dynamic_cast<KPDGUINode *>(items.first());
	if (node){
		//node->setNodeStatus(false);
		updateVisibility();
	}
}

void KPDGUI::deleteNode(){

	int r = QMessageBox::warning(0, "KPD", "Clicking 'Yes' will remove selected pair from pool and all previously found solutions permanently.\nAre you sure you want to delete selected pair?",
		QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	if (r == QMessageBox::Yes) {
		QList<QGraphicsItem*> items = kpdguiScene->selectedItems();
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(items.first());
		if (node){
			//emit deleteNode(node->getID());
		}
	}
}

void KPDGUI::holdMultipleNodes(){
	QList<QGraphicsItem*> items = kpdguiScene->selectedItems();
	foreach(QGraphicsItem * item, items){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
		if (node){
			//node->setNodeStatus(true);
			updateVisibility();
		}
	}
}

void KPDGUI::unholdMultipleNodes(){
	QList<QGraphicsItem*> items = kpdguiScene->selectedItems();
	foreach(QGraphicsItem * item, items){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
		if (node){
			//node->setNodeStatus(false);
			updateVisibility();
		}
	}
}

void KPDGUI::clusterMultipleNodes(){

	QList<QGraphicsItem*> items = kpdguiScene->selectedItems();

	qreal avgx = 0;
	qreal avgy = 0;
	qreal dist = 50 + 10 * items.size();

	
	foreach(QGraphicsItem * item, items){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
		if (node){
			avgx += node->getNodePosition().x();
			avgy += node->getNodePosition().y();
		}
	}

	qreal x = avgx / items.size();
	qreal y = avgy / items.size();

	qreal angle = (2 * PI) / items.size();
	qreal nodeAngle = PI;

	QApplication::setOverrideCursor(Qt::WaitCursor);
	QApplication::processEvents();

	foreach(QGraphicsItem * item, items){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
		if (node){
			//node->setVisible(false);
			if (!(abs((node->getNodePosition().x()) - (x + dist*cos(nodeAngle))) < TOL && abs((node->getNodePosition().y()) - (y + dist*sin(nodeAngle)) < TOL))){
				node->setNodePosition(QPoint(x + dist*cos(nodeAngle), y + dist*sin(nodeAngle)));
			}
			nodeAngle += angle;
			//node->setVisible(true);
			node->setSelected(true);
		}
	}

	QApplication::restoreOverrideCursor();
	QApplication::processEvents();
}

void KPDGUI::deleteMultipleNodes(){

	int r = QMessageBox::warning(0, "KPD", "Clicking \"Yes\" will remove selected pairs from pool and all previously found solutions permanently.\nAre you sure you want to delete selected pairs?",
		QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	if (r == QMessageBox::Yes) {
		/*QApplication::setOverrideCursor(Qt::WaitCursor);
		QApplication::processEvents();
		QList<QGraphicsItem*> items = kpdguiScene->selectedItems();
		foreach(QGraphicsItem * item, items){
			KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
			if (node){
				node->setSelected(false);
			}
		}
		foreach(QGraphicsItem * item, items){
			KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
			if (node){
				//emit deleteNode(node->getID());
			}
		}
		QApplication::restoreOverrideCursor();
		QApplication::processEvents();*/
	}
}

void KPDGUI::checkNodeMatches(KPDGUINode * node) {
	foreach(KPDGUINode *comparisonNode, kpdguiRecord->getNodes()) {
		if (comparisonNode->getType() == PAIR) {
			foreach(KPDGUIDonor * donor, node->getDonors()) {
				if (kpdguiRecord->isMatch(donor, comparisonNode->getCandidate(), false, false)) {
					addMatch(donor, comparisonNode->getCandidate());
				}
			}
		}
		if (node->getType() == PAIR) {
			foreach(KPDGUIDonor * comparisonDonor, comparisonNode->getDonors()) {
				if (kpdguiRecord->isMatch(comparisonDonor, node->getCandidate(), false, false)) {
					addMatch(comparisonDonor, node->getCandidate());
				}
			}
		}
	}
}

void KPDGUI::updateStatus(QString message){

	statusBar()->showMessage(message, STATUS_TIME);
	ui->dashboard->appendDashboardText(message);
}


void KPDGUI::readSettings()
{

}

void KPDGUI::writeSettings()
{

}



