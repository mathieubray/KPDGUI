
#include "ui_KPDGUI.h"

#include "KPDGUI.h"

KPDGUI::KPDGUI(QWidget *parent) : QMainWindow(parent), ui(new Ui::KPDGUI)
{
    ui->setupUi(this);

	//Initialize parameters
	setCurrentFile("");
	previousSliderPosition = 0;

	baselineID = 1;
	matchRunID = 1;
	
	//Set up views
	kpdguiScene = new KPDGUIGraphicsScene();
	ui->kpdGraphicsView->setScene(kpdguiScene);
	connect(kpdguiScene, SIGNAL(updateVisibilitySignal()), this, SLOT(updateScene()));
	connect(kpdguiScene, SIGNAL(selectionClustered(int, int)), ui->kpdGraphicsView, SLOT(centerView(int, int)));
	//connect(kpdguiScene, SIGNAL(addNewDonorSignal(KPDGUICandidate*)), this, SLOT(addNewDonor(KPDGUICandidate*)));

	kpdguiCommandHistory = new KPDGUICommandHistory();
	kpdguiNodeList = new KPDGUIDashboardList(NODE);
	kpdguiDonorList = new KPDGUIDashboardList(DONOR);
	kpdguiCandidateList = new KPDGUIDashboardList(CANDIDATE);	
	kpdguiMatchList = new KPDGUIDashboardList(MATCH);
	
	kpdguiArrangementList = new QTreeWidget();
	kpdguiArrangementList->setHeaderHidden(true);
	kpdguiArrangementList->setContextMenuPolicy(Qt::CustomContextMenu);
	//connect(kpdguiArrangementList, SIGNAL(pressed()), this, SLOT(arrangementListSelectionActions()));
	//connect(kpdguiArrangementList, SIGNAL(itemSelectionChanged()), this, SLOT(arrangementListSelectionActions()));
	connect(kpdguiArrangementList, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this, SLOT(arrangementListClickActions(QTreeWidgetItem *)));
	connect(kpdguiArrangementList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(arrangementListDoubleClickActions(QTreeWidgetItem*)));
	connect(kpdguiArrangementList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(arrangementListRightClickActions(QPoint)));
	
	kpdguiSolutionList = new QTreeWidget();
	kpdguiSolutionList->setHeaderHidden(true);
	kpdguiSolutionList->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(kpdguiSolutionList, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this, SLOT(solutionListClickActions(QTreeWidgetItem *)));
	connect(kpdguiSolutionList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(solutionListDoubleClickActions(QTreeWidgetItem*)));
	connect(kpdguiSolutionList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(solutionListRightClickActions(QPoint)));

	ui->kpdListView->insertTab(1, kpdguiCommandHistory, "History");
	ui->kpdListView->insertTab(2, kpdguiNodeList, "Pairings/NDDs");
	ui->kpdListView->insertTab(3, kpdguiDonorList, "Donors");
	ui->kpdListView->insertTab(4, kpdguiCandidateList, "Candidates");
	ui->kpdListView->insertTab(5, kpdguiMatchList, "Matches");
	ui->kpdListView->insertTab(6, kpdguiArrangementList, "Possible Exchanges");
	ui->kpdListView->insertTab(7, kpdguiSolutionList, "Solutions");
	
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

	nMatches = 0;
	nNodes = 0;
	nDonors = 0;
	nCandidates = 0;
	
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

			QFile file(fileName);
			if (!file.open(QIODevice::ReadOnly)) {
				QMessageBox::warning(this, tr("KPD"),
					tr("Cannot read file %1:\n%2.")
					.arg(file.fileName())
					.arg(file.errorString()));

				updateStatus("Failed To Load " + fileName);
			}

			else {
				QDataStream in(&file);
				in.setVersion(QDataStream::Qt_5_3);

				qint32 number;
				in >> number;

				if (number != MagicNumber) {
					QMessageBox::warning(this, tr("KPD"),
						tr("Cannot read file %1:\n%2.")
						.arg(file.fileName())
						.arg(file.errorString()));

					updateStatus("Failed To Load " + fileName);
				}

				else {
					KPDGUI *mainWin = new KPDGUI;
					mainWin->loadFile(fileName);
					mainWin->show();
				}
			}
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

			KPDCrossmatchResult result = kpdguiCrossmatchFunctions->performCrossmatch(donor, candidate);
			donor->setCompatibilityWithPairedCandidate(result);
			
			// Store donors
			QVector<KPDGUIDonor *> associatedDonors;
			associatedDonors.push_back(donor);

			// Repeat for additional donors
			while (dialogDonor->getAdditionalDonor()){

				dialogDonor = new DialogDonor(true, this);
				dialogDonor->setWindowTitle("Add New Additional Donor");

				if (dialogDonor->exec()){
					KPDGUIDonor * additionalDonor = new KPDGUIDonor(dialogDonor);

					KPDCrossmatchResult result = kpdguiCrossmatchFunctions->performCrossmatch(additionalDonor, candidate);
					additionalDonor->setCompatibilityWithPairedCandidate(result);

					associatedDonors.push_back(additionalDonor);
				}
				else {
					break;
				}
			}

			
			/*QVector<KPDCrossmatchResult> crossmatchResults;

			foreach(KPDGUIDonor * donor, associatedDonors) {
				KPDCrossmatchResult result = kpdguiCrossmatchFunctions->performCrossmatch(donor, candidate);
				crossmatchResults << result;
			}*/

			// Create node
			KPDGUINode * newNode = new KPDGUINode(associatedDonors, candidate);

			candidate->setParentNode(newNode);
			foreach(KPDGUIDonor * donor, associatedDonors) {
				donor->setParentNode(newNode);
			}

			// Insert node
			insertNode(newNode);

			// Add to scene
			updateHueValues();
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
	DialogDonor * dialogNDD = new DialogDonor(false, this);

	if (dialogNDD->exec()) {

		// Create NDD
		KPDGUIDonor * nonDirectedDonor = new KPDGUIDonor(dialogNDD);

		// Create node
		KPDGUINode * newNode = new KPDGUINode(nonDirectedDonor);

		nonDirectedDonor->setParentNode(newNode);

		// Insert node
		insertNode(newNode);

		// Add to scene
		updateHueValues();
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

void KPDGUI::addNewDonor() {

	KPDGUICandidate * candidate = dynamic_cast<KPDGUICandidate *>(sender());

	if (candidate) {

		DialogDonor * dialogDonor = new DialogDonor(true, this);
		dialogDonor->additionalDonorButton->setVisible(false);
		dialogDonor->setWindowTitle("Add Additional Donor");

		KPDGUINode * parentNode = candidate->getParentNode();

		if (dialogDonor->exec()) {

			// Create New Donor
			KPDGUIDonor * additionalDonor = new KPDGUIDonor(dialogDonor);

			KPDCrossmatchResult result = kpdguiCrossmatchFunctions->performCrossmatch(additionalDonor, candidate);
			additionalDonor->setCompatibilityWithPairedCandidate(result);

			// Add to Node
			parentNode->addDonor(additionalDonor);


			/// Donor Connections
			QObject::connect(additionalDonor, SIGNAL(donorEdited()), this, SLOT(updateMatches()));

			QObject::connect(this, SIGNAL(updateDonorHueSignal(int, double, double)), additionalDonor, SLOT(updateHue(int, double, double)));

			KPDGUIDonorWrapper * donorWrapper = new KPDGUIDonorWrapper(additionalDonor);
			kpdguiDonorList->addTopLevelItem(donorWrapper);

			QObject::connect(this, SIGNAL(nodesAdded()), donorWrapper, SLOT(updateText()));
			QObject::connect(this, SIGNAL(matchRunCompleted()), donorWrapper, SLOT(updateText()));

			QObject::connect(kpdguiDonorList, SIGNAL(itemClicked(QTreeWidgetItem*, int)), donorWrapper, SLOT(donorWrapperClickActions(QTreeWidgetItem*)));
			QObject::connect(kpdguiDonorList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), donorWrapper, SLOT(donorWrapperDoubleClickActions(QTreeWidgetItem*)));

			QObject::connect(donorWrapper, SIGNAL(updateVisibilitySignal()), this, SLOT(updateScene()));


			/// Donor Matches

			foreach(KPDGUINode *comparisonNode, nodes.values()) {
				if (parentNode->getID() != comparisonNode->getID()) {
					if (comparisonNode->getType() == PAIR) {

						KPDGUICandidate * candidate = comparisonNode->getCandidate();

						KPDCrossmatchResult crossmatch = kpdguiCrossmatchFunctions->performCrossmatch(additionalDonor, candidate);

						if (!(crossmatch == FAILED_CROSSMATCH_BT || crossmatch == FAILED_CROSSMATCH_HLA)) {

							double fiveYearSurvival = kpdguiCrossmatchFunctions->calculateSurvival(additionalDonor, candidate, 1);
							double tenYearSurvival = kpdguiCrossmatchFunctions->calculateSurvival(additionalDonor, candidate, 0);
							bool difficultToMatch = kpdguiCrossmatchFunctions->determineDifficultMatch(additionalDonor, candidate);

							KPDGUIMatch * match = new KPDGUIMatch(additionalDonor, candidate, crossmatch, fiveYearSurvival, tenYearSurvival, difficultToMatch);
							insertMatch(match);
						}
					}
				}
			}

			nDonors++;			

			// Add to Scene
			updateHueValues();
			kpdguiScene->addItem(additionalDonor);			

			// Focus on the parent node
			ui->kpdGraphicsView->centerOn(parentNode->getNodePosition());

			// Select parent node
			parentNode->setSelected(true);

			updateStatus("Added New Donor " + additionalDonor->getName() + " to Candidate " + candidate->getName() + " (" + QString::number(parentNode->getID()) + ")");
			setWindowModified(true);

			emit nodesAdded();

		}
	}

}


void KPDGUI::loadNodes()
{
	ReadFileDialog readFileDialog(false, this);

	if (readFileDialog.exec()) {
		QApplication::setOverrideCursor(Qt::WaitCursor);
		QApplication::processEvents();

		// Get file and layout information
		QString fileName = readFileDialog.loadLineEdit->text();
		QString layout = readFileDialog.layoutComboBox->currentText();

		QVector<QVector<QVector<QString> > > nodeInfo = KPDFunctions::loadData(fileName, true);

		// Load pairs from file
		QMap<int, QVector<KPDGUIDonor *> > donorsToAdd;
		QMap<int, KPDGUICandidate *> candidatesToAdd;
		QVector<KPDGUIDonor *> nddsToAdd;

		int previousNodeID = -1;

		foreach(QVector<QVector<QString> > line, nodeInfo) {

			int currentNodeID = line.at(0).at(0).toInt();

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

			// NDD
			if (line.at(2).at(0).toInt() == 1) {
				nddsToAdd.push_back(newDonor);
			}
			// New Donor
			else {
				donorsToAdd[currentNodeID] << newDonor;
			}

			// New Candidate
			if (line.at(2).at(0).toInt() == 0 && currentNodeID != previousNodeID) {

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

				//newCandidate->setStatus(status);
				newCandidate->setStatus(true);

				candidatesToAdd[currentNodeID] = newCandidate;
			}

			previousNodeID = currentNodeID;
		}

		QVector<KPDGUINode *> nodesToAdd;

		foreach(KPDGUIDonor * ndd, nddsToAdd) {

			KPDGUINode * newNDDNode = new KPDGUINode(ndd);

			ndd->setParentNode(newNDDNode);

			nodesToAdd << newNDDNode;
		}


		foreach(int id, candidatesToAdd.keys()) {

			KPDGUINode * newNode;

			KPDGUICandidate * newCandidate = candidatesToAdd[id];

			QVector<KPDGUIDonor *> newDonors = donorsToAdd[id];

			//QVector<KPDCrossmatchResult> crossmatchResults;

			foreach(KPDGUIDonor * donor, newDonors) {

				KPDCrossmatchResult result = kpdguiCrossmatchFunctions->performCrossmatch(donor, newCandidate);
				donor->setCompatibilityWithPairedCandidate(result);
				//crossmatchResults << result;
			}

			newNode = new KPDGUINode(newDonors, newCandidate);

			foreach(KPDGUIDonor * donor, newDonors) {		
				donor->setParentNode(newNode);
			}

			newCandidate->setParentNode(newNode);

			nodesToAdd << newNode;
		}

		// Insert nodes
		foreach(KPDGUINode * node, nodesToAdd) {
			insertNode(node);
		}

		// Add to scene
		updateHueValues();
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

void KPDGUI::loadAPD()
{
	ReadFileDialog readFileDialog(true, this);

	if (readFileDialog.exec()) {
		QApplication::setOverrideCursor(Qt::WaitCursor);
		QApplication::processEvents();

		// Get file and layout information
		QString folderName = readFileDialog.loadLineEdit->text();
		QString layout = readFileDialog.layoutComboBox->currentText();


		// Store NDD IDs
		QString nddFileName = folderName + "/NDD_APD.csv";

		QSet<int> nonDirectedDonors;

		QFile nddFile(nddFileName);
		if (!nddFile.open(QIODevice::ReadOnly)) {
			qDebug() << "Cannot Open File For Reading: " << qPrintable(nddFile.errorString());
		}
		QTextStream nddFileStream(&nddFile);

		while (!nddFileStream.atEnd()) {
			
			nonDirectedDonors << nddFileStream.readLine().toInt();

		}

		/*foreach(int ndd, nonDirectedDonors) {
			qDebug() << "NDD: " + QString::number(ndd);
		}*/

		// Store Multiple Donor Candidates
		QString multipleDonorFileName = folderName + "/SamePat_APD.csv";

		QMap<int, int> multipleDonorPairs;
		QSet<int> multipleDonorIDs;

		QFile multipleDonorFile(multipleDonorFileName);
		if (!multipleDonorFile.open(QIODevice::ReadOnly)) {
			qDebug() << "Cannot Open File For Reading: " << qPrintable(multipleDonorFile.errorString());
		}
		QTextStream multipleDonorFileStream(&multipleDonorFile);

		while (!multipleDonorFileStream.atEnd()) {
			QString multipleDonors = multipleDonorFileStream.readLine();
			QStringList tokens = multipleDonors.split(',');
			
			int candidateID = tokens.at(0).toInt();
			int donorID = tokens.at(1).toInt();

			multipleDonorPairs[donorID] = candidateID;
			multipleDonorIDs.insert(donorID);
		}

		/*foreach(int id, multipleDonorPairs.keys()) {
			qDebug() << "MD PAIRS: " << QString::number(id) << ":" << QString::number(multipleDonorPairs[id]);
		}

		foreach(int id, multipleDonorIDs) {
			qDebug() << "MD IDS: " << QString::number(id);
		}*/

		// Collect Donors and Candidates
		QString donorCandidateFileName = folderName + "/Info_APD.csv";

		QVector<KPDGUIDonor *> fullDonors;
		QMap<int, QVector<KPDGUIDonor *> > donorMap;
		QMap<int, KPDGUICandidate *> candidateMap;
		QMap<int, KPDNodeType> nodeTypeMap;
		QVector<int> nodeIDs;

		QFile donorCandidateFile(donorCandidateFileName);
		if (!donorCandidateFile.open(QIODevice::ReadOnly)) {
			qDebug() << "Cannot Open File For Reading: " << qPrintable(donorCandidateFile.errorString());
		}
		QTextStream donorCandidateFileStream(&donorCandidateFile);

		//for (std::vector<std::vector<std::vector<std::string> > >::iterator infoIt = APDInfoData.begin(); infoIt != APDInfoData.end(); infoIt++) {

		int n = 0;

		while (!donorCandidateFileStream.atEnd()) {
			QString info = donorCandidateFileStream.readLine();
			QStringList tokens = info.split(',');

			int id = tokens.at(0).toInt();
			int pra = tokens.at(1).toInt();
			KPDBloodType candidateBT = KPDFunctions::stringToBloodType(tokens.at(2));
			KPDBloodType donorBT = KPDFunctions::stringToBloodType(tokens.at(3));
			QString candidateName = tokens.at(5);
			QString donorName = tokens.at(6);

			if (multipleDonorIDs.contains(id)) {

				int matchingID = multipleDonorPairs[id];

				KPDGUIDonor * newDonor = new KPDGUIDonor();
				newDonor->setName(donorName + " (" + QString::number(id) + ")");
				newDonor->setBT(donorBT);

				fullDonors << newDonor;

				if (donorMap.contains(matchingID)) {
					donorMap[matchingID].push_back(newDonor);
				}
				else {

					// This should never happen, but just in case...

					QVector<KPDGUIDonor *> donors;
					donors.push_back(newDonor);
					donorMap[matchingID] = donors;

					KPDGUICandidate * newCandidate = new KPDGUICandidate();
					newCandidate->setName(candidateName + " (" + QString::number(matchingID) + ")");
					newCandidate->setPRA(pra);
					newCandidate->setBT(candidateBT);

					candidateMap[matchingID] = newCandidate;

					nodeTypeMap[matchingID] = PAIR;

					nodeIDs.push_back(matchingID);
				}
			}

			else {
				nodeIDs.push_back(id);

				if (nonDirectedDonors.contains(id)) {

					KPDGUIDonor * newDonor = new KPDGUIDonor();
					newDonor->setName(donorName + " (" + QString::number(id) + ")");
					newDonor->setBT(donorBT);

					fullDonors << newDonor;

					QVector<KPDGUIDonor *> donors;
					donors.push_back(newDonor);
					donorMap[id] = donors;

					nodeTypeMap[id] = NDD;
				}
				else {

					KPDGUIDonor * newDonor = new KPDGUIDonor();
					newDonor->setName(donorName + " (" + QString::number(id) + ")");
					newDonor->setBT(donorBT);

					fullDonors << newDonor;

					QVector<KPDGUIDonor *> donors;
					donors.push_back(newDonor);
					donorMap[id] = donors;

					KPDGUICandidate * newCandidate = new KPDGUICandidate();
					newCandidate->setName(candidateName + " (" + QString::number(id) + ")");
					newCandidate->setPRA(pra);
					newCandidate->setBT(candidateBT);

					candidateMap[id] = newCandidate;

					nodeTypeMap[id] = PAIR;
				}
			}

			n++;
		}

		// Assemble Nodes

		int numberOfNDDs = 0;
		int numberOfIncompatiblePairings = 0;
		int numberOfIncompatibleDonors = 0;
		
		QVector<KPDGUINode *> nodesToAdd;

		foreach(int matchingID, nodeIDs){
			
			KPDGUINode * newNode;

			if (nodeTypeMap[matchingID] == NDD) {

				KPDGUIDonor * ndd = donorMap[matchingID].at(0);

				newNode = new KPDGUINode(ndd);

				ndd->setParentNode(newNode);
				
				numberOfNDDs++;
			}
			else {
				KPDGUICandidate * candidate = candidateMap[matchingID];
				QVector<KPDGUIDonor *> donors = donorMap[matchingID];

				foreach(KPDGUIDonor * donor, donors) {
					donor->setCompatibilityWithPairedCandidate(FAILED_CROSSMATCH_HLA);
				}

				newNode = new KPDGUINode(donors, candidate);

				foreach(KPDGUIDonor * donor, donors) {
					donor->setParentNode(newNode);
				}
				candidate->setParentNode(newNode);

				numberOfIncompatiblePairings++;
				numberOfIncompatibleDonors += newNode->getNumberOfDonors();
			}

			newNode->setID(baselineID);
			baselineID++;

			nodesToAdd << newNode;
		}

		foreach(KPDGUINode * node, nodesToAdd) {
			insertNode(node, true);
		}

		kpdguiScene->addNodes(nodesToAdd, layout);
		updateHueValues();

		// Prepare Matches
		QString incidenceFileName = folderName + "/Comp_APD.csv";

		QFile incidenceFile(incidenceFileName);
		if (!incidenceFile.open(QIODevice::ReadOnly)) {
			qDebug() << "Cannot Open File For Reading: " << qPrintable(incidenceFile.errorString());
		}
		QTextStream incidenceFileStream(&incidenceFile);

		QVector<QVector<bool> > incidenceMatrix(1 + n, QVector<bool>(1 + n, false));

		int i = 1;
		while (!incidenceFileStream.atEnd()) {
			
			QString incidenceRow = incidenceFileStream.readLine();

			//qDebug() << incidenceRow;

			QStringList tokens = incidenceRow.split(',');

			int j = 1;
			foreach(QString token, tokens) {
				if (token.toInt() == 1) {
					incidenceMatrix[i][j] = true;

					//qDebug() << "[" << QString::number(i) << "," << QString::number(j) << "] " << incidenceMatrix[i][j];
				}
				j++;
			}
			i++;
		}


		QString weightFileName = folderName + "/Weight_APD.csv";

		QFile weightFile(weightFileName);
		if (!weightFile.open(QIODevice::ReadOnly)) {
			qDebug() << "Cannot Open File For Reading: " << qPrintable(weightFile.errorString());
		}
		QTextStream weightFileStream(&weightFile);

		QVector<QVector<double> > weightMatrix(1 + n, QVector<double>(1 + n, 0.0));

		i = 1;
		while (!weightFileStream.atEnd()) {
			QString weightRow = weightFileStream.readLine();
			QStringList tokens = weightRow.split(',');

			int j = 1;
			foreach(QString token, tokens) {
				if (incidenceMatrix[i][j]) {
					weightMatrix[i][j] = token.toDouble();

					//qDebug() << "[" << QString::number(i) << "," << QString::number(j) << "] " << weightMatrix[i][j];
				}
				j++;
			}
			i++;
		}
		
		for (int i = 1; i <= n; i++) {

			if (nodeIDs.contains(i) && !nonDirectedDonors.contains(i)){

				for (int j = 1; j <= n; j++) {

					if (incidenceMatrix[i][j]) {

						KPDGUIDonor * donor = fullDonors[j - 1];
						KPDGUICandidate * candidate = candidateMap[i];

						KPDCrossmatchResult result = kpdguiCrossmatchFunctions->performCrossmatch(donor, candidate);
						double fiveYearSurvival = kpdguiCrossmatchFunctions->calculateSurvival(donor, candidate, true);
						double tenYearSurvival = kpdguiCrossmatchFunctions->calculateSurvival(donor, candidate, false);
						bool difficultToMatch = kpdguiCrossmatchFunctions->determineDifficultMatch(donor, candidate);

						KPDGUIMatch * match = new KPDGUIMatch(donor, candidate, result, fiveYearSurvival, tenYearSurvival, difficultToMatch);

						double score = weightMatrix[i][j];
						if (score == 0) {
							score = 0.00001;
						}

						match->setAssignedUtility(score);

						insertMatch(match, true);				

					}
				}
				
			}
		}

		//updateHueValues();

		// Alert
		emit nodesAdded();
		emit displaySettingsChanged(kpdguiDisplaySettings);

		QApplication::restoreOverrideCursor();
		QApplication::processEvents();

		updateStatus("Loaded APD Pool From " + folderName);
		
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
			tr("The pool has been modified since the last time parameters were set. \n\nSet parameters now?"),
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

		// Set up progress bar
		QProgressDialog * progressBar = new QProgressDialog("Setting Up Match Run...", QString(), 0, 100, this);
		progressBar->setFixedWidth(500);
		progressBar->setWindowModality(Qt::WindowModal);
		progressBar->setWindowTitle("Match Run Progress");
		progressBar->setAutoClose(false);
		progressBar->show();
		QApplication::setOverrideCursor(Qt::WaitCursor);
		QApplication::processEvents();

		// Perform match run
		KPDGUIMatchRun * matchRun = new KPDGUIMatchRun(getNodes(), kpdguiParameters, progressBar);

		// Set time stamp and collect match run text
		QString timestamp = QDate::currentDate().toString() + " " + QTime::currentTime().toString();
		QString matchRunNodeList = matchRun->getNodeListString();
		QString matchRunMatchList = matchRun->getMatchListString();
		
		// Collect arrangement information from match run
		QMap<int, KPDGUIArrangement *> matchRunArrangements;
		QVector<KPDGUIArrangementSet *> matchRunSolutions;

		QVector<QVector<KPDGUINode *> > collectedArrangementNodes = matchRun->getMatchRunArrangementNodes();
		QVector<QVector<KPDGUIMatch *> > collectedArrangementMatches = matchRun->getMatchRunArrangementMatches();
		QVector<double> collectedArrangementValues = matchRun->getAssignedValueOfMatchRunArrangements();

		int numberOfCollectedArrangements = collectedArrangementNodes.size();

		QVector<QVector<int> > selectedSolutions = matchRun->getMatchRunSelectedSolutions();
		QVector<double> selectedSolutionValues = matchRun->getAssignedValueOfMatchRunSolutions();

		int numberOfSelectedSolutions = selectedSolutions.size();

		bool collectAllMatchRunArrangements = kpdguiParameters->getCollectArrangements() && collectedArrangementNodes.size() <= kpdguiParameters->getCollectArrangementsCutoff();
		
		QVector<bool> arrangementsThatAppearInSolutions(numberOfCollectedArrangements, false);

		foreach(QVector<int> solution, selectedSolutions) {
			foreach(int arrangementID, solution) {
				arrangementsThatAppearInSolutions[arrangementID] = true;
			}
		}

		// Prepare match run arrangements		

		progressBar->setLabelText("Preparing Match Run Exchanges...");
		progressBar->setRange(0, 2 * numberOfCollectedArrangements);
		progressBar->setValue(0);

		// Go through arrangements from match run
		int i = 1;
		foreach(QVector<KPDGUINode *> arrangement, collectedArrangementNodes) {

			// Get arrangement value
			double currentArrangementValue = collectedArrangementValues[i - 1];

			if (collectAllMatchRunArrangements || arrangementsThatAppearInSolutions[i - 1]) {
				// Create new arrangement
				KPDGUIArrangement * newArrangement = new KPDGUIArrangement(i, currentArrangementValue);
				QObject::connect(newArrangement, SIGNAL(arrangementClustered(int, int)), ui->kpdGraphicsView, SLOT(centerView(int, int)));

				// Add nodes to arrangement
				foreach(KPDGUINode * node, arrangement) {
					newArrangement->addNode(node);
				}

				// Add relevant matches to arrangement
				foreach(KPDGUIMatch * match, collectedArrangementMatches[i - 1]) {
					newArrangement->addMatch(match);
				}

				// Add to collected arrangements
				matchRunArrangements.insert(i-1,newArrangement);
			}

			progressBar->setValue(i);
			QApplication::processEvents();

			i++;
		}

		// Create new arrangement set
		KPDGUIArrangementSet * matchRunArrangementSet = new KPDGUIArrangementSet(kpdguiParameters, timestamp, matchRunNodeList, matchRunMatchList, false, collectAllMatchRunArrangements, numberOfCollectedArrangements);
		QObject::connect(matchRunArrangementSet, SIGNAL(arrangementClustered(int, int)), ui->kpdGraphicsView, SLOT(centerView(int, int)));

		// Add official arrangements to arrangement set
		foreach(KPDGUIArrangement * arrangement, matchRunArrangements) {

			matchRunArrangementSet->addArrangement(arrangement);

			progressBar->setValue(i);
			QApplication::processEvents();

			i++;
		}

		// Increase popularity
		matchRunArrangementSet->increasePopularity();

		// Add to dashboard
		kpdguiArrangementList->insertTopLevelItem(0, matchRunArrangementSet);
		matchRunArrangementSet->setExpanded(true);

		// Print to dashboard
		updateStatus("Match Run Arrangements:");
		updateStatus(matchRunArrangementSet->toCondensedString());

		storedMatchRunResults.insert(matchRunID, matchRunArrangementSet);
		

		// Go through solutions			
		progressBar->setLabelText("Preparing Match Run Solutions...");
		progressBar->setRange(0, numberOfSelectedSolutions);
		progressBar->setValue(0);

		int p = 1;
		for (int i = numberOfSelectedSolutions - 1; i >= 0; i--) {

			QVector<int> solution = selectedSolutions[i];

			// Need to copy the parameters
			KPDGUIParameters * parameters = new KPDGUIParameters();
			parameters->copyParameters(kpdguiParameters);

			// Create new solution set
			KPDGUIArrangementSet * newSolution = new KPDGUIArrangementSet(parameters, timestamp, matchRunNodeList, matchRunMatchList, true, true, solution.size(), i + 1);
			QObject::connect(newSolution, SIGNAL(arrangementClustered(int, int)), ui->kpdGraphicsView, SLOT(centerView(int, int)));

			// Add arrangements to solution set
			foreach(int arrangementID, solution) {
				newSolution->addArrangement(matchRunArrangements[arrangementID]);
			}

			// Increase popularity
			newSolution->increasePopularity();

			// Add to dashboard
			kpdguiSolutionList->insertTopLevelItem(0, newSolution);
			newSolution->setExpanded(true);

			// Print to dashboard
			matchRunSolutions << newSolution;

			// Print to Dashboard
			updateStatus(newSolution->toCondensedString());

			progressBar->setValue(p);
			QApplication::processEvents();

			p++;
		}		

		storedMatchRunSolutions.insert(matchRunID, matchRunSolutions);
		matchRunID++;

		kpdguiParameters->setParametersHaveBeenUpdatedFlag(false);

		emit matchRunCompleted();

		// Close Progress Bar
		progressBar->close();
		delete progressBar;
		QApplication::restoreOverrideCursor();
		QApplication::processEvents();

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

			kpdguiScene->clearSelection();

			qDebug() << "A";

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

void KPDGUI::filterMatchesSuccessful(bool show) {
	kpdguiDisplaySettings->setFilterSuccessfulMatches(show);
	emit displaySettingsChanged(kpdguiDisplaySettings);
}

void KPDGUI::filterMatchesOtoNonO(bool show) {
	kpdguiDisplaySettings->setFilterOtoNonOMatches(show);
	emit displaySettingsChanged(kpdguiDisplaySettings);
}

void KPDGUI::filterMatchesFailedAdditionalHLA(bool show) {
	kpdguiDisplaySettings->setFilterFailedMatchesAdditionalHLA(show);
	emit displaySettingsChanged(kpdguiDisplaySettings);
}

void KPDGUI::filterMatchesFailedCrossmatch(bool show) {
	kpdguiDisplaySettings->setFilterFailedMatchesCrossmatch(show);
	emit displaySettingsChanged(kpdguiDisplaySettings);
}

void KPDGUI::runSurvivalCalculator(KPDGUIMatch * match) {

	DialogSurvivalCalculator * dialog = new DialogSurvivalCalculator(match, kpdguiDonorList, kpdguiCandidateList, kpdguiCrossmatchFunctions, this);

	if (dialog->exec()) {

		kpdguiCommandHistory->appendCommand("Ran Survival Calculator");

	}

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
		"<p>By Mathieu Bray"
		"<p>2018"));
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
	file.open(QIODevice::ReadOnly);
	QDataStream in(&file);
	in.setVersion(QDataStream::Qt_5_3);

	qint32 number;
	in >> number;
	//qDebug() << "in >> number: " << QString::number(number);
	
	qint32 baseline;
	in >> baseline;
	baselineID = baseline;
	//qDebug() << "in >> baseline: " << QString::number(baseline);

	qint32 numberOfNodes;
	in >> numberOfNodes;
	//nNodes = numberOfNodes;
	//qDebug() << "in >> numberOfNodes: " << QString::number(numberOfNodes);

	for (int i = 0; i < numberOfNodes; i++) {

		qint32 x;
		qint32 y;

		in >> x >> y;
		//qDebug() << "in >> x >> y: " << QString::number(x) << QString::number(y);

		int id;
		int type;

		in >> id >> type;
		//qDebug() << "in >> id >> type: " << QString::number(id) << QString::number(type);

		KPDNodeType myType = KPDFunctions::intToNodeType(type);

		QVector<KPDGUIDonor * > donors;
		int numberOfDonors;

		in >> numberOfDonors;
		//qDebug() << "in >> numberOfDonors: " << QString::number(numberOfDonors);

		KPDGUINode * newNode;

		for (int i = 1; i <= numberOfDonors; i++) {

			KPDGUIDonor * d = new KPDGUIDonor();

			//qDebug() << "in >> *d";
			in >> *d;

			donors.push_back(d);
		}
		
		if (myType == PAIR) {
			
			KPDGUICandidate * c = new KPDGUICandidate();

			//qDebug() << "in >> *c:";
			in >> *c;

			newNode = new KPDGUINode(donors, c);
			newNode->setID(id);

			c->setParentNode(newNode);

			foreach(KPDGUIDonor * donor, donors) {
				donor->setParentNode(newNode);
			}

			insertNode(newNode, true);
		}

		else {

			newNode = new KPDGUINode(donors.first());
			newNode->setID(id);

			donors.first()->setParentNode(newNode);

			insertNode(newNode, true);

		}


		kpdguiScene->addNode(newNode);
		newNode->setNodePosition(QPointF(x, y));
	}

	updateHueValues();

	qint32 numberOfMatches;
	in >> numberOfMatches;
	//nMatches = numberOfMatches;

	for (int i = 0; i < numberOfMatches; i++) {

		int donorNodeID;
		int donorNumber;
		int candidateNodeID;

		in >> donorNodeID >> donorNumber >> candidateNodeID;

		KPDGUIMatch * match = new KPDGUIMatch();

		KPDGUINode * donorNode = nodes[donorNodeID];
		KPDGUIDonor * donor = donorNode->getDonor(donorNumber-1);
		KPDGUINode * candidateNode = nodes[candidateNodeID];
		KPDGUICandidate * candidate = candidateNode->getCandidate();

		in >> *match;

		match->setDonorAndCandidate(donor, candidate);

		insertMatch(match, true);
	}


	updateHueValues();

	qint32 numberOfMatchRuns;
	in >> numberOfMatchRuns;

	for (int i = 0; i < numberOfMatchRuns; i++) {

		qint32 matchRunID;

		in >> matchRunID;

		KPDGUIArrangementSet * matchRunResult = new KPDGUIArrangementSet();
		in >> *matchRunResult;
		QObject::connect(matchRunResult, SIGNAL(arrangementClustered(int, int)), ui->kpdGraphicsView, SLOT(centerView(int, int)));


		qint32 numberOfArrangements;
		in >> numberOfArrangements;

		for (int j = 0; j < numberOfArrangements; j++) {

			qint32 id;
			qreal util;
			qint32 numberOfNodes;

			in >> id >> util >> numberOfNodes;

			KPDGUIArrangement * newArrangement = new KPDGUIArrangement(id, util);
			QObject::connect(newArrangement, SIGNAL(arrangementClustered(int, int)), ui->kpdGraphicsView, SLOT(centerView(int, int)));


			for (int k = 0; k < numberOfNodes; k++) {

				qint32 nodeID;
				in >> nodeID;

				newArrangement->addNode(nodes[nodeID]);
			}

			qint32 numberOfMatches;
			in >> numberOfMatches;

			for (int k = 0; k < numberOfMatches; k++) {

				qint32 donorID;
				qint32 donorNumber;
				qint32 candidateID;
				in >> donorID >> donorNumber >> candidateID;

				KPDGUIDonor * donor = nodes[donorID]->getDonor(donorNumber - 1);
				
				foreach(KPDGUIMatch * match, donor->getMatches()) {
					if (match->getCandidate()->getID() == candidateID) {
						newArrangement->addMatch(match);
						break;
					}
				}
			}

			matchRunResult->addArrangement(newArrangement);
		}

		matchRunResult->increasePopularity();

		kpdguiArrangementList->insertTopLevelItem(0, matchRunResult);
		matchRunResult->setExpanded(true);

		storedMatchRunResults.insert(matchRunID, matchRunResult);
	}

	for (int i = 0; i < numberOfMatchRuns; i++) {

		qint32 matchRunID;
		in >> matchRunID;

		KPDGUIArrangementSet * arrangementSet = storedMatchRunResults[matchRunID];

		qint32 numberOfSolutions;
		in >> numberOfSolutions;

		QVector<KPDGUIArrangementSet *> matchRunSolutions;

		for (int j = 0; j < numberOfSolutions; j++) {

			KPDGUIArrangementSet * matchRunSolution = new KPDGUIArrangementSet();
			in >> *matchRunSolution;
			QObject::connect(matchRunSolution, SIGNAL(arrangementClustered(int, int)), ui->kpdGraphicsView, SLOT(centerView(int, int)));


			qint32 numberOfArrangements;
			in >> numberOfArrangements;

			for (int k = 0; k < numberOfArrangements; k++) {
				qint32 arrangementID;
				in >> arrangementID;

				foreach(KPDGUIArrangement * arrangement, arrangementSet->getArrangements()) {
					if (arrangementID == arrangement->getID()) {
						matchRunSolution->addArrangement(arrangement);
						break;
					}
				}
			}

			matchRunSolution->increasePopularity();

			kpdguiSolutionList->insertTopLevelItem(0, matchRunSolution);
			matchRunSolution->setExpanded(true);

			matchRunSolutions << matchRunSolution;
		}

		storedMatchRunSolutions.insert(matchRunID, matchRunSolutions);
	}


	KPDGUIDisplaySettings * displaySettings = new KPDGUIDisplaySettings();
	//qDebug() << "in >> *displaySettings:";
	in >> *displaySettings;
	kpdguiDisplaySettings->changeDisplaySettings(displaySettings);

	KPDMatchDisplayMode matchDisplayMode = displaySettings->getMatchDisplayMode();

	if (matchDisplayMode == WITHIN_SELECTION) {
		ui->actionDisplayCompatibilitiesWithinSelection->setChecked(true);
	}
	if (matchDisplayMode == SELECTED_COMPATIBILITIES) {
		ui->actionDisplaySelectedCompatibilities->setChecked(true);
	}
	if (matchDisplayMode == ALL_COMPATIBILITIES) {
		ui->actionDisplayAllCompatibilities->setChecked(true);
	}
	if (matchDisplayMode == NO_COMPATIBILITIES) {
		ui->actionDisplayNoCompatibilities->setChecked(true);
	}

	ui->actionFilter_Successful_Matches->setChecked(displaySettings->getFilterSuccessfulMatches());
	ui->actionFilter_O_Donor_to_Non_O_Candidate_Matches->setChecked(displaySettings->getFilterOtoNonOMatches());
	ui->actionFilter_Failed_Matches_on_Addtional_HLA->setChecked(displaySettings->getFilterFailedMatchesAdditionalHLA());
	ui->actionFilter_Failed_Matches_on_Crossmatch->setChecked(displaySettings->getFilterFailedMatchesCrossmatch());

	qint32 zoomVal;
	in >> zoomVal;
	zoomSlider->setValue(zoomVal);
	//qDebug() << "in >> zoomVal: " << QString::number(zoomVal);

	bool mouseTool;
	in >> mouseTool;
	if (mouseTool) {
		changeToMouseMode();
	}
	else {
		changeToHandMode();
	}
	//qDebug() << "in >> mouseTool: " << mouseTool;
	
	emit nodesAdded();
	emit displaySettingsChanged(kpdguiDisplaySettings);

	setCurrentFile(fileName);
	updateStatus(QFileInfo(fileName).fileName() + " Loaded");
	
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
	//qDebug() << "out << MagicNumber: " << QString::number(MagicNumber);

	out << qint32(baselineID);
	//qDebug() << "out << baselineID: " << QString::number(baselineID);
	
	out << qint32(nNodes);
	//qDebug() << "out << nNodes: " << QString::number(nNodes);

	foreach (KPDGUINode * node, nodes.values()) {
		int x = node->getNodePosition().x();
		int y = node->getNodePosition().y();

		out << qint32(x) << qint32(y);
		//qDebug() << "out << x << y: " << QString::number(x) << " " << QString::number(y);

		out << qint32(node->getID());
		out << qint32(KPDFunctions::nodeTypeToInt(node->getType()));

		//qDebug() << "out << node->getID(): " << QString::number(node->getID());
		//qDebug() << "out << node->getType(): " << QString::number(KPDFunctions::nodeTypeToInt(node->getType()));

		out << qint32(node->getNumberOfDonors());
		//qDebug() << "out << node->getNumberOfDonors(): " << QString::number(node->getNumberOfDonors());

		foreach(KPDGUIDonor * donor, node->getDonors()) {
			//qDebug() << "out << *donor";
			out << *donor;
		}

		if (node->getType() == PAIR) {
			//qDebug() << "out << *(node->getCandidate())";
			out << *(node->getCandidate());
		}
	}

	out << qint32(nMatches);

	foreach(QVector<KPDGUIMatch *> matches, donorMatches.values()) {
		foreach(KPDGUIMatch * match, matches) {

			int donorNodeID = match->getDonor()->getID();
			int donorNodeNumber = match->getDonor()->getDonorNumber();
			int candidateID = match->getCandidate()->getID();

			out << donorNodeID;
			out << donorNodeNumber;
			out << candidateID;

			out << *match;
		}
	}

	int numberOfMatchRuns = storedMatchRunResults.size();
	out << qint32(numberOfMatchRuns);

	foreach(int i, storedMatchRunResults.keys()) {

		out << qint32(i);

		KPDGUIArrangementSet * matchRunResult = storedMatchRunResults[i];
		out << *matchRunResult;
		
		out << qint32(matchRunResult->getNumberOfArrangements());

		foreach(KPDGUIArrangement * arrangement, matchRunResult->getArrangements()){

			out << arrangement->getID();
			out << qreal(arrangement->getUtility());
			out << qint32(arrangement->getNumberOfNodes());

			foreach(KPDGUINode * node, arrangement->getNodes()) {
				out << qint32(node->getID());
			}

			out << qint32(arrangement->getNumberOfMatches());

			foreach(KPDGUIMatch * match, arrangement->getMatches()) {
				out << qint32(match->getDonor()->getID());
				out << qint32(match->getDonor()->getDonorNumber());
				out << qint32(match->getCandidate()->getID());
			}			
		}
	}

	foreach(int i, storedMatchRunSolutions.keys()) {

		out << qint32(i);

		QVector<KPDGUIArrangementSet *> matchRunSolutions = storedMatchRunSolutions[i];

		out << qint32(matchRunSolutions.size());

		foreach(KPDGUIArrangementSet * matchRunSolution, matchRunSolutions) {

			out << *matchRunSolution;

			out << qint32(matchRunSolution->getNumberOfArrangements());

			foreach(KPDGUIArrangement * arrangement, matchRunSolution->getArrangements()) {
				out << qint32(arrangement->getID());
			}
		}
	}

	KPDGUIDisplaySettings const& displaySettings = *(kpdguiDisplaySettings);
	//qDebug() << "out << displaySettings: ";
	out << displaySettings;

	int zoom = zoomSlider->value();
	out << qint32(zoom);
	//qDebug() << "out << zoom: " << QString::number(zoom);

	bool mouseTool = ui->actionMouseTool->isChecked();
	out << mouseTool;
	//qDebug() << "out << mouseTool: " << mouseTool;
			
	setCurrentFile(fileName);
	updateStatus(QFileInfo(fileName).fileName() + " Saved");

	return true;
}

void KPDGUI::setCurrentFile(const QString &fileName)
{
	currentFile = fileName;
	setWindowModified(false);

	QString shownName = tr("Untitled");
	if (!currentFile.isEmpty()) {
		shownName = QFileInfo(currentFile).baseName();
	}

	this->setWindowTitle(tr("%1[*] - %2").arg(shownName)
		.arg(tr("KPDGUI")));
}

void KPDGUI::updateHueValues() {

	double avgDonorMatches = ((double)nMatches) / nDonors;
	double avgCandidateMatches = ((double)nMatches) / nCandidates;

	double sumSqDonor = 0.0;
	double sumSqCandidate = 0.0;


	foreach(int donorID, donorMatches.keys()) {
		sumSqDonor += pow(donorMatches[donorID].size() - avgDonorMatches, 2);
	}

	foreach(int candidateID, candidateMatches.keys()) {
		sumSqCandidate += pow(candidateMatches[candidateID].size() - avgCandidateMatches, 2);
	}

	double stdDevDonorMatches = sumSqDonor / nDonors;
	double stdDevCandidateMatches = sumSqCandidate / nCandidates;

	emit updateDonorHueSignal(nDonors, avgDonorMatches, stdDevDonorMatches);
	emit updateCandidateHueSignal(nCandidates, avgCandidateMatches, stdDevCandidateMatches);	
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

void KPDGUI::insertNode(KPDGUINode * node, bool loadedFromKPDFile) {

	if (!loadedFromKPDFile) {
		node->setID(baselineID);
		baselineID++;
	}

	nodes.insert(node->getID(), node);
	nNodes++;
	nDonors += node->getNumberOfDonors();

	foreach(KPDGUIDonor * donor, node->getDonors()) {
		//QObject::connect(donor, SIGNAL(donorSelectionChanged()), this, SLOT(selectionActions()));

		QObject::connect(donor, SIGNAL(donorEdited()), this, SLOT(updateMatches()));

		QObject::connect(this, SIGNAL(updateDonorHueSignal(int, double, double)), donor, SLOT(updateHue(int, double, double)));

		KPDGUIDonorWrapper * donorWrapper = new KPDGUIDonorWrapper(donor);
		kpdguiDonorList->addTopLevelItem(donorWrapper);


		QObject::connect(this, SIGNAL(nodesAdded()), donorWrapper, SLOT(updateText()));
		QObject::connect(this, SIGNAL(matchRunCompleted()), donorWrapper, SLOT(updateText()));


		QObject::connect(kpdguiDonorList, SIGNAL(itemClicked(QTreeWidgetItem*, int)), donorWrapper, SLOT(donorWrapperClickActions(QTreeWidgetItem*)));
		QObject::connect(kpdguiDonorList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), donorWrapper, SLOT(donorWrapperDoubleClickActions(QTreeWidgetItem*)));

		QObject::connect(donorWrapper, SIGNAL(updateVisibilitySignal()), this, SLOT(updateScene()));
	}	
	if (node->getType() == PAIR) {

		nCandidates++;

		//QObject::connect(node->getCandidate(), SIGNAL(candidateSelectionChanged()), this, SLOT(selectionActions()));

		QObject::connect(node->getCandidate(), SIGNAL(candidateEdited()), this, SLOT(updateMatches()));
		QObject::connect(node->getCandidate(), SIGNAL(addAdditionalDonorSignal()), this, SLOT(addNewDonor()));

		QObject::connect(this, SIGNAL(updateCandidateHueSignal(int, double, double)), node->getCandidate(), SLOT(updateHue(int, double, double)));

		KPDGUICandidateWrapper * candidateWrapper = new KPDGUICandidateWrapper(node->getCandidate());
		kpdguiCandidateList->addTopLevelItem(candidateWrapper);

		QObject::connect(this, SIGNAL(nodesAdded()), candidateWrapper, SLOT(updateText()));
		QObject::connect(this, SIGNAL(matchRunCompleted()), candidateWrapper, SLOT(updateText()));
		

		QObject::connect(kpdguiCandidateList, SIGNAL(itemClicked(QTreeWidgetItem *, int)), candidateWrapper, SLOT(candidateWrapperClickActions(QTreeWidgetItem*)));
		QObject::connect(kpdguiCandidateList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), candidateWrapper, SLOT(candidateWrapperDoubleClickActions(QTreeWidgetItem*)));

		QObject::connect(candidateWrapper, SIGNAL(updateVisibilitySignal()), this, SLOT(updateScene()));
	}	

	QObject::connect(this, SIGNAL(displaySettingsChanged(KPDGUIDisplaySettings *)), node, SLOT(updateVisibility(KPDGUIDisplaySettings *)));


	KPDGUINodeWrapper * nodeWrapper = new KPDGUINodeWrapper(node);
	kpdguiNodeList->addTopLevelItem(nodeWrapper);

	QObject::connect(kpdguiNodeList, SIGNAL(itemClicked(QTreeWidgetItem*, int)), nodeWrapper, SLOT(nodeWrapperClickActions(QTreeWidgetItem*)));
	QObject::connect(kpdguiNodeList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), nodeWrapper, SLOT(nodeWrapperDoubleClickActions(QTreeWidgetItem*)));

	QObject::connect(this, SIGNAL(nodesAdded()), nodeWrapper, SLOT(updateText()));
	QObject::connect(this, SIGNAL(matchRunCompleted()), nodeWrapper, SLOT(updateText()));

	QObject::connect(nodeWrapper, SIGNAL(updateVisibilitySignal()), this, SLOT(updateScene()));

	if (!loadedFromKPDFile) {

		foreach(KPDGUINode *comparisonNode, nodes.values()) {
			if (node->getID() != comparisonNode->getID()) {
				if (comparisonNode->getType() == PAIR) {
					foreach(KPDGUIDonor * donor, node->getDonors()) {

						KPDGUICandidate * candidate = comparisonNode->getCandidate();

						KPDCrossmatchResult crossmatch = kpdguiCrossmatchFunctions->performCrossmatch(donor, candidate);

						if (!(crossmatch == FAILED_CROSSMATCH_BT || crossmatch == FAILED_CROSSMATCH_HLA)) {

							double fiveYearSurvival = kpdguiCrossmatchFunctions->calculateSurvival(donor, candidate, 1);
							double tenYearSurvival = kpdguiCrossmatchFunctions->calculateSurvival(donor, candidate, 0);
							bool difficultToMatch = kpdguiCrossmatchFunctions->determineDifficultMatch(donor, candidate);

							KPDGUIMatch * match = new KPDGUIMatch(donor, candidate, crossmatch, fiveYearSurvival, tenYearSurvival, difficultToMatch);
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
							bool difficultToMatch = kpdguiCrossmatchFunctions->determineDifficultMatch(donor, candidate);

							KPDGUIMatch * match = new KPDGUIMatch(donor, candidate, crossmatch, fiveYearSurvival, tenYearSurvival, difficultToMatch);
							insertMatch(match);
						}
					}
				}
			}
		}

	}	
}

void KPDGUI::insertMatch(KPDGUIMatch * match, bool loadedFromKPDFile) {

	nMatches++;

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
	QObject::connect(match, SIGNAL(showAdditionalMatchInformation(KPDGUIMatch *)), this, SLOT(runSurvivalCalculator(KPDGUIMatch*)));

	KPDGUIMatchWrapper * matchWrapper = new KPDGUIMatchWrapper(match);
	
	QObject::connect(kpdguiMatchList, SIGNAL(itemClicked(QTreeWidgetItem*, int)), matchWrapper, SLOT(matchWrapperClickActions(QTreeWidgetItem*)));
	QObject::connect(kpdguiMatchList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), matchWrapper, SLOT(matchWrapperDoubleClickActions(QTreeWidgetItem*)));

	QObject::connect(this, SIGNAL(nodesAdded()), matchWrapper, SLOT(updateText()));
	QObject::connect(this, SIGNAL(matchRunCompleted()), matchWrapper, SLOT(updateText()));
	
	QObject::connect(matchWrapper, SIGNAL(updateVisibilitySignal()), this, SLOT(updateScene()));

	kpdguiMatchList->addTopLevelItem(matchWrapper);
}

