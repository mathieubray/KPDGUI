#include "KPDGUIGraphicsScene.h"

const qreal Pi = 3.14159265;
const qreal Tol = 3;

KPDGUIGraphicsScene::KPDGUIGraphicsScene() : QGraphicsScene()
{
	setBackgroundBrush(QBrush(Qt::lightGray, Qt::Dense5Pattern));
	
	createNodeActions();
}

KPDGUIGraphicsScene::~KPDGUIGraphicsScene()
{

}

void KPDGUIGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseReleaseEvent(event);

	emit mouseReleased();
}

void KPDGUIGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	QMenu menu(event->widget());
	QList<QGraphicsItem*> items = selectedItems();

	if (selectedItems().size() >= 2){
		bool allHeld = true;
		foreach(QGraphicsItem * item, items){
			KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
			if (!node->isOnHold()){
				allHeld = false;
			}
		}
		menu.addAction(clusterMultipleNodesAction);
		menu.addSeparator();
		if (allHeld){
			menu.addAction(unholdMultipleNodesAction);
		}
		else {
			menu.addAction(holdMultipleNodesAction);
		}
		
		menu.addAction(deleteMultipleNodesAction);
	}

	else if (selectedItems().size() == 1){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(items.first());
		if (node){
			menu.addAction(editNodeAction);
			menu.addSeparator();
			if (node->isOnHold()){
				menu.addAction(unholdNodeAction);
			}
			else {
				menu.addAction(holdNodeAction);
			}
			menu.addAction(deleteNodeAction);
		}
	}

	menu.exec(event->screenPos());
}

