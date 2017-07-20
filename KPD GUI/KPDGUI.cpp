
#include "ui_KPDGUI.h"

#include "KPDGUI.h"

KPDGUI::KPDGUI(QWidget *parent) : QMainWindow(parent), ui(new Ui::KPDGUI)
{
    ui->setupUi(this);

	//Initialize parameters
	setCurrentFile("");
	previousSliderPosition = 0;

	baselineID = 1;
	
	//Set up views
	kpdguiScene = new KPDGUIGraphicsScene();
	ui->kpdGraphicsView->setScene(kpdguiScene);

	kpdguiCommandHistory = new KPDGUICommandHistory();
	kpdguiNodeList = new KPDGUIDashboardList(NODE);
	kpdguiDonorList = new KPDGUIDashboardList(DONOR);
	kpdguiCandidateList = new KPDGUIDashboardList(CANDIDATE);	
	kpdguiMatchList = new KPDGUIDashboardList(MATCH);
	kpdguiArrangementList = new QTreeWidget();
	kpdguiSolutionList = new QTreeWidget();

	kpdguiArrangementList->setHeaderHidden(true);
	kpdguiSolutionList->setHeaderHidden(true);

	ui->kpdListView->insertTab(1, kpdguiCommandHistory, "History");
	ui->kpdListView->insertTab(2, kpdguiNodeList, "Pairings/NDDs");
	ui->kpdListView->insertTab(3, kpdguiDonorList, "Donors");
	ui->kpdListView->insertTab(4, kpdguiCandidateList, "Candidates");
	ui->kpdListView->insertTab(5, kpdguiMatchList, "Matches");
	ui->kpdListView->insertTab(6, kpdguiArrangementList, "Possible Exchanges");
	ui->kpdListView->insertTab(7, kpdguiSolutionList, "Solutions");

	connect(kpdguiArrangementList, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this, SLOT(arrangementListClickActions(QTreeWidgetItem *)));
	connect(kpdguiArrangementList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(arrangementListDoubleClickActions(QTreeWidgetItem*)));

	connect(kpdguiSolutionList, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this, SLOT(solutionListClickActions(QTreeWidgetItem *)));
	connect(kpdguiSolutionList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(solutionListDoubleClickActions(QTreeWidgetItem*)));


	//Set up defaults
	kpdguiDisplaySettings = new KPDGUIDisplaySettings();
	kpdguiCrossmatchFunctions = new KPDGUICrossmatchFunctions();
	kpdguiParameters = new KPDGUIParameters();

	//Group actions
	displayMatchesActionGroup = new QActionGroup(this);
	displayMatchesActionGroup->addAction(ui->actionDisplayCompatibilitiesWithinSelection);
	displayMatchesActionGroup->addAction(ui->actionDisplaySelectedCompatibilities);
	displayMatchesActionGroup->addAction(ui->actionDisplayAllCompatibilities);
	displayMatchesActionGroup->addAction(ui->actionDisplayNoCompatibilities);

	//Set up slider
	zoomSlider = new QSlider();
	zoomSlider->setMinimumSize(QSize(84, 24));
	zoomSlider->setMaximumSize(QSize(84, 24));
	zoomSlider->setMinimum(MINIMUM_SLIDER_POSITION);
	zoomSlider->setMaximum(MAXIMUM_SLIDER_POSITION);
	zoomSlider->setValue(0);
	zoomSlider->setOrientation(Qt::Horizontal);
	zoomSlider->setTickPosition(QSlider::TicksBelow);
	connect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoom(int)));

	//Set up toolbar
	ui->toolBar->insertWidget(ui->actionZoomIn, zoomSlider);
	ui->actionMouseTool->setChecked(true);	
	
	updateStatus("Welcome to KPDGUI - " + QDate::currentDate().toString() + " " + QTime::currentTime().toString() + "\n");	
}

KPDGUI::~KPDGUI()
{
    delete ui;
}

void KPDGUI::newKPD()
{
    KPDGUI *mainWin = new KPDGUI;
    mainWin->show();
}