void KPDGUI::updateScene() {

	kpdguiScene->raiseZValue();

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

/*void KPDGUI::arrangementListSelectionActions() {

	if (kpdguiArrangementList->selectedItems().size() == 0) {
		qDebug() << "NONE!";
	}

	foreach(QTreeWidgetItem * item, kpdguiArrangementList->selectedItems()) {

		KPDGUIArrangementWrapper * wrapper = dynamic_cast<KPDGUIArrangementWrapper *>(item);
		if (wrapper) {
			qDebug() << "Arrangement";
			//wrapper->getArrangement()->highlight();
		}
		else {
			KPDGUIArrangementSet * set = dynamic_cast<KPDGUIArrangementSet *>(item);
			if (set) {
				qDebug() << "Arrangement Set";
			}
		}
	}

}*/

void KPDGUI::arrangementListClickActions(QTreeWidgetItem * item) {

	kpdguiScene->clearSelection();
	
	updateScene();
	
	KPDGUIArrangementWrapper * wrapper = dynamic_cast<KPDGUIArrangementWrapper *>(item);
	if (wrapper) {	
		wrapper->getArrangement()->highlight();
	}
	else {
		KPDGUIArrangementSet * set = dynamic_cast<KPDGUIArrangementSet *>(item);
		if (set) {
			set->highlight();
		}
	}

}

void KPDGUI::arrangementListDoubleClickActions(QTreeWidgetItem * item) {

	KPDGUIArrangementSet * arrangementSet = dynamic_cast<KPDGUIArrangementSet *>(item);
	if (arrangementSet) {
		arrangementSet->displayInformation();
	}
}

void KPDGUI::arrangementListRightClickActions(QPoint pos) {
	
	QTreeWidgetItem * item = kpdguiArrangementList->itemAt(pos);

	QMenu *menu = new QMenu(this);
	QAction * clusterAction = new QAction("Cluster Arrangement", this);
	QAction * displayInformationAction = new QAction("View Information", this);

	KPDGUIArrangementWrapper * wrapper = dynamic_cast<KPDGUIArrangementWrapper *>(item);
	if (wrapper) {
		
		connect(clusterAction, SIGNAL(triggered()), wrapper->getArrangement(), SLOT(cluster()));
		
		menu->addAction(clusterAction);
	}
	else {
		KPDGUIArrangementSet * arrangementSet = dynamic_cast<KPDGUIArrangementSet *>(item);
		if (arrangementSet) {
			connect(displayInformationAction, SIGNAL(triggered()), arrangementSet, SLOT(displayInformation()));

			menu->addAction(displayInformationAction);
		}
	}

	if (menu->actions().size() > 0) {
		menu->popup(kpdguiArrangementList->viewport()->mapToGlobal(pos));
	}
}

void KPDGUI::solutionListClickActions(QTreeWidgetItem * item) {
	
	kpdguiScene->clearSelection();

	updateScene();

	KPDGUIArrangementWrapper * wrapper = dynamic_cast<KPDGUIArrangementWrapper *>(item);
	if (wrapper) {
		wrapper->getArrangement()->highlight();
	}
	else {
		KPDGUIArrangementSet * set = dynamic_cast<KPDGUIArrangementSet *>(item);
		if (set) {
			set->highlight();
		}
	}

}

void KPDGUI::solutionListDoubleClickActions(QTreeWidgetItem * item) {
	
	KPDGUIArrangementSet * arrangementSet = dynamic_cast<KPDGUIArrangementSet *>(item);
	if (arrangementSet) {
		arrangementSet->displayInformation();
	}
}


void KPDGUI::solutionListRightClickActions(QPoint pos) {

	QTreeWidgetItem * item = kpdguiSolutionList->itemAt(pos);

	QMenu * menu = new QMenu(this);
	QAction * clusterAction;
	QAction * displayInformationAction = new QAction("View Information", this);

	KPDGUIArrangementWrapper * wrapper = dynamic_cast<KPDGUIArrangementWrapper *>(item);
	if (wrapper) {
		
		clusterAction = new QAction("Cluster Arrangement", this);

		connect(clusterAction, SIGNAL(triggered()), wrapper->getArrangement(), SLOT(cluster()));

		menu->addAction(clusterAction);
	}
	else {
		KPDGUIArrangementSet * arrangementSet = dynamic_cast<KPDGUIArrangementSet *>(item);
		if (arrangementSet) {

			clusterAction = new QAction("Cluster Solution", this);
			
			connect(clusterAction, SIGNAL(triggered()), arrangementSet, SLOT(cluster()));
			connect(displayInformationAction, SIGNAL(triggered()), arrangementSet, SLOT(displayInformation()));

			menu->addAction(clusterAction);
			menu->addSeparator();
			menu->addAction(displayInformationAction);
		}
	}


	if (menu->actions().size() > 0) {
		menu->popup(kpdguiArrangementList->viewport()->mapToGlobal(pos));
	}
}

void KPDGUI::updateMatches() {

	KPDGUIDonor * donor = dynamic_cast<KPDGUIDonor *>(sender());

	if (donor) {

		if (!donor->isAltruistic()) {
			KPDGUICandidate * pairedCandidate = donor->getParentNode()->getCandidate();
			KPDCrossmatchResult result = kpdguiCrossmatchFunctions->performCrossmatch(donor, pairedCandidate);
			donor->setCompatibilityWithPairedCandidate(result);
		}

		foreach(KPDGUIMatch * match, donor->getMatches()) {

			KPDGUICandidate * matchedCandidate = match->getCandidate();

			KPDCrossmatchResult crossmatch = kpdguiCrossmatchFunctions->performCrossmatch(donor, matchedCandidate);
			double fiveYearSurvival = kpdguiCrossmatchFunctions->calculateSurvival(donor, matchedCandidate, 1);
			double tenYearSurvival = kpdguiCrossmatchFunctions->calculateSurvival(donor, matchedCandidate, 0);
			bool difficultToMatch = kpdguiCrossmatchFunctions->determineDifficultMatch(donor, matchedCandidate);

			match->updateCrossmatchResults(crossmatch, fiveYearSurvival, tenYearSurvival, difficultToMatch);
		}
	}
	else {
		KPDGUICandidate * candidate = dynamic_cast<KPDGUICandidate *>(sender());

		if (candidate) {

			foreach(KPDGUIDonor * donor, candidate->getParentNode()->getDonors()) {

				KPDCrossmatchResult result = kpdguiCrossmatchFunctions->performCrossmatch(donor, candidate);
				donor->setCompatibilityWithPairedCandidate(result);

			}

			foreach(KPDGUIMatch * match, candidate->getMatches()) {
				KPDGUIDonor * matchedDonor = match->getDonor();

				KPDCrossmatchResult crossmatch = kpdguiCrossmatchFunctions->performCrossmatch(matchedDonor, candidate);
				double fiveYearSurvival = kpdguiCrossmatchFunctions->calculateSurvival(matchedDonor, candidate, 1);
				double tenYearSurvival = kpdguiCrossmatchFunctions->calculateSurvival(matchedDonor, candidate, 0);
				bool difficultToMatch = kpdguiCrossmatchFunctions->determineDifficultMatch(matchedDonor, candidate);

				match->updateCrossmatchResults(crossmatch, fiveYearSurvival, tenYearSurvival, difficultToMatch);
			}
		}
	}

	emit displaySettingsChanged(kpdguiDisplaySettings);
}
