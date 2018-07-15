
#include "DialogDonor.h"

#include "KPDGUIDonor.h"

//New Donor Constructor
DialogDonor::DialogDonor(bool showAdditionalDonorButton, QWidget * parent) : QDialog(parent)
{
	setupUi(this);

	additionalDonor = false;
	additionalDonorButton->setVisible(showAdditionalDonorButton);

	additionalSetup();
}

//Edit Donor Constructor
DialogDonor::DialogDonor(KPDGUIDonor * donor, bool showAdditionalDonorButton, QWidget *parent) : QDialog(parent)
{
	setupUi(this);

	additionalDonor = false;
	additionalDonorButton->setVisible(showAdditionalDonorButton);

	additionalSetup();
	
	if (donor->isAltruistic()) {
		setWindowTitle("Edit - " + donor->getName() + " (" + QString::number(donor->getID()) + ")");
	}
	else {
		setWindowTitle("Edit - " + donor->getName() + " (" + QString::number(donor->getID()) + "-" + QString::number(donor->getDonorNumber()) + ")");
	}

	//Name
	donorNameLineEdit->setText(donor->getName());

	//Age
	donorAgeSpinBox->setValue(donor->getAge());

	//Blood Type
	donorBTComboBox->setCurrentIndex(KPDFunctions::bloodTypeToInt(donor->getBT()));
	
	//Failure Probability
	donorFailureProbabilitySpinBox->setValue(donor->getFailureProbability());

	//Status
	donorStatusCheckBox->setChecked(donor->getStatus());

	//Gender
	if (donor->getMale()) { donorGenderComboBox->setCurrentIndex(0); }
	else { donorGenderComboBox->setCurrentIndex(1); }
	
	//Race
	donorRaceComboBox->setCurrentIndex(KPDFunctions::raceToInt(donor->getRace()));

	//Height
	donorHeightSpinBox->setValue(donor->getHeight());

	//Weight
	donorWeightSpinBox->setValue(donor->getWeight());

	//Cigarette
	donorCigaretteCheckBox->setChecked(donor->getCigarette());	

	//HLA
	if (donor->getA().size() >= 1){
		int hlaA1index = donorHLAA1ComboBox->findText(donor->getA().at(0));
		if (hlaA1index >= 0){
			donorHLAA1ComboBox->setCurrentIndex(hlaA1index);
		}
		if (donor->getA().size() >= 2){
			int hlaA2index = donorHLAA2ComboBox->findText(donor->getA().at(1));
			if (hlaA2index >= 0){
				donorHLAA2ComboBox->setCurrentIndex(hlaA2index);
			}
		}
	}
	if (donor->getB().size() >= 1){
		int hlaB1index = donorHLAB1ComboBox->findText(donor->getB().at(0));
		if (hlaB1index >= 0){
			donorHLAB1ComboBox->setCurrentIndex(hlaB1index);
		}
		if (donor->getB().size() >= 2){
			int hlaB2index = donorHLAB2ComboBox->findText(donor->getB().at(1));
			if (hlaB2index >= 0){
				donorHLAB2ComboBox->setCurrentIndex(hlaB2index);
			}
		}
	}
	if (donor->getCW().size() >= 1){
		int hlaCW1index = donorHLACW1ComboBox->findText(donor->getCW().at(0));
		if (hlaCW1index >= 0){
			donorHLACW1ComboBox->setCurrentIndex(hlaCW1index);
		}
		if (donor->getCW().size() >= 2){
			int hlaCW2index = donorHLACW2ComboBox->findText(donor->getCW().at(1));
			if (hlaCW2index >= 0){
				donorHLACW2ComboBox->setCurrentIndex(hlaCW2index);
			}
		}
	}
	if (donor->getDQ().size() >= 1){
		int hlaDQ1index = donorHLADQ1ComboBox->findText(donor->getDQ().at(0));
		if (hlaDQ1index >= 0){
			donorHLADQ1ComboBox->setCurrentIndex(hlaDQ1index);
		}
		if (donor->getDQ().size() >= 2){
			int hlaDQ2index = donorHLADQ2ComboBox->findText(donor->getDQ().at(1));
			if (hlaDQ2index >= 0){
				donorHLADQ2ComboBox->setCurrentIndex(hlaDQ2index);
			}
		}
	}
	if (donor->getDR().size() >= 1){
		int hlaDR1index = donorHLADR1ComboBox->findText(donor->getDR().at(0));
		if (hlaDR1index >= 0){
			donorHLADR1ComboBox->setCurrentIndex(hlaDR1index);
		}
		if (donor->getDR().size() >= 2){
			int hlaDR2index = donorHLADR2ComboBox->findText(donor->getDR().at(1));
			if (hlaDR2index >= 0){
				donorHLADR2ComboBox->setCurrentIndex(hlaDR2index);
			}
		}
	}

	donorBW4CheckBox->setChecked(donor->getBW4());
	donorBW6CheckBox->setChecked(donor->getBW6());
	donorDR51CheckBox->setChecked(donor->getDR51());
	donorDR52CheckBox->setChecked(donor->getDR52());
	donorDR53CheckBox->setChecked(donor->getDR53());
	
	//Additional Donor HLA
	QString additionalDonorHLAString = "";
	foreach(QString additionalDonorHLA, donor->getAdditionalHLA()){
		additionalDonorHLAString.append(additionalDonorHLA);
		additionalDonorHLAString.append(";");
	}
	additionalDonorHLAString.chop(1);
	donorHLALineEdit->setText(additionalDonorHLAString);	

	//Comments
	commentTextEdit->setText(donor->getComment());
}

