#include "KPDGUISimulParam.h"

KPDGUISimulParam::KPDGUISimulParam(){
	//Default Parameters

	parametersSet = false;

	//Simulation Settings
	outputFolderName = "";
	allocScheme = "NEAD"; //DPD
	utilityScheme = "TRANSPLANTS"; //SCORE, SURVIVAL5YEAR, SURVIVAL10YEAR
	//pairEntryScheme = "ALL"; //ALL, SUBSET, POISSON
	//adEntryScheme = "ALL"; //ALL, SUBSET, CHANCE
	//samplingScheme = "WITH"; // WITHOUT
	//pairSelectionSeed = 0;
	//simulationConditionsSeed = 900707;

	//Numerical Parameters
	//simulations = 1;
	//months = 1;
	//arrivals = 30;
	//ads = 1;
	maxChainLength = 2;
	//attritionRate = 0.02;
	//renegeRate = 0.01;
	//pairFailureRate = 0.12;
	//probReturnToPool = 0.80;
	//exogenousFailureRate = 0.0;
	tiebreakIterations = 1;

	//Optimization Settings	
	muc = true;
	meuc = false;
	meus = false;
	scc = false;
	//fallbacks = true;

	//Data Configuration and Files
	data_configuration = "ASHLAGI"; //APD MATCH RUN, MICHIGAN, MATCH RUN, COMBINED
	//candidate_file = "ashlagi-candidates_with_demo_merged.csv";
	//donor_file = "ashlagi-donors_with_demo_fixed.csv";
	//pair_file = "michigandata-updated_fixed.csv";
	//info_file = "Info_APD.csv";
	//exInfo_file = "Extra_Info_APD.csv";
	//ndd_file = "NDD_APD.csv";
	//samePatient_file = "SamePat_APD.csv";
	//comp_file = "Comp_APD.csv";
	//weight_file = "Weight_APD.csv";

	//Output Suppression
	outputEdgeInfo = false;
	outputExchangeInfo = false;
	outputCycleInfo = false;
	outputSimInfo = false;
	outputPopulationStats = false;

	//Additional Flags
	praAdvantage = false;
	reserveOtoO = false;
	randomPairFailure = false;
	chainstorage = "LAST"; //FIRST, LAST
	checkDP = false;
	includeCompatiblePairs = false;
	includeABbridgeDonors = false;
}

KPDGUISimulParam::~KPDGUISimulParam(){

}


