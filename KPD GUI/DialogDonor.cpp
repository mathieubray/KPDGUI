#include <QtGui>

#include "DialogDonor.h"

#include "KPDGUIDonor.h"

#include "MultiSelectCompleter.h"

//New Donor Constructor
DialogDonor::DialogDonor(QWidget * parent) : QDialog(parent)
{
	setupUi(this);
	additionalSetup();
}

//Edit Donor Constructor
DialogDonor::DialogDonor(KPDGUIDonor * donor, bool disableMajorEdits, QWidget *parent) : QDialog(parent)
{
	setupUi(this);
	additionalSetup();
	
	setWindowTitle("Edit Donor Information");

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
	
	//Height
	double donorHeight = sqrt(donor->getWeight() / ( donor->getBMI()));
	donorHeightSpinBox->setValue(donorHeight);

	//Weight
	donorWeightSpinBox->setValue(donor->getWeight());

	

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

	if (disableMajorEdits){
		donorBTComboBox->setEnabled(false);

		donorHLAA1ComboBox->setEnabled(false);
		donorHLAA2ComboBox->setEnabled(false);
		donorHLAB1ComboBox->setEnabled(false);
		donorHLAB2ComboBox->setEnabled(false);
		donorHLACW1ComboBox->setEnabled(false);
		donorHLACW2ComboBox->setEnabled(false);
		donorHLADQ1ComboBox->setEnabled(false);
		donorHLADQ2ComboBox->setEnabled(false);
		donorHLADR1ComboBox->setEnabled(false);
		donorHLADR2ComboBox->setEnabled(false);

		donorBW4CheckBox->setEnabled(false);
		donorBW6CheckBox->setEnabled(false);
		donorDR51CheckBox->setEnabled(false);
		donorDR52CheckBox->setEnabled(false);
		donorDR53CheckBox->setEnabled(false);

		donorHLALineEdit->setEnabled(false);
	}

	//Comments
	commentTextEdit->setText(donor->getComment());
}


void DialogDonor::additionalSetup(){

	//Comment Tab
	commentTextEdit = new QTextEdit();
	donorInfoTabWidget->addTab(commentTextEdit, "Comments");

	//HLA Completers
	QString hla = "A1,A2,A3,A9,A10,A11,A19,A23,A24,A25,A26,A28,A29,A30,A31,A32,A33,A34,A36,A43,A66,A68,A69,A74,A80,A203,A210,A2403,A6601,A6602,B5,B7,B8,B12,B13,B14,B15,B16,B17,B18,B21,B22,B27,B35,B37,B38,B39,B40,B41,B42,B44,B45,B46,B47,B48,B49,B50,B51,B52,B53,B54,B55,B56,B57,B58,B59,B60,B61,B62,B63,B64,B65,B67,B70,B71,B72,B73,B75,B76,B77,B78,B81,B82,B703,B804,B1304,B2708,B3901,B3902,B3905,B4005,B5102,B5103,B8201,BW4,BW6,CW1,CW2,CW3,CW4,CW5,CW6,CW7,CW8,CW9,CW10,CW12,CW13,CW14,CW15,CW16,CW17,CW18,DQ1,DQ2,DQ3,DQ4,DQ5,DQ6,DQ7,DQ8,DQ9,DQB1,DQB2,DQB3,DQB4,DQB5,DQB6,DQB7,DQB8,DQB9,DR1,DR2,DR3,DR4,DR5,DR6,DR7,DR8,DR9,DR10,DR11,DR12,DR13,DR14,DR15,DR16,DR17,DR18,DR103,DR1403,DR1404,DR51,DR52,DR53";
	QStringList hlaList = hla.split(",");

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

	MultiSelectCompleter * hlaCompleter = new MultiSelectCompleter(hlaList, this);

	donorHLALineEdit->setCompleter(hlaCompleter);

}