void KPDGUIGraphicsScene::editNode(){
	QList<QGraphicsItem*> items = selectedItems();
	if (items.size() == 1){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(items.first());
		if (node){
			if (node->getType() == AD){
				int id = node->getInternalID();
				Donor * donor = node->getDonorPtr();
				QString comment = node->getComment();

				AltruisticDonorDialog adDialog(id, donor, comment, true, 0);
				if (adDialog.exec()){
					bool majorChange = false;
					if (donor->BT != adDialog.donorBTComboBox->currentText()){
						majorChange = true;
					}
					if (donor->donorA.size() > 0){
						if (donor->donorA[0] != adDialog.donorA1LineEdit->text()){ 
							majorChange = true; 
						}
						if (donor->donorA.size() > 1){
							if (donor->donorA[1] != adDialog.donorA2LineEdit->text()){
								majorChange = true; 
							}
						}
					}

					if (donor->donorB.size() > 0){
						if (donor->donorB[0] != adDialog.donorB1lineEdit->text()){ 
							majorChange = true; 
						}
						if (donor->donorB.size() > 1){
							if (donor->donorB[1] != adDialog.donorB2LineEdit->text()){ 
								majorChange = true; 
							}
						}
					}

					if (donor->donorCW.size() > 0){
						if (donor->donorCW[0] != adDialog.donorCW1LineEdit->text()){ 
							majorChange = true; 
						}
						if (donor->donorCW.size() > 1){
							if (donor->donorCW[1] != adDialog.donorCW2LineEdit->text()){ 
								majorChange = true; 
							}
						}
					}

					if (donor->donorDP.size() > 0){
						if (donor->donorDP[0] != adDialog.donorDP1LineEdit->text()){ 
							majorChange = true; 
						}
						if (donor->donorDP.size() > 1){
							if (donor->donorDP[1] != adDialog.donorDP2LineEdit->text()){ 
								majorChange = true; 
							}
						}
					}

					if (donor->donorDQ.size() > 0){
						if (donor->donorDQ[0] != adDialog.donorDQ1LineEdit->text()){ 
							majorChange = true; 
						}
						if (donor->donorDQ.size() > 1){
							if (donor->donorDQ[1] != adDialog.donorDQ2LineEdit->text()){
								majorChange = true; 
							}
						}
					}

					if (donor->donorDR.size() > 0){
						if (donor->donorDR[0] != adDialog.donorDR1LineEdit->text()){
							majorChange = true; 
						}
						if (donor->donorDR.size() > 1){
							if (donor->donorDR[1] != adDialog.donorDR2LineEdit->text()){  
								majorChange = true; 
							}
						}
					}

					if (donor->donorBW4 != adDialog.donorBW4CheckBox->isChecked()){
						majorChange = true;
					}
					if (donor->donorBW6 != adDialog.donorBW6CheckBox->isChecked()){
						majorChange = true;
					}
					if (donor->donorDR51 != adDialog.donorDR51CheckBox->isChecked()){
						majorChange = true;
					}
					if (donor->donorDR52 != adDialog.donorDR52CheckBox->isChecked()){
						majorChange = true;
					}
					if (donor->donorDR53 != adDialog.donorDR53CheckBox->isChecked()){
						majorChange = true;
					}

					if (majorChange){
						int r = QMessageBox::warning(0, tr("KPD"),
							tr("Major changes to nodes will result in their removal from previous solutions. Are you sure you want to submit these changes?"),
							QMessageBox::Yes | QMessageBox::No);
						if (r == QMessageBox::Yes) {
							Donor d;

							d.name = adDialog.donorNameLineEdit->text();
							d.age = adDialog.donorAgeSpinBox->value();
							d.BT = adDialog.donorBTComboBox->currentText();

							double donorHeight = adDialog.donorHeightSpinBox->value();
							double donorWeight = adDialog.donorWeightSpinBox->value();
							d.BMI =  donorWeight / donorHeight / donorHeight;
							d.weight = donorWeight;
							QString donorGender = adDialog.donorGenderComboBox->currentText();
							if (donorGender == "Male"){ d.genderMale = true; }
							else { d.genderMale = false; }

							//d.id = -1;
							//d.donorid = -1;

							d.donorA.push_back(adDialog.donorA1LineEdit->text());
							d.donorA.push_back(adDialog.donorA2LineEdit->text());
							d.donorB.push_back(adDialog.donorB1lineEdit->text());
							d.donorB.push_back(adDialog.donorB2LineEdit->text());
							d.donorCW.push_back(adDialog.donorCW1LineEdit->text());
							d.donorCW.push_back(adDialog.donorCW2LineEdit->text());
							d.donorDP.push_back(adDialog.donorDP1LineEdit->text());
							d.donorDP.push_back(adDialog.donorDP2LineEdit->text());
							d.donorDQ.push_back(adDialog.donorDQ1LineEdit->text());
							d.donorDQ.push_back(adDialog.donorDQ2LineEdit->text());
							d.donorDR.push_back(adDialog.donorDR1LineEdit->text());
							d.donorDR.push_back(adDialog.donorDR2LineEdit->text());
							d.donorBW4 = adDialog.donorBW4CheckBox->isChecked();
							d.donorBW6 = adDialog.donorBW6CheckBox->isChecked();
							d.donorDR51 = adDialog.donorDR51CheckBox->isChecked();
							d.donorDR52 = adDialog.donorDR52CheckBox->isChecked();
							d.donorDR53 = adDialog.donorDR53CheckBox->isChecked();
							d.type = KPDPairType::AD;

							QString comment = adDialog.commentTextEdit->toPlainText();
						}
					}
					else {
						node->setDonorName(adDialog.donorNameLineEdit->text());
						node->setDonorAge(adDialog.donorAgeSpinBox->value());
						double donorHeight = adDialog.donorHeightSpinBox->value();
						double donorWeight = adDialog.donorWeightSpinBox->value();
						node->setDonorBMI( donorWeight / donorHeight / donorHeight);
						node->setDonorWeight(donorWeight);
						QString donorGender = adDialog.donorGenderComboBox->currentText();
						if (node->getDonorGenderMale() == true && donorGender != "Male"){
							node->setDonorGenderMale(false);
						}
						else if (node->getDonorGenderMale() == false && donorGender != "Female"){
							node->setDonorGenderMale(true);
						}

						node->setComment(adDialog.commentTextEdit->toPlainText());

						emit editNode(node->getInternalID());
					}
				}
			}
			else {
				int id = node->getInternalID();
				Donor * donor = node->getDonorPtr();
				Candidate * candidate = node->getCandidatePtr();
				QString comment = node->getComment();

				PairDialog pairDialog(id, donor, candidate, comment, true, 0);
				if (pairDialog.exec()){
					bool majorChange = false;

					if (donor->BT != pairDialog.donorBTComboBox->currentText()){
						majorChange = true;
					}
					if (candidate->BT != pairDialog.recipBTComboBox->currentText()){						
						majorChange = true;
					}
					if (candidate->pra != pairDialog.recipPRASpinBox->value()){
						majorChange = true;
					}
					
					QString antibodies = pairDialog.recipHLALineEdit->text();
					if (node->getRecipHLAString() != antibodies){
						majorChange = true;
					}					

					if (donor->donorA.size() > 0){
						if (donor->donorA[0] != pairDialog.donorA1LineEdit->text()){
							majorChange = true; 
						}
						if (donor->donorA.size() > 1){
							if (donor->donorA[1] != pairDialog.donorA2LineEdit->text()){
								majorChange = true; 
							}
						}
					}					
					
					if (donor->donorB.size() > 0){
						if (donor->donorB[0] != pairDialog.donorB1lineEdit->text()){
							majorChange = true; 
						}
						if (donor->donorB.size() > 1){
							if (donor->donorB[1] != pairDialog.donorB2LineEdit->text()){
								majorChange = true; 
							}
						}
					}

					if (donor->donorCW.size() > 0){
						if (donor->donorCW[0] != pairDialog.donorCW1LineEdit->text()){ 
							majorChange = true; 
						}
						if (donor->donorCW.size() > 1){
							if (donor->donorCW[1] != pairDialog.donorCW2LineEdit->text()){
								majorChange = true; 
							}
						}
					}

					if (donor->donorDP.size() > 0){
						if (donor->donorDP[0] != pairDialog.donorDP1LineEdit->text()){ 
							majorChange = true; 
						}
						if (donor->donorDP.size() > 1){
							if (donor->donorDP[1] != pairDialog.donorDP2LineEdit->text()){ 
								majorChange = true; 
							}
						}
					}
					
					if (donor->donorDQ.size() > 0){
						if (donor->donorDQ[0] != pairDialog.donorDQ1LineEdit->text()){
							majorChange = true; 
						}
						if (donor->donorDQ.size() > 1){
							if (donor->donorDQ[1] != pairDialog.donorDQ2LineEdit->text()){ 
								majorChange = true; 
							}
						}
					}
					
					if (donor->donorDR.size() > 0){
						if (donor->donorDR[0] != pairDialog.donorDR1LineEdit->text()){ 
							majorChange = true; 
						}
						if (donor->donorDR.size() > 1){
							if (donor->donorDR[1] != pairDialog.donorDR2LineEdit->text()){
								majorChange = true; 
							}
						}
					}

					if (donor->donorBW4 != pairDialog.donorBW4CheckBox->isChecked()){
						majorChange = true;
					}
					if (donor->donorBW6 != pairDialog.donorBW6CheckBox->isChecked()){
						majorChange = true;
					}
					if (donor->donorDR51 != pairDialog.donorDR51CheckBox->isChecked()){
						majorChange = true;
					}
					if (donor->donorDR52 != pairDialog.donorDR52CheckBox->isChecked()){
						majorChange = true;
					}
					if (donor->donorDR53 != pairDialog.donorDR53CheckBox->isChecked()){
						majorChange = true;
					}

					if (majorChange){
						int r = QMessageBox::warning(0, tr("KPD"),
							tr("Major changes to nodes will result in their removal from previous solutions. Are you sure you want to submit these changes?"),
							QMessageBox::Yes | QMessageBox::No);
						if (r == QMessageBox::Yes) {
							Donor d;
							Candidate c;

							d.name = pairDialog.donorNameLineEdit->text();
							c.name = pairDialog.recipNameLineEdit->text();
							d.age = pairDialog.donorAgeSpinBox->value();
							c.age = pairDialog.recipAgeSpinBox->value();
							d.BT = pairDialog.donorBTComboBox->currentText();
							c.BT = pairDialog.recipBTComboBox->currentText();
							c.pra = pairDialog.recipPRASpinBox->value();
							
							double recipHeight = pairDialog.recipHeightSpinBox->value();
							double recipWeight = pairDialog.recipWeightSpinBox->value();
							c.BMI =  recipWeight / recipHeight / recipHeight;
							c.weight = recipWeight;
							c.diabetes = pairDialog.recipDiabetesCheckBox->isChecked();
							QString recipGender = pairDialog.recipGenderComboBox->currentText();
							if (recipGender == "Male"){ c.genderMale = true; }
							else { c.genderMale = false; }
							c.race = pairDialog.recipRaceComboBox->currentText();
							c.prevTrans = pairDialog.recipPrevTransCheckBox->isChecked();
							c.TOD = pairDialog.recipTODSpinBox->value();
							c.hepC = pairDialog.recipHepCCheckBox->isChecked();

							double donorHeight = pairDialog.donorHeightSpinBox->value();
							double donorWeight = pairDialog.donorWeightSpinBox->value();
							d.BMI =  donorWeight / donorHeight / donorHeight;
							d.weight = donorWeight;
							QString donorGender = pairDialog.donorGenderComboBox->currentText();
							if (donorGender == "Male"){ d.genderMale = true; }
							else { d.genderMale = false; }

							//d.id = -1;
							//d.donorid = -1;
							//c.id = -1;
							//c.recipid = -1;

							QString antibodies = pairDialog.recipHLALineEdit->text();
							QStringList antibodyList = antibodies.split(";");

							foreach(QString antibody, antibodyList){
								c.antibodies.push_back(antibody);
							}

							d.donorA.push_back(pairDialog.donorA1LineEdit->text());
							d.donorA.push_back(pairDialog.donorA2LineEdit->text());
							d.donorB.push_back(pairDialog.donorB1lineEdit->text());
							d.donorB.push_back(pairDialog.donorB2LineEdit->text());
							d.donorCW.push_back(pairDialog.donorCW1LineEdit->text());
							d.donorCW.push_back(pairDialog.donorCW2LineEdit->text());
							d.donorDP.push_back(pairDialog.donorDP1LineEdit->text());
							d.donorDP.push_back(pairDialog.donorDP2LineEdit->text());
							d.donorDQ.push_back(pairDialog.donorDQ1LineEdit->text());
							d.donorDQ.push_back(pairDialog.donorDQ2LineEdit->text());
							d.donorDR.push_back(pairDialog.donorDR1LineEdit->text());
							d.donorDR.push_back(pairDialog.donorDR2LineEdit->text());
							d.donorBW4 = pairDialog.donorBW4CheckBox->isChecked();
							d.donorBW6 = pairDialog.donorBW6CheckBox->isChecked();
							d.donorDR51 = pairDialog.donorDR51CheckBox->isChecked();
							d.donorDR52 = pairDialog.donorDR52CheckBox->isChecked();
							d.donorDR53 = pairDialog.donorDR53CheckBox->isChecked();
							d.type = KPDPairType::PAIR;

							QString comment = pairDialog.commentTextEdit->toPlainText();							
						}						
					}
					else {
						node->setDonorName(pairDialog.donorNameLineEdit->text());
						node->setRecipName(pairDialog.recipNameLineEdit->text());
						node->setDonorAge(pairDialog.donorAgeSpinBox->value());
						node->setRecipAge(pairDialog.recipAgeSpinBox->value());
						double recipHeight = pairDialog.recipHeightSpinBox->value();
						double recipWeight = pairDialog.recipWeightSpinBox->value();
						node->setRecipBMI( recipWeight / recipHeight / recipHeight);
						node->setRecipWeight(recipWeight);
						node->setRecipDiabetes(pairDialog.recipDiabetesCheckBox->isChecked());
						QString recipGender(pairDialog.recipGenderComboBox->currentText());
						if (node->getRecipGenderMale() == true && recipGender != "Male"){
							node->setRecipGenderMale(false);
						}
						else if (node->getRecipGenderMale() == false && recipGender != "Female"){
							node->setRecipGenderMale(true);
						}
						node->setRecipRace(pairDialog.recipRaceComboBox->currentText());
						node->setRecipPrevTrans(pairDialog.recipPrevTransCheckBox->isChecked());
						node->setRecipTOD(pairDialog.recipTODSpinBox->value());
						node->setRecipHepC(pairDialog.recipHepCCheckBox->isChecked());
						double donorHeight = pairDialog.donorHeightSpinBox->value();
						double donorWeight = pairDialog.donorWeightSpinBox->value();
						node->setDonorBMI( donorWeight / donorHeight / donorHeight);
						node->setDonorWeight(donorWeight);
						QString donorGender = pairDialog.donorGenderComboBox->currentText();
						if (node->getDonorGenderMale() == true && donorGender != "Male"){
							node->setDonorGenderMale(false);
						}
						else if (node->getDonorGenderMale() == false && donorGender != "Female"){
							node->setDonorGenderMale(true);
						}

						node->setComment(pairDialog.commentTextEdit->toPlainText());

						emit editNode(node->getInternalID());
					}
				}
			}
		}
	}
}