void KPDGUISimulParam::processParams(ParamInfoStruct paramInfo){

	parametersSet = true;

	maxChainLength = paramInfo.maxChainLength;
	string newScheme;
	if (paramInfo.utilScheme == "Transplants"){
		newScheme = "TRANSPLANTS";
	}
	else if (paramInfo.utilScheme == "5 Year Survival"){
		newScheme = "SURVIVAL5YEAR";
	}
	else if (paramInfo.utilScheme == "10 Year Survival"){
		newScheme = "SURVIVAL10YEAR";
	}
	else {
		newScheme = "SCORE";
	}

	utilityScheme = newScheme;

	muc = false; meuc = false; meus = false; scc = false;

	if (paramInfo.optScheme == "MUC"){
		muc = true;
	}
	else if (paramInfo.optScheme == "MEUC"){
		meuc = true;
	}
	else if (paramInfo.optScheme == "MEUS"){
		meus = true;
	}
	else if (paramInfo.optScheme == "SCC"){
		scc = true;
	}

	praAdvantage = paramInfo.praAdvantage;
	reserveOtoO = paramInfo.reserveOtoO;
	checkDP = paramInfo.checkDP;
	includeCompatiblePairs = paramInfo.includeCompatiblePairs;
	includeABbridgeDonors = paramInfo.includeABBridgeDonors;
	tiebreakIterations = paramInfo.numberOfSolutions;

	/*
	ifstream iFile(fileName.c_str());

	if (!iFile.is_open()){
	specs << "Cannot open file: " << fileName << endl;
	return false;
	}

	while (!iFile.eof()){

	stringstream lineStream;
	string line;
	getline(iFile, line);
	if (line.empty())
	continue;
	lineStream << line;

	while (!lineStream.eof()){
	string tokenOne;
	string tokenTwo;
	getline(lineStream, tokenOne, '=');
	getline(lineStream, tokenTwo, '=');

	//Simulation Settings
	if (tokenOne.compare("#outputfoldername") == 0){ outputFolderName = tokenTwo; }
	if (tokenOne.compare("#allocation") == 0){ allocScheme = tokenTwo; }
	if (tokenOne.compare("#utilityscheme") == 0){ utilityScheme = tokenTwo; }
	if (tokenOne.compare("#pairentryscheme") == 0){ pairEntryScheme = tokenTwo; }
	if (tokenOne.compare("#adentryscheme") == 0){ adEntryScheme = tokenTwo; }
	if (tokenOne.compare("#samplingscheme") == 0){ samplingScheme = tokenTwo; }
	if (tokenOne.compare("#pairselectionseed") == 0){ pairSelectionSeed = atoi(tokenTwo.c_str()); }
	if (tokenOne.compare("#simulationconditionsseed") == 0){ simulationConditionsSeed = atoi(tokenTwo.c_str()); }

	//Numerical Parameters
	if (tokenOne.compare("#simulations") == 0){ simulations = atoi(tokenTwo.c_str()); }
	if (tokenOne.compare("#months") == 0){ months = atoi(tokenTwo.c_str()); }
	if (tokenOne.compare("#arrivals") == 0){ arrivals = atof(tokenTwo.c_str()); }
	if (tokenOne.compare("#ads") == 0){ ads = atof(tokenTwo.c_str()); }
	if (tokenOne.compare("#maxchainlength") == 0){ maxChainLength = atoi(tokenTwo.c_str()); }
	if (tokenOne.compare("#attrition") == 0){ attritionRate = atof(tokenTwo.c_str()); }
	if (tokenOne.compare("#renege") == 0){ renegeRate = atof(tokenTwo.c_str()); }
	if (tokenOne.compare("#pairfailurerate") == 0){ pairFailureRate = atof(tokenTwo.c_str()); }
	if (tokenOne.compare("#probreturntopool") == 0){ probReturnToPool = atof(tokenTwo.c_str()); }
	if (tokenOne.compare("#exogenousfailurerate") == 0){ exogenousFailureRate = atof(tokenTwo.c_str()); }
	if (tokenOne.compare("#tiebreakIterations") == 0){ tiebreakIterations = atoi(tokenTwo.c_str()); }

	//Optimization Settings
	if (tokenOne.compare("#muc") == 0){
	if (tokenTwo.compare("TRUE") == 0){ muc = true; }
	else if (tokenTwo.compare("FALSE") == 0){ muc = false; }
	}
	if (tokenOne.compare("#meuc") == 0){
	if (tokenTwo.compare("TRUE") == 0){ meuc = true; }
	else if (tokenTwo.compare("FALSE") == 0){ meuc = false; }
	}
	if (tokenOne.compare("#meus") == 0){
	if (tokenTwo.compare("TRUE") == 0){ meus = true; }
	else if (tokenTwo.compare("FALSE") == 0){ meus = false; }
	}
	if (tokenOne.compare("#scc") == 0){
	if (tokenTwo.compare("TRUE") == 0){ scc = true; }
	else if (tokenTwo.compare("FALSE") == 0){ scc = false; }
	}
	if (tokenOne.compare("#fallbacks") == 0){
	if (tokenTwo.compare("TRUE") == 0){ fallbacks = true; }
	else if (tokenTwo.compare("FALSE") == 0){ fallbacks = false; }
	}

	//Data Configuration and Files
	if (tokenOne.compare("#dataconfiguration") == 0){
	data_configuration = tokenTwo;
	if (tokenTwo.compare("APD") == 0){
	candidate_file = "kalbfleisch-candidates_merged.csv";
	donor_file = "kalbfleisch-donors_fixed.csv";
	}
	else if (tokenTwo.compare("MICHIGAN") == 0){
	pair_file = "michigandata-updated_fixed.csv";
	}
	else if (tokenTwo.compare("COMBINED") == 0){
	pair_file = "michigandata-updated_fixed.csv";
	candidate_file = "kalbfleisch-candidates_merged.csv";
	donor_file = "kalbfleisch-donors_fixed.csv";
	}
	else if (tokenTwo.compare("APD MATCH RUN") == 0){
	info_file = "Info_APD.csv";
	exInfo_file = "Extra_Info_APD.csv";
	ndd_file = "NDD_APD.csv";
	samePatient_file = "SamePat_APD.csv";
	comp_file = "Comp_APD.csv";
	weight_file = "Weight_APD.csv";
	}
	}
	if (tokenOne.compare("#candidatefile") == 0){ candidate_file = tokenTwo; }
	if (tokenOne.compare("#donorfile") == 0){ donor_file = tokenTwo; }
	if (tokenOne.compare("#pairfile") == 0){ pair_file = tokenTwo; }

	//Output Suppression
	if (tokenOne.compare("#outputedgeinfo") == 0){
	if (tokenTwo.compare("TRUE") == 0){ outputEdgeInfo = true; }
	else if (tokenTwo.compare("FALSE") == 0){ outputEdgeInfo = false; }
	}
	if (tokenOne.compare("#outputexchangeinfo") == 0){
	if (tokenTwo.compare("TRUE") == 0){ outputExchangeInfo = true; }
	else if (tokenTwo.compare("FALSE") == 0){ outputExchangeInfo = false; }
	}
	if (tokenOne.compare("#outputcycleinfo") == 0){
	if (tokenTwo.compare("TRUE") == 0){ outputCycleInfo = true; }
	else if (tokenTwo.compare("FALSE") == 0){ outputCycleInfo = false; }
	}
	if (tokenOne.compare("#outputsiminfo") == 0){
	if (tokenTwo.compare("TRUE") == 0){ outputSimInfo = true; }
	else if (tokenTwo.compare("FALSE") == 0){ outputSimInfo = false; }
	}
	if (tokenOne.compare("#populationstats") == 0){
	if (tokenTwo.compare("TRUE") == 0){ outputPopulationStats = true; }
	else if (tokenTwo.compare("FALSE") == 0){ outputPopulationStats = false; }
	}

	//Addditional Flags
	if (tokenOne.compare("#praAdvantage") == 0){
	if (tokenTwo.compare("TRUE") == 0){ praAdvantage = true; }
	else if (tokenTwo.compare("FALSE") == 0){ praAdvantage = false; }
	}
	if (tokenOne.compare("#reserveOtoO") == 0){
	if (tokenTwo.compare("TRUE") == 0){ reserveOtoO = true; }
	else if (tokenTwo.compare("FALSE") == 0){ reserveOtoO = false; }
	}
	if (tokenOne.compare("#pairfailurerandom") == 0){
	if (tokenTwo.compare("TRUE") == 0){ randomPairFailure = true; }
	else if (tokenTwo.compare("FALSE") == 0){ randomPairFailure = false; }
	}
	if (tokenOne.compare("#chainstorage") == 0){
	chainstorage = tokenTwo;
	}
	if (tokenOne.compare("#checkdp") == 0){
	if (tokenTwo.compare("TRUE") == 0){ checkDP = true; }
	else if (tokenTwo.compare("FALSE") == 0){ checkDP = false; }
	}
	if (tokenOne.compare("#compatiblepairs") == 0){
	if (tokenTwo.compare("TRUE") == 0){ includeCompatiblePairs = true; }
	else if (tokenTwo.compare("FALSE") == 0){ includeCompatiblePairs = false; }
	}
	if (tokenOne.compare("#abbridgedonors") == 0){
	if (tokenTwo.compare("TRUE") == 0){ includeABbridgeDonors = true; }
	else if (tokenTwo.compare("FALSE") == 0){ includeABbridgeDonors = false; }
	}
	}
	}

	return true;
	*/
}

