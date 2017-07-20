#ifndef DIALOGSURVIVALCALCULATOR_H
#define DIALOGSURVIVALCALCULATOR_H

#include <QtGui>
#include <QtWidgets>

#include "ui_DialogSurvivalCalculator.h"

#include "KPDGUIDashboardList.h"

#include "KPDGUIHLASelecter.h"

#include "KPDGUICrossmatchFunctions.h"

class DialogSurvivalCalculator : public QDialog, public Ui_DialogSurvivalCalculator
{
	Q_OBJECT

public:
	DialogSurvivalCalculator(KPDGUIDashboardList * donorDashboard, KPDGUIDashboardList * candidateDashboard, KPDGUICrossmatchFunctions * functions, QWidget * parent = 0);
	~DialogSurvivalCalculator();

	KPDGUIDonor * donor;
	KPDGUICandidate * candidate;

	KPDGUICrossmatchFunctions * crossmatchFunctions;


private slots:

	void updateDonorAge(int age);
	void updateDonorBT(int btIndex);

	void updateDonorA();
	void updateDonorB();
	void updateDonorCW();
	void updateDonorDQ();
	void updateDonorDR();

	void updateDonorBW4(bool hla);
	void updateDonorBW6(bool hla);
	void updateDonorDR51(bool hla);
	void updateDonorDR52(bool hla);
	void updateDonorDR53(bool hla);

	void updateAdditionalDonorHLA(QString hla);

	void updateDonorGender(int genderIndex);
	void updateDonorRace(int raceIndex);
	void updateDonorHeight(double height);
	void updateDonorWeight(double weight);
	void updateDonorCigaretteUse(bool cigarette);

	void updateCandidateAge(int age);
	void updateCandidatePRA(int pra);
	void updateCandidateBT(int btIndex);

	void updateCandidateHLA(QString hla);
	
	void updateCandidateGender(int genderIndex);
	void updateCandidateRace(int raceIndex);
	void updateCandidateDiabetes(bool diabetes);
	void updateCandidateWeight(double weight);
	void updateCandidateHeight(double height);

	void updateCandidatePrevTrans(bool prevTrans);
	void updateCandidateTOD(double TOD);
	void updateCandidateHepC(bool hepC);
	void updateCandidateInsurance(int insuranceIndex);

	void updateDonorInfo(QListWidgetItem * item);
	void updateCandidateInfo(QListWidgetItem * item);

	void updateSurvival();

signals:
	void survivalSignal();

private:

	void additionalSetup(KPDGUIDashboardList * d, KPDGUIDashboardList * c);

	QMap<QListWidgetItem *, KPDGUIDonor *> donorMap;
	QMap<QListWidgetItem *, KPDGUICandidate *> candidateMap;

};

#endif