void KPDGUI::openKPD()
{
	bool open = true;

	if (isWindowModified()) {
		int r = QMessageBox::warning(this, tr("KPD"),
			tr("The document has been modified.\n"
				"Do you want to save your changes?"),
			QMessageBox::Yes | QMessageBox::No
			| QMessageBox::Cancel);
		if (r == QMessageBox::Yes) {
			open = saveKPD();
		}
		else if (r == QMessageBox::Cancel) {
			open = false;
		}
	}

    if (open) {
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
	// First get info about the candidate
	DialogCandidate * dialogCandidate = new DialogCandidate(this);

	if (dialogCandidate->exec()) {
		
		// Then get info about the first donor		
		DialogDonor * dialogDonor = new DialogDonor(true, this);
		dialogDonor->setWindowTitle("Add New Donor");

		// If both a valid donor and candidate dialog have been submitted...
		if (dialogDonor->exec()) {

			// Create candidate
			KPDGUICandidate * candidate = new KPDGUICandidate(dialogCandidate);

			// Create first donor
			KPDGUIDonor * donor = new KPDGUIDonor(dialogDonor);
			
			// Store donors
			QVector<KPDGUIDonor *> associatedDonors;
			associatedDonors.push_back(donor);

			// Repeat for additional donors
			while (dialogDonor->getAdditionalDonor()){

				dialogDonor = new DialogDonor(true, this);
				dialogDonor->setWindowTitle("Add New Additional Donor");

				if (dialogDonor->exec()){
					KPDGUIDonor * additionalDonor = new KPDGUIDonor(dialogDonor);
					associatedDonors.push_back(additionalDonor);
				}
				else {
					break;
				}
			}

			
			QVector<KPDCrossmatchResult> crossmatchResults;

			foreach(KPDGUIDonor * donor, associatedDonors) {
				KPDCrossmatchResult result = kpdguiCrossmatchFunctions->performCrossmatch(donor, candidate);
				crossmatchResults << result;
			}

			// Create node
			KPDGUINode * newNode = new KPDGUINode(associatedDonors, candidate, crossmatchResults);

			foreach(KPDGUIDonor * donor, associatedDonors) {
				donor->setParentNode(newNode);
			}

			// Insert node
			insertNode(newNode);

			// Add to scene
			kpdguiScene->addNode(newNode);

			// Select new node
			newNode->setSelected(true);

			// Focus on the new node
			ui->kpdGraphicsView->centerOn(newNode->getNodePosition());

			// Alert
			emit nodesAdded();
			emit displaySettingsChanged(kpdguiDisplaySettings);

			updateStatus("Added New Pairing: " + newNode->getNameString());
			setWindowModified(true);
		}

		// In the case where a candidate dialog is submitted, but the donor dialog is cancelled
		else {
			QMessageBox::about(this, tr("About KPDGUI"),"No donors added. Pairing will not be created");
		}
	}
}

void KPDGUI::addNewNDD()
{
	DialogDonor * dialogNDD = new DialogDonor(this);

	if (dialogNDD->exec()) {

		// Create NDD
		KPDGUIDonor * nonDirectedDonor = new KPDGUIDonor(dialogNDD);

		// Create node
		KPDGUINode * newNode = new KPDGUINode(nonDirectedDonor);

		nonDirectedDonor->setParentNode(newNode);

		// Insert node
		insertNode(newNode);

		// Add to scene
		kpdguiScene->addNode(newNode);

		// Focus on the new node
		ui->kpdGraphicsView->centerOn(newNode->getNodePosition());
		
		// Select new node
		newNode->setSelected(true);

		// Alert
		emit nodesAdded();
		emit displaySettingsChanged(kpdguiDisplaySettings);

		updateStatus("Added New Altrustic Donor: " + newNode->getNameString());
		setWindowModified(true);
	}
}

void KPDGUI::loadNodes()
{
	ReadFileDialog readFileDialog(this);

	if (readFileDialog.exec()) {
		QApplication::setOverrideCursor(Qt::WaitCursor);
		QApplication::processEvents();
		
		// Get file and layout information
		QString fileName = readFileDialog.pairFileLineEdit->text();
		QString layout = readFileDialog.layoutComboBox->currentText();

		QVector<QVector<QVector<QString> > > nodeInfo = KPDFunctions::loadData(fileName, true);
		
		// Load pairs from file
		QVector<KPDGUINode *> nodesToAdd;

		foreach(QVector<QVector<QString> > line, nodeInfo) {

			KPDGUINode * newNode;

			bool status = true;
			if (line.at(1).at(0) != "1") {
				status = false;
			}

			KPDGUIDonor * newDonor = new KPDGUIDonor();

			newDonor->setName(line.at(6).at(0));
			newDonor->setAge(line.at(7).at(0).toInt());

			//Donor Crossmatch Information

			QString donorBT = line.at(8).at(0);
			if (donorBT == "O") { newDonor->setBT(BT_O); }
			else if (donorBT == "A") { newDonor->setBT(BT_A); }
			else if (donorBT == "B") { newDonor->setBT(BT_B); }
			else if (donorBT == "AB") { newDonor->setBT(BT_AB); }

			QVector<QString> hlaA;
			hlaA.push_back(line.at(12).at(0));
			hlaA.push_back(line.at(13).at(0));
			newDonor->setA(hlaA);

			QVector<QString> hlaB;
			hlaB.push_back(line.at(14).at(0));
			hlaB.push_back(line.at(15).at(0));
			newDonor->setB(hlaB);

			newDonor->setBW4(line.at(16).at(0) == "BW4");
			newDonor->setBW6(line.at(17).at(0) == "BW6");

			QVector<QString> hlaCW;
			hlaCW.push_back(line.at(18).at(0));
			hlaCW.push_back(line.at(19).at(0));
			newDonor->setCW(hlaCW);

			QVector<QString> hlaDQ;
			hlaDQ.push_back(line.at(25).at(0));
			hlaDQ.push_back(line.at(26).at(0));
			newDonor->setDQ(hlaDQ);

			QVector<QString> hlaDR;
			hlaDR.push_back(line.at(20).at(0));
			hlaDR.push_back(line.at(21).at(0));
			newDonor->setDR(hlaDR);

			newDonor->setDR51(line.at(22).at(0) == "DR51");
			newDonor->setDR52(line.at(23).at(0) == "DR52");
			newDonor->setDR53(line.at(24).at(0) == "DR53");

			//Characteristics

			newDonor->setMale(line.at(36).at(0) == "M");

			QString donorRace = line.at(37).at(0);
			if (donorRace == "White") {
				newDonor->setRace(RACE_WHITE);
			}
			else if (donorRace == "Black") {
				newDonor->setRace(RACE_BLACK);
			}
			else if (donorRace == "Hispanic") {
				newDonor->setRace(RACE_HISPANIC);
			}
			else {
				newDonor->setRace(RACE_OTHER);
			}

			newDonor->setHeight(line.at(38).at(0).toDouble());
			newDonor->setWeight(line.at(39).at(0).toDouble());
			newDonor->setCigarette(line.at(40).at(0) == "Y");

			newDonor->setStatus(status);

			//Pair
			if (line.at(2).at(0).toInt() == 0) {

				KPDGUICandidate * newCandidate = new KPDGUICandidate();

				newCandidate->setName(line.at(3).at(0));
				newCandidate->setAge(line.at(4).at(0).toInt());

				//Crossmatch Information

				QString candidateBT = line.at(5).at(0);
				if (candidateBT == "O") { newCandidate->setBT(BT_O); }
				else if (candidateBT == "A") { newCandidate->setBT(BT_A); }
				else if (candidateBT == "B") { newCandidate->setBT(BT_B); }
				else if (candidateBT == "AB") { newCandidate->setBT(BT_AB); }

				newCandidate->setPRA(line.at(9).at(0).toInt());

				QVector<QString> antibodies;

				foreach(QString antibody, line.at(10)) {
					antibodies.push_back(antibody);
				}
				foreach(QString antibody, line.at(11)) {
					antibodies.push_back(antibody);
				}

				newCandidate->setHLA(antibodies);

				//Characteristics

				newCandidate->setMale(line.at(27).at(0) == "M");

				QString candidateRace = line.at(28).at(0);
				if (candidateRace == "White") {
					newCandidate->setRace(RACE_WHITE);
				}
				else if (candidateRace == "Black") {
					newCandidate->setRace(RACE_BLACK);
				}
				else if (candidateRace == "Hispanic") {
					newCandidate->setRace(RACE_HISPANIC);
				}
				else {
					newCandidate->setRace(RACE_OTHER);
				}

				newCandidate->setDiabetes(line.at(29).at(0) == "Y");
				newCandidate->setHeight(line.at(30).at(0).toDouble());
				newCandidate->setWeight(line.at(31).at(0).toDouble());
				newCandidate->setPrevTrans(line.at(32).at(0) == "Y");
				newCandidate->setTOD(line.at(33).at(0).toDouble());
				newCandidate->setHepC(line.at(34).at(0) == "Y");

				QString candidateInsurance = line.at(35).at(0);
				if (candidateInsurance == "Public") {
					newCandidate->setInsurance(PUBLIC);
				}
				else if (candidateInsurance == "Private") {
					newCandidate->setInsurance(PRIVATE);
				}
				else {
					newCandidate->setInsurance(OTHER_INSURANCE);
				}

				newCandidate->setStatus(status);

				QVector<KPDGUIDonor *> newDonors;
				newDonors << newDonor;

				QVector<KPDCrossmatchResult> crossmatchResults;
				foreach(KPDGUIDonor * donor, newDonors) {
					KPDCrossmatchResult result = kpdguiCrossmatchFunctions->performCrossmatch(donor, newCandidate);
					crossmatchResults << result;
				}

				newNode = new KPDGUINode(newDonors, newCandidate, crossmatchResults);
			}
			else {
				newNode = new KPDGUINode(newDonor);
			}

			newDonor->setParentNode(newNode);

			nodesToAdd << newNode;
		}

		// Insert nodes
		foreach(KPDGUINode * node, nodesToAdd) {
			insertNode(node);
		}

		// Add to scene
		kpdguiScene->addNodes(nodesToAdd, layout);

		// Alert
		emit nodesAdded();
		emit displaySettingsChanged(kpdguiDisplaySettings);

		QApplication::restoreOverrideCursor();
		QApplication::processEvents();

		QStringList fileNameReduced = fileName.split("/");
		updateStatus("Loaded Pairs From " + fileNameReduced.last());

		setWindowModified(true);
	}
}

void KPDGUI::exitProgram()
{
	qApp->closeAllWindows();
}

void KPDGUI::performMatchRun()
{
	bool proceed = true;

	if (!kpdguiParameters->parametersHaveBeenUpdated()) {
		int r = QMessageBox::warning(this, tr("KPD"),
			tr("The pool has been modified since the last time parameters were set. Set parameters now?"),
			QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		if (r == QMessageBox::Yes) {
			proceed = setSimParameters();
		}
		else if (r == QMessageBox::Cancel) {
			proceed = false;
		}
	}
	
	if (proceed) {
		
		updateStatus("Performing Match Run...");

		// Perform match run
		KPDGUIMatchRun * matchRun = new KPDGUIMatchRun(getNodes(), kpdguiParameters);

		// Set time stamp and collect match run text
		QString timestamp = QDate::currentDate().toString() + " " + QTime::currentTime().toString();
		QString matchRunText = matchRun->printLog();

		// Official results
		QVector<KPDGUIArrangement *> officialArrangements;
		QVector<KPDGUIArrangementSet *> officialSolutions;

		// Collect arrangement information from match run
		QVector<QVector<KPDGUINode *> > arrangementNodes = matchRun->getMatchRunArrangementNodes();
		QVector<QVector<KPDGUIMatch *> > arrangementMatches = matchRun->getMatchRunArrangementMatches();
		QVector<double> arrangementValues = matchRun->getAssignedValueOfMatchRunArrangements();

		QVector<QVector<int> > solutions = matchRun->getMatchRunSelectedSolutions();
		QVector<double> solutionValues = matchRun->getAssignedValueOfMatchRunSolutions();

		// Go through arrangements from match run
		int i = 1;
		foreach(QVector<KPDGUINode *> arrangement, arrangementNodes) {
			
			// Get arrangement value
			double currentArrangementValue = arrangementValues[i - 1];

			// Create new arrangement
			KPDGUIArrangement * newArrangement = new KPDGUIArrangement(currentArrangementValue, QString::number(i));

			// Add nodes to arrangement
			foreach (KPDGUINode * node, arrangement) {				
				newArrangement->addNode(node);
			}

			// Add relevant matches to arrangement
			foreach (KPDGUIMatch * match, arrangementMatches[i - 1]) {
				newArrangement->addMatch(match);
			}

			// Add to official arrangements
			officialArrangements << newArrangement;

			i++;
		}

		// Create new arrangement set
		KPDGUIArrangementSet * matchRunArrangements = new KPDGUIArrangementSet(kpdguiParameters, timestamp, matchRunText, false);
		
		// Add official arrangements to arrangement set
		foreach(KPDGUIArrangement * arrangement, officialArrangements) {

			matchRunArrangements->addArrangement(arrangement);

			updateStatus(arrangement->arrangementDashboardString());
		}

		// Increase popularity
		matchRunArrangements->increasePopularity();

		// Add to dashboard
		kpdguiArrangementList->insertTopLevelItem(0, matchRunArrangements);
		matchRunArrangements->setExpanded(true);

		// Print to dashboard
		updateStatus("Match Run Arrangements:");
		updateStatus(matchRunArrangements->getDashboardString());

		
		// Go through solutions
		int p = 1;
		foreach(QVector<int> solution, solutions) {

			// Need to copy the parameters
			KPDGUIParameters * parameters = new KPDGUIParameters();
			parameters->copyParameters(kpdguiParameters);

			KPDGUIArrangementSet * newSolution = new KPDGUIArrangementSet(parameters, timestamp, matchRunText, true, p);

			foreach(int arrangementID, solution) {

				newSolution->addArrangement(officialArrangements[arrangementID]);

			}

			newSolution->increasePopularity();

			officialSolutions << newSolution;

			kpdguiSolutionList->insertTopLevelItem(0, newSolution);
			newSolution->setExpanded(true);
			

			updateStatus(newSolution->getDashboardString());

			p++;
		}

		kpdguiParameters->setParametersHaveBeenUpdatedFlag(false);

		emit matchRunCompleted();

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
		kpdguiParameters->setParametersHaveBeenUpdatedFlag(true);
		updateStatus("Set New Parameters");		

		return true;
	}

	return false;
}

void KPDGUI::clearArrangements() {
	int r = QMessageBox::warning(this, tr("KPD"),
		tr("Remove Found Arrangements?"),
		QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	if (r == QMessageBox::Yes) {

		kpdguiArrangementList->clear();

		updateStatus("Arrangements Cleared");

		setWindowModified(true);
	}
}

void KPDGUI::clearSolutions(){
	int r = QMessageBox::warning(this, tr("KPD"),
		tr("Remove Solutions?"),
		QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	if (r == QMessageBox::Yes) {
		
		kpdguiSolutionList->clear();

		updateStatus("Solutions Cleared");

		setWindowModified(true);
	}
}

bool KPDGUI::changeNodeViewMode()
{
	DialogDisplaySettings * displayDialog = new DialogDisplaySettings(kpdguiDisplaySettings);

	if (displayDialog->exec()) {
		bool settingsChanged = kpdguiDisplaySettings->changeDisplaySettings(displayDialog);

		if (settingsChanged) {
			emit displaySettingsChanged(kpdguiDisplaySettings);
			return true;
		}

	}

	return false;
}

void KPDGUI::changeMatchViewMode_Within()
{
	kpdguiDisplaySettings->setMatchDisplayMode(WITHIN_SELECTION);
	emit displaySettingsChanged(kpdguiDisplaySettings);	
}

void KPDGUI::changeMatchViewMode_SelectedCompatibilities()
{
	kpdguiDisplaySettings->setMatchDisplayMode(SELECTED_COMPATIBILITIES);
	emit displaySettingsChanged(kpdguiDisplaySettings);
}

void KPDGUI::changeMatchViewMode_All()
{
	kpdguiDisplaySettings->setMatchDisplayMode(ALL_COMPATIBILITIES);
	emit displaySettingsChanged(kpdguiDisplaySettings);	
}

void KPDGUI::changeMatchViewMode_None()
{
	kpdguiDisplaySettings->setMatchDisplayMode(NO_COMPATIBILITIES);
	emit displaySettingsChanged(kpdguiDisplaySettings);	
}

void KPDGUI::runSurvivalCalculator() {

	DialogSurvivalCalculator * dialog = new DialogSurvivalCalculator(kpdguiDonorList, kpdguiCandidateList, kpdguiCrossmatchFunctions, this);

	if (dialog->exec()) {

		kpdguiCommandHistory->appendCommand("Ran Survival Calculator");

	}

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
	ui->kpdGraphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

	if (tick > previousSliderPosition){
		for (int i = 0; i < (tick - previousSliderPosition); i++){
			ui->kpdGraphicsView->scale(scaleFactor, scaleFactor);
		}
	}
	else if (tick < previousSliderPosition){
		for (int i = 0; i < (previousSliderPosition - tick); i++){
			ui->kpdGraphicsView->scale(1 / scaleFactor, 1 / scaleFactor);
		}
	}
	previousSliderPosition = tick;
}

void KPDGUI::changeToMouseMode(){
	ui->actionHandTool->setChecked(false);
	ui->actionMouseTool->setChecked(true);

	ui->kpdGraphicsView->setDragMode(QGraphicsView::RubberBandDrag);
	ui->kpdGraphicsView->setCursor(Qt::ArrowCursor);
	ui->kpdGraphicsView->changeMode(0);
}

void KPDGUI::changeToHandMode(){
	ui->actionHandTool->setChecked(true);
	ui->actionMouseTool->setChecked(false);

	ui->kpdGraphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
	ui->kpdGraphicsView->setCursor(Qt::OpenHandCursor);
	ui->kpdGraphicsView->changeMode(1);
}

void KPDGUI::aboutKPD()
{
	QMessageBox::about(this, tr("About KPDGUI"),
		tr("<h2>KPDGUI 2.1</h2>"
		"<p>Author: Mathieu Bray"
		"<p>2016"));
}


void KPDGUI::closeEvent(QCloseEvent *event)
{
	bool close = true;

	if (isWindowModified()) {
		int r = QMessageBox::warning(this, tr("KPD"),
			tr("The document has been modified.\n"
				"Do you want to save your changes?"),
			QMessageBox::Yes | QMessageBox::No
			| QMessageBox::Cancel);
		if (r == QMessageBox::Yes) {
			close = saveKPD();
		}
		else if (r == QMessageBox::Cancel) {
			close = false;
		}
	}

	if (close) {
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

void KPDGUI::updateStatus(QString message){

	statusBar()->showMessage(message, STATUS_TIME);
	kpdguiCommandHistory->appendCommand(message);
}


KPDGUINode * KPDGUI::getNode(int nodeID) {
	if (nodes.keys().contains(nodeID)) {
		return nodes[nodeID];
	}
	else {
		return NULL;
	}
}

QList<KPDGUINode *> KPDGUI::getNodes() {
	return nodes.values();
}

QVector<KPDGUIMatch *> KPDGUI::getMatches(int id) {
	return donorMatches[id];
}

void KPDGUI::insertNode(KPDGUINode * node) {

	node->setID(baselineID);
	baselineID++;

	nodes.insert(node->getID(), node);

	//QObject::connect(node->getCandidate(), SIGNAL(nodeWasClicked(int, bool)), this, SLOT(nodeClickActions(int, bool)));
	foreach(KPDGUIDonor * donor, node->getDonors()) {
		QObject::connect(donor, SIGNAL(donorSelectionChanged(int, int, bool)), this, SLOT(donorSelectionActions(int, int, bool)));

		KPDGUIDonorWrapper * donorWrapper = new KPDGUIDonorWrapper(donor);
		kpdguiDonorList->addTopLevelItem(donorWrapper);


		QObject::connect(this, SIGNAL(nodesAdded()), donorWrapper, SLOT(updateText()));
		QObject::connect(this, SIGNAL(matchRunCompleted()), donorWrapper, SLOT(updateText()));

		QObject::connect(kpdguiDonorList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), donorWrapper, SLOT(donorWrapperDoubleClickActions(QTreeWidgetItem*)));

	}	
	if (node->getType() == PAIR) {
		QObject::connect(node->getCandidate(), SIGNAL(candidateSelectionChanged(int, bool)), this, SLOT(candidateSelectionActions(int, bool)));
		//QObject::connect(node, SIGNAL(nodeWasEdited(int)), this, SLOT(nodeEditActions(int)));

		KPDGUICandidateWrapper * candidateWrapper = new KPDGUICandidateWrapper(node->getCandidate());
		kpdguiCandidateList->addTopLevelItem(candidateWrapper);

		QObject::connect(this, SIGNAL(nodesAdded()), candidateWrapper, SLOT(updateText()));
		QObject::connect(this, SIGNAL(matchRunCompleted()), candidateWrapper, SLOT(updateText()));

		QObject::connect(kpdguiCandidateList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), candidateWrapper, SLOT(candidateWrapperDoubleClickActions(QTreeWidgetItem*)));
	}	

	QObject::connect(this, SIGNAL(displaySettingsChanged(KPDGUIDisplaySettings *)), node, SLOT(updateVisibility(KPDGUIDisplaySettings *)));


	KPDGUINodeWrapper * nodeWrapper = new KPDGUINodeWrapper(node);
	kpdguiNodeList->addTopLevelItem(nodeWrapper);

	nodeWrapperMap.insert(node, nodeWrapper);

	QObject::connect(kpdguiNodeList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), nodeWrapper, SLOT(nodeWrapperDoubleClickActions(QTreeWidgetItem*)));
	QObject::connect(this, SIGNAL(nodesAdded()), nodeWrapper, SLOT(updateText()));
	QObject::connect(this, SIGNAL(matchRunCompleted()), nodeWrapper, SLOT(updateText()));

	foreach(KPDGUINode *comparisonNode, nodes.values()) {
		if (node->getID() != comparisonNode->getID()) {
			if (comparisonNode->getType() == PAIR) {
				foreach(KPDGUIDonor * donor, node->getDonors()) {

					KPDGUICandidate * candidate = comparisonNode->getCandidate();

					KPDCrossmatchResult crossmatch = kpdguiCrossmatchFunctions->performCrossmatch(donor, candidate);

					if (!(crossmatch == FAILED_CROSSMATCH_BT || crossmatch == FAILED_CROSSMATCH_HLA)) {

						double fiveYearSurvival = kpdguiCrossmatchFunctions->calculateSurvival(donor, candidate, 1);
						double tenYearSurvival = kpdguiCrossmatchFunctions->calculateSurvival(donor, candidate, 0);

						KPDGUIMatch * match = new KPDGUIMatch(donor, candidate, crossmatch, fiveYearSurvival, tenYearSurvival);
						insertMatch(match);
					}
				}
			}
			if (node->getType() == PAIR) {
				foreach(KPDGUIDonor * donor, comparisonNode->getDonors()) {

					KPDGUICandidate * candidate = node->getCandidate();

					KPDCrossmatchResult crossmatch = kpdguiCrossmatchFunctions->performCrossmatch(donor, node->getCandidate());

					if (!(crossmatch == FAILED_CROSSMATCH_BT || crossmatch == FAILED_CROSSMATCH_HLA)) {

						double fiveYearSurvival = kpdguiCrossmatchFunctions->calculateSurvival(donor, candidate, 1);
						double tenYearSurvival = kpdguiCrossmatchFunctions->calculateSurvival(donor, candidate, 0);

						KPDGUIMatch * match = new KPDGUIMatch(donor, candidate, crossmatch, fiveYearSurvival, tenYearSurvival);
						insertMatch(match);
					}
				}
			}
		}
	}
	
}

void KPDGUI::insertMatch(KPDGUIMatch * match) {

	KPDGUIDonor * donor = match->getDonor();
	KPDGUICandidate * candidate = match->getCandidate();

	candidate->addMatchingDonor(match);
	donor->addMatchingCandidate(match);

	int donorNodeID = match->getDonor()->getID();
	int candidateNodeID = match->getCandidate()->getID();

	donorMatches[donorNodeID] << match;
	candidateMatches[candidateNodeID] << match;
	
	kpdguiScene->addItem(match);

	QObject::connect(this, SIGNAL(displaySettingsChanged(KPDGUIDisplaySettings *)), match, SLOT(updateVisibility(KPDGUIDisplaySettings *)));


	KPDGUIMatchWrapper * matchWrapper = new KPDGUIMatchWrapper(match);
	
	QObject::connect(kpdguiMatchList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), matchWrapper, SLOT(matchWrapperDoubleClickActions(QTreeWidgetItem*)));
	QObject::connect(this, SIGNAL(nodesAdded()), matchWrapper, SLOT(updateText()));
	QObject::connect(this, SIGNAL(matchRunCompleted()), matchWrapper, SLOT(updateText()));

	kpdguiMatchList->addTopLevelItem(matchWrapper);

	matchWrapperMap.insert(match, matchWrapper);


}

void KPDGUI::donorSelectionActions(int nodeID, int donorID, bool selected) {

	KPDGUINode * node = nodes[nodeID];

	if (node->getType() == PAIR) {
		node->getCandidate()->setSelected(selected);		
	}

	//nodeWrapperMap[node]->setSelected(selected);

	kpdguiScene->raiseZValue();

	emit displaySettingsChanged(kpdguiDisplaySettings);

}

void KPDGUI::candidateSelectionActions(int id, bool selected) {

	KPDGUINode * node = nodes[id];

	foreach(KPDGUIDonor * donor, node->getDonors()) {
		donor->setSelected(selected);
	}

	kpdguiScene->raiseZValue();

	//nodeWrapperMap[node]->setSelected(selected);

	emit displaySettingsChanged(kpdguiDisplaySettings);
}

/*void KPDGUI::nodeWrapperClickActions() {

	for(int i = 0; i < kpdguiNodeList->topLevelItemCount(); i++) {
		
		QTreeWidgetItem * item = kpdguiNodeList->topLevelItem(i);

		KPDGUINodeWrapper * wrapper = dynamic_cast<KPDGUINodeWrapper *>(item);
		if (wrapper) {
			
			bool selected = wrapper->isSelected();
			KPDGUINode * node = wrapper->getNode();

			if (node->getType() == PAIR) {
				if (selected) {
					ui->kpdGraphicsView->centerOn(QPointF(node->getCandidate()->x(), node->getCandidate()->y()));
				}
				node->getCandidate()->setSelected(selected);
			}
			else {
				if (selected) {
					ui->kpdGraphicsView->centerOn(QPointF(node->getFirstDonor()->x(), node->getFirstDonor()->y()));
				}
				node->getFirstDonor()->setSelected(selected);
			}
		}
	}


}*/

void KPDGUI::arrangementListClickActions(QTreeWidgetItem * item) {
	
	KPDGUIArrangementWrapper * wrapper = dynamic_cast<KPDGUIArrangementWrapper *>(item);
	if (wrapper) {		
		wrapper->getArrangement()->highlight();
	}

}

void KPDGUI::arrangementListDoubleClickActions(QTreeWidgetItem * item) {

	KPDGUIArrangementSet * arrangementSet = dynamic_cast<KPDGUIArrangementSet *>(item);
	if (arrangementSet) {
		arrangementSet->displayInformation();
	}
}

void KPDGUI::solutionListClickActions(QTreeWidgetItem * item) {

	KPDGUIArrangementWrapper * wrapper = dynamic_cast<KPDGUIArrangementWrapper *>(item);
	if (wrapper) {
		wrapper->getArrangement()->highlight();
	}

}

void KPDGUI::solutionListDoubleClickActions(QTreeWidgetItem * item) {
	
	KPDGUIArrangementSet * arrangementSet = dynamic_cast<KPDGUIArrangementSet *>(item);
	if (arrangementSet) {
		arrangementSet->displayInformation();
	}
}