/*void KPDGUISimulParam::printSpecs(){

specs << "Simulation Settings" << endl;
specs << "-------------------" << endl << endl;

specs << "Output Folder: " << outputFolderName << endl;
specs << "Allocation Scheme: " << allocScheme << endl;
specs << "Utility Based On: ";
if (utilityScheme.compare("SURVIVAL5YEAR") == 0){
specs << "5 Year Survival" << endl;
}
else if (utilityScheme.compare("SURVIVAL10YEAR") == 0){
specs << "10 Year Survival" << endl;
}
else if (utilityScheme.compare("SCORE") == 0){
specs << "APD Score" << endl;
}
else if (utilityScheme.compare("TRANSPLANTS") == 0){
specs << "# of Transplants" << endl;
}
specs << "Pair Entry Scheme: " << pairEntryScheme << endl;
specs << "AD Entry Scheme: " << adEntryScheme << endl;
if (pairEntryScheme.compare("FIXED") == 0 || pairEntryScheme.compare("POISSON") == 0){
if (samplingScheme.compare("WITH") == 0){
specs << "Sample With Replacement" << endl;
}
else if (samplingScheme.compare("WITHOUT") == 0){
specs << "Sample Without Replacement" << endl;
}
}
specs << "Pair Selection Random Number Generator Seed: " << pairSelectionSeed << endl;
specs << "Simulation Conditions Random Number Generator Seed: " << simulationConditionsSeed << endl;
specs << endl;

specs << "Numerical Parameters" << endl;
specs << "--------------------" << endl << endl;

specs << "Simulations: " << simulations << endl;
specs << "# of Match Runs: " << months << endl;
if (pairEntryScheme.compare("ALL") != 0){
if (pairEntryScheme.compare("POISSON") == 0){
specs << "Expected ";
}
specs << "Arrivals: " << arrivals << endl;
}
else { specs << "All Pairs Added To Match Run" << endl; }
if (adEntryScheme.compare("ALL") != 0){
if (adEntryScheme.compare("CHANCE") == 0){
specs << "Chance That A Pair Is Substituted By";
}
specs << "ADs: " << ads << endl;
}
else { specs << "All ADs Added To Match Run" << endl; }
specs << "Maximum Chain Length: " << maxChainLength << endl;
specs << "Attrition Rate: " << attritionRate << endl;
specs << "Renege Rate: " << renegeRate << endl;
specs << "Pair Failure Rate: " << pairFailureRate << endl;
specs << "Probability That Failed Pair Returns To Pool: " << probReturnToPool << endl;
if (exogenousFailureRate == 0){
specs << "No Exogenous Failure Rate" << endl;
}
else {
specs << "Exogenous Failure Rate: " << exogenousFailureRate << endl;
}
if (tiebreakIterations == 1){
specs << "No Tiebreaking Between Possible Alternate Solutions" << endl;
}
else {
specs << "Tiebreak Between " << tiebreakIterations << " Possible Solutions" << endl;
}
specs << endl;

specs << "Optimization Settings" << endl;
specs << "---------------------" << endl << endl;

specs << "Schemes Under Consideration: ";
if (muc == true){
specs << "MUC ";
}
if (meuc == true){
specs << "MEUC ";
}
if (meus == true){
specs << "MEUS ";
}
if (scc == true){
specs << "SCC ";
}
specs << endl;
if (fallbacks == false){
specs << "Do Not ";
}
specs << "Take Available Fallback Options" << endl;
specs << endl;

specs << "Data Configuration and Files" << endl;
specs << "----------------------------" << endl << endl;

specs << "Data Configuration: " << data_configuration << endl;
if (data_configuration.compare("MICHIGAN") == 0 || data_configuration.compare("MATCH RUN") == 0){
specs << "\tData File Name: " << pair_file << endl;
}
else if (data_configuration.compare("COMBINED") == 0){
specs << "\tPair Data File Name: " << pair_file << endl;
specs << "\tCandidate Data File Name: " << candidate_file << endl;
specs << "\tDonor Data File Name: " << donor_file << endl;
}
else if (data_configuration.compare("APD MATCH RUN") == 0){
specs << "\tAPD Information Data File Name: " << info_file << endl;
specs << "\tExtra Information Data File Name: " << exInfo_file << endl;
specs << "\tNon-Directed Donor File Name: " << ndd_file << endl;
specs << "\tSame Patient File Name: " << samePatient_file << endl;
specs << "\tCompatibility Matrix File Name: " << comp_file << endl;
specs << "\tAPD Scoring Matrix File Name: " << weight_file << endl;
}
else { //Default is "Ashlagi", also works for "APD"
specs << "\tCandidate Data File Name: " << candidate_file << endl;
specs << "\tDonor Data File Name: " << donor_file << endl;
}
specs << endl;

specs << "Output Suppression" << endl;
specs << "------------------" << endl << endl;

if (outputEdgeInfo == false){
specs << "Do Not ";
}
specs << "Output Edge Information" << endl;
if (outputExchangeInfo == false){
specs << "Do Not ";
}
specs << "Output Exchange Information" << endl;
if (outputCycleInfo == false){
specs << "Do Not ";
}
specs << "Output List Of Found Cycles" << endl;
if (outputSimInfo == false){
specs << "Do Not ";
}
specs << "Output Log Of Simulation" << endl;
if (outputPopulationStats == false){
specs << "Do Not ";
}
specs << "Include Pool Population Stats" << endl;
specs << endl;

specs << "Additional Flags" << endl;
specs << "----------------" << endl << endl;

if (praAdvantage == false){
specs << "Do Not ";
}
specs << "Add Advantage to High PRA Recipients" << endl;
if (reserveOtoO == false){
specs << "Do Not ";
}
specs << "Reserve O Donors for O Recipients" << endl;
specs << "Pair Failure ";
if (randomPairFailure == true){
specs << "Random" << endl;
}
else {
specs << "Fixed" << endl;
}
specs << "Chains Are Stored ";
if (chainstorage.compare("FIRST") == 0){
specs << "First" << endl;
}
else if (chainstorage.compare("LAST") == 0){
specs << "Last" << endl;
}
else {
specs << "As They Are Found" << endl;
}
if (checkDP == false){
specs << "Do Not ";
}
specs << "Check Additional HLA Information (ie. outside of A,B,BW,CW,DQ,DR)" << endl;
if (includeCompatiblePairs == false){
specs << "Do Not ";
}
specs << "Include Compatible Pairs In Match Runs" << endl;
if (includeABbridgeDonors == false){
specs << "Do Not ";
}
specs << "Include Chains Which End With AB Bridge Donor" << endl;

string specsFile = "output/" + outputFolderName + "/Logfiles/specsLog.txt";
ofstream oFileSpecs(specsFile.c_str());
oFileSpecs << specs.str();
oFileSpecs.close();
}*/