bool DialogDonor::getAdditionalDonor() {
	return (additionalDonor);
}

void DialogDonor::setAdditionalDonor() {
	additionalDonor = true;
}

void DialogDonor::additionalSetup(){

	//Comment Tab
	commentTextEdit = new QTextEdit();
	donorInfoTabWidget->addTab(commentTextEdit, "Comments");

	//HLA Completers
	QStringList hlaList = HLA_LIST.split(",");

	donorHLAA1ComboBox->addItem("");
	donorHLAA2ComboBox->addItem("");
	donorHLAB1ComboBox->addItem("");
	donorHLAB2ComboBox->addItem("");
	donorHLACW1ComboBox->addItem("");
	donorHLACW2ComboBox->addItem("");
	donorHLADQ1ComboBox->addItem("");
	donorHLADQ2ComboBox->addItem("");
	donorHLADR1ComboBox->addItem("");
	donorHLADR2ComboBox->addItem("");

	QStringList hlaAList = hlaList.filter(QRegularExpression("^A"));
	foreach(QString hla, hlaAList){
		donorHLAA1ComboBox->addItem(hla);
		donorHLAA2ComboBox->addItem(hla);
	}

	QStringList hlaBList = hlaList.filter(QRegularExpression("^B"));
	foreach(QString hla, hlaBList){
		if (hla != "BW4" && hla != "BW6"){
			donorHLAB1ComboBox->addItem(hla);
			donorHLAB2ComboBox->addItem(hla);
		}
	}

	QStringList hlaCWList = hlaList.filter(QRegularExpression("^CW"));
	foreach(QString hla, hlaCWList){
		donorHLACW1ComboBox->addItem(hla);
		donorHLACW2ComboBox->addItem(hla);
	}

	QStringList hlaDQList = hlaList.filter(QRegularExpression("^DQ"));
	foreach(QString hla, hlaDQList){
		donorHLADQ1ComboBox->addItem(hla);
		donorHLADQ2ComboBox->addItem(hla);
	}

	QStringList hlaDRList = hlaList.filter(QRegularExpression("^DR"));
	foreach(QString hla, hlaDRList){
		if (hla != "DR51" && hla != "DR52" && hla != "DR53"){
			donorHLADR1ComboBox->addItem(hla);
			donorHLADR2ComboBox->addItem(hla);
		}
	}

	KPDGUIHLASelecter * hlaCompleter = new KPDGUIHLASelecter(hlaList, this);
	donorHLALineEdit->setCompleter(hlaCompleter);

}

void DialogDonor::setDefaultHeightWeight(int index) {

	if (index == 0) {
		donorHeightSpinBox->setValue(1.62);
		donorWeightSpinBox->setValue(76.0);
	}
	else if (index == 1) {
		donorHeightSpinBox->setValue(1.75);
		donorWeightSpinBox->setValue(89.0);
	}

}