void KPDGUIGraphicsScene::holdNode(){
	QList<QGraphicsItem*> items = selectedItems();
	KPDGUINode *node = dynamic_cast<KPDGUINode *>(items.first());
	if (node){
		node->setHoldStatus(true);
		emit screenChanged();
	}	
}

void KPDGUIGraphicsScene::unholdNode(){
	QList<QGraphicsItem*> items = selectedItems();
	KPDGUINode *node = dynamic_cast<KPDGUINode *>(items.first());
	if (node){
		node->setHoldStatus(false);
		emit screenChanged();
	}	
}

void KPDGUIGraphicsScene::deleteNode(){
	
	int r = QMessageBox::warning(0,"KPD","Clicking 'Yes' will remove selected pair from pool and all previously found solutions permanently.\nAre you sure you want to delete selected pair?",
		QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	if (r == QMessageBox::Yes) {
		QList<QGraphicsItem*> items = selectedItems();
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(items.first());
		if (node){
			emit deleteNode(node->getInternalID());
		}
	}
}

void KPDGUIGraphicsScene::holdMultipleNodes(){
	QList<QGraphicsItem*> items = selectedItems();
	foreach(QGraphicsItem * item, items){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
		if (node){
			node->setHoldStatus(true);
			emit screenChanged();
		}
	}	
}

void KPDGUIGraphicsScene::unholdMultipleNodes(){
	QList<QGraphicsItem*> items = selectedItems();
	foreach(QGraphicsItem * item, items){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
		if (node){
			node->setHoldStatus(false);
			emit screenChanged();
		}
	}
}

void KPDGUIGraphicsScene::clusterMultipleNodes(){
	qreal avgx = 0;
	qreal avgy = 0;
	qreal dist = 50+10*selectedItems().size();

	QList<QGraphicsItem*> items = selectedItems();
	foreach(QGraphicsItem * item, items){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
		if (node){
			avgx += node->x();
			avgy += node->y();
		}
	}

	qreal x = avgx / selectedItems().size();
	qreal y = avgy / selectedItems().size();
	
	qreal angle = (2 * Pi) / selectedItems().size();
	qreal nodeAngle = Pi;

	QApplication::setOverrideCursor(Qt::WaitCursor);
	QApplication::processEvents();

	foreach(QGraphicsItem * item, items){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
		if (node){
			node->setVisible(false);
			if (!(abs((node->x()) - (x + dist*cos(nodeAngle))) < Tol && abs((node->y()) - (y + dist*sin(nodeAngle)) < Tol))){
				node->setPos(QPoint(x + dist*cos(nodeAngle), y + dist*sin(nodeAngle)));
			}
			nodeAngle += angle;
			node->setVisible(true);
			node->setSelected(true);
		}
	}

	QApplication::restoreOverrideCursor();
	QApplication::processEvents();
}

void KPDGUIGraphicsScene::deleteMultipleNodes(){

	int r = QMessageBox::warning(0, "KPD", "Clicking \"Yes\" will remove selected pairs from pool and all previously found solutions permanently.\nAre you sure you want to delete selected pairs?",
		QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	if (r == QMessageBox::Yes) {
		QApplication::setOverrideCursor(Qt::WaitCursor);
		QApplication::processEvents();
		QList<QGraphicsItem*> items = selectedItems();
		foreach(QGraphicsItem * item, items){
			KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
			if (node){
				node->setSelected(false);
			}
		}
		foreach(QGraphicsItem * item, items){
			KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
			if (node){
				emit deleteNode(node->getInternalID());
			}
		}
		QApplication::restoreOverrideCursor();
		QApplication::processEvents();
	}	
}

void KPDGUIGraphicsScene::createNodeActions(){
	editNodeAction = new QAction(tr("&Edit"), this);
	connect(editNodeAction, SIGNAL(triggered()), this, SLOT(editNode()));

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
	connect(deleteMultipleNodesAction, SIGNAL(triggered()), this, SLOT(deleteMultipleNodes()));
}