bool KPDGUISimulParam::getParametersSet(){
	return parametersSet;
}

void KPDGUISimulParam::setParametersSet(bool flag){
	parametersSet = flag;
}

string KPDGUISimulParam::getOutputFolderName(){
	return outputFolderName;
}

string KPDGUISimulParam::getAllocationScheme(){
	return allocScheme;
}

string KPDGUISimulParam::getUtilityScheme(){
	return utilityScheme;
}

/*string KPDGUISimulParam::getPairEntryScheme(){
	return pairEntryScheme;
}

string KPDGUISimulParam::getADEntryScheme(){
	return adEntryScheme;
}

string KPDGUISimulParam::getSamplingScheme(){
	return samplingScheme;
}

//int KPDGUISimulParam::getPairSelectionSeed(){
//return pairSelectionSeed;
//}

//int KPDGUISimulParam::getSimulationConditionsSeed(){
//return simulationConditionsSeed;
//}

int KPDGUISimulParam::getSimulations(){
	return simulations;
}

int KPDGUISimulParam::getMonths(){
	return months;
}

double KPDGUISimulParam::getArrivals(){
	return arrivals;
}

double KPDGUISimulParam::getADs(){
	return ads;
}*/

int KPDGUISimulParam::getMaxChainLength(){
	return maxChainLength;
}

