
#include "ui_KPDGUI.h"

#include "KPDGUI.h"

KPDGUI::KPDGUI(QWidget *parent) : QMainWindow(parent), ui(new Ui::KPDGUI)
{
    ui->setupUi(this);

	initializeParameters();	
	setUpKPDObjects();
	setUpLists();
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
	nodeList = new KPDGUINodeList();

	ui->nodeAndMatchWidget->insertTab(1, nodeList, "Pairings/ADs");

	
	//connect(ui->nodeList, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(clickActions(QTreeWidgetItem*)));
	//connect(ui->nodeList, SIGNAL(mouseReleased()), this, SLOT(newPairListSelectionActions()));
	//connect(ui->nodeList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(pairListCustomMenu(QPoint)));
	


	//Structure Tree
	ui->structureWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	//connect(ui->structureWidget, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this, SLOT(structureTreeSelectionActions(QTreeWidgetItem*)));
	//connect(ui->structureWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(structureTreeCustomMenu(QPoint)));
	
	//Solution Tree
	ui->solutionWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	//connect(ui->solutionWidget, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this, SLOT(solutionTreeSelectionActions(QTreeWidgetItem*)));
	//connect(ui->solutionWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(solutionTreeCustomMenu(QPoint)));
	
	ui->structureWidget->setVisible(false);
	ui->solutionWidget->setVisible(false);
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
		dialogDonor->setWindowTitle("Add New Donor");

		if (dialogDonor->exec()) {

			QVector<KPDGUIDonor *> associatedDonors;
			
			KPDGUIDonor * donor = new KPDGUIDonor(dialogDonor);
			associatedDonors.push_back(donor);

			int additionalDonorMessage = QMessageBox::warning(this, tr("KPD"),
				"New Pairing Contains a Single Donor. Add Another Donor to Pairing?",
				QMessageBox::Yes | QMessageBox::No);
			
			while (additionalDonorMessage == QMessageBox::Yes) {

				DialogDonor * additionalDialogDonor = new DialogDonor(this);
				additionalDialogDonor->setWindowTitle("Add Additional Donor");

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

	updateVisibility();
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

void KPDGUI::updateVisibility(){
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

	newNode->clusterNode();

	++nodePlacementSequenceNumber;	

	checkNodeMatches(newNode);

	KPDGUINodeWrapper * wrapper = new KPDGUINodeWrapper(newNode);
	nodeList->addTopLevelItem(wrapper);
	
	connect(ui->graphicsView, SIGNAL(mouseReleased()), newNode, SLOT(updateVisibility()));
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