/*double KPDGUISimulParam::getAttritionRate(){
	return attritionRate;
}

double KPDGUISimulParam::getRenegeRate(){
	return renegeRate;
}

double KPDGUISimulParam::getPairFailureRate(){
	return pairFailureRate;
}

double KPDGUISimulParam::getProbReturnToPool(){
	return probReturnToPool;
}

double KPDGUISimulParam::getExogenousFailureRate(){
	return exogenousFailureRate;
}*/

int KPDGUISimulParam::getTiebreakIterations(){
	return tiebreakIterations;
}

bool KPDGUISimulParam::getMUC(){
	return muc;
}

bool KPDGUISimulParam::getMEUC(){
	return meuc;
}

bool KPDGUISimulParam::getMEUS(){
	return meus;
}

bool KPDGUISimulParam::getSCC(){
	return scc;
}

//bool KPDGUISimulParam::getFallbacks(){
	//return fallbacks;
//}

string KPDGUISimulParam::getDataConfiguration(){
	return data_configuration;
}

/*string KPDGUISimulParam::getCandidateFile(){
return candidate_file;
}

string KPDGUISimulParam::getDonorFile(){
return donor_file;
}

string KPDGUISimulParam::getPairFile(){
return pair_file;
}

string KPDGUISimulParam::getInfoFile(){
return info_file;
}

string KPDGUISimulParam::getExtraInfoFile(){
return exInfo_file;
}

string KPDGUISimulParam::getNDDFile(){
return ndd_file;
}

string KPDGUISimulParam::getSamePatientFile(){
return samePatient_file;
}

string KPDGUISimulParam::getCompFile(){
return comp_file;
}

string KPDGUISimulParam::getWeightFile(){
return weight_file;
}*/

bool KPDGUISimulParam::getOutputEdgeFlag(){
	return outputEdgeInfo;
}

bool KPDGUISimulParam::getOutputExchangeFlag(){
	return outputExchangeInfo;
}
	
bool KPDGUISimulParam::getOutputCycleFlag(){
	return outputCycleInfo;
}

bool KPDGUISimulParam::getOutputSimFlag(){
	return outputSimInfo;
}

bool KPDGUISimulParam::getOutputPopStatsFlag(){
	return outputPopulationStats;
}

bool KPDGUISimulParam::getPRAadvantage(){
	return praAdvantage;
}

bool KPDGUISimulParam::getReserveOtoO(){
	return reserveOtoO;
}

bool KPDGUISimulParam::getRandomPairFailure(){
	return randomPairFailure;
}

string KPDGUISimulParam::getChainStorage(){
	return chainstorage;
}

bool KPDGUISimulParam::getCheckDP(){
	return checkDP;
}

bool KPDGUISimulParam::getIncludeCompatiblePairsFlag(){
	return includeCompatiblePairs;
}

bool KPDGUISimulParam::getIncludeABbridgeDonorsFlag(){
	return includeABbridgeDonors;
}

QString KPDGUISimulParam::toString(){
	QString parameterString = "";

	parameterString.append("Maximum Chain Length: " + QString::number(maxChainLength) + "\n");
		
	if (utilityScheme == "TRANSPLANTS"){
		parameterString.append("Utility Based On # Of Transplants\n");
	}
	else if (utilityScheme == "SURVIVAL5YEAR"){
		parameterString.append("Utility Based On 5-Year Graft Survival\n");
	}
	else if (utilityScheme == "SURVIVAL10YEAR"){
		parameterString.append("Utility Based On 10-Year Graft Survival\n");
	}
	else {
		parameterString.append("Utility Based On Assigned Score\n");
	}
	
	if (praAdvantage){
		parameterString.append("Add Advantage To High PRA Recipients\n");		
	}
	else {
		parameterString.append("Do Not Add Advantage To High PRA Recipients\n");
	}

	if (reserveOtoO){
		parameterString.append("Reserve O Donors For O Recipients\n");
	}
	else {
		parameterString.append("Do Not Reserve O Donors For O Recipients\n");
	}

	if (checkDP){
		parameterString.append("Check Additional HLA Information (DP)\n");
	}
	else {
		parameterString.append("Do Not Check Additional HLA Information\n");
	}

	if (includeCompatiblePairs){
		parameterString.append("Include Compatible Pairs In Match Runs\n");
	}
	else {
		parameterString.append("Do Not Include Compatible Pairs In Match Runs\n");
	}

	if (includeABbridgeDonors){
		parameterString.append("Allow AB Bridge Donors\n");
	}
	else {
		parameterString.append("Do Not Allow AB Bridge Donors\n");
	}

	if (tiebreakIterations > 1){
		parameterString.append(tiebreakIterations + " Alternate Solutions Will Be Produced\n");
	}

	return parameterString;
}