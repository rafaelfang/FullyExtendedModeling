/*
 * Alignment.cpp
 *
 *  Created on: Dec 14, 2015
 *      Author: Chao
 */

#include "Alignment.h"

Alignment::Alignment() {
	// TODO Auto-generated ructor stub

}
Alignment::~Alignment() {
	// TODO Auto-generated destructor stub
}

void Alignment::fetchTrimHit() {
	//initialize the trimString with '-'
	std::string trimString(targetLength, '-');

	//cout << templateName << endl;
	//cout << "TemplateReference:" << endl;
	//cout << templateReferenceSequenceInfo << endl;
	//cout << "TemplateReal:" << endl;
	//cout << templateRealSequenceInfo << endl;
	std::string missingPointArray;
	for (int i = 0; i < templateSequenceLength; i++) {
		if (templateReferenceSequenceInfo[i] == templateRealSequenceInfo[i]) {
			missingPointArray += 'n';
		} else {
			missingPointArray += 'y';
		}
	}

	//cout << "missingPointArray:" << endl;
	//cout << missingPointArray << endl;
	std::string trimFlag(subjectPart.length(), '*');

	for (int i = 0; i < subjectPart.length() - 1; i++) {
		if (queryPart[i] != '-' && queryPart[i + 1] != '-') {
			trimFlag[i] = 'm'; //current is letter and next is letter, set flag 'm'
		} else if (queryPart[i] != '-' && queryPart[i + 1] == '-') {
			trimFlag[i] = '#'; //current is letter and next is gap, set flag '#'
		} else if (queryPart[i] == '-') {
			trimFlag[i] = 'd'; //current is gap, set flag '-'
		}

	}

	//check last position of query
	if (queryPart[subjectPart.length() - 1] != '-') {
		trimFlag[subjectPart.length() - 1] = 'm';
	} else {
		trimFlag[subjectPart.length() - 1] = 'd';
	}
	//cout<<"queryPart"<<endl;
	//cout<<queryPart<<endl;
	//cout<<"subjectPart"<<endl;
	//cout<<subjectPart<<endl;
	//cout<<"trimFlag"<<endl;
	//cout<<trimFlag<<endl;

	//get rid of the 'd' part from query and subject
	std::string tempTrim;

	for (int i = 0; i < trimFlag.length(); i++) {
		if (trimFlag[i] == 'm'
				&& missingPointArray[i + subjectStart - 1] == 'n') {
			tempTrim += subjectPart[i];
		} else if (trimFlag[i] == 'm'
				&& missingPointArray[i + subjectStart - 1] == 'y') {
			tempTrim += '+';
		} else if (trimFlag[i] == '#') {

			tempTrim += '#';
		} else if (queryPart[i] != '-' && subjectPart[i] == '-') {
			tempTrim += '-';
		}
	}
	for (int i = 0; i < tempTrim.length(); i++) {
		trimString[i + queryStart - 1] = tempTrim[i];
	}

	//cout << trimFlag << endl;
	//cout<<"trimString"<<endl;
	//cout << trimString << endl;
	setTrimHit(trimString);
}

void Alignment::fetchFullyExtended3DCoords() {

	int queryGaps = 0;
	char flag[queryPart.size()];
	for (int i = 0; i < queryPart.size(); i++) {
		if (queryPart[i] != '-' && subjectPart[i] != '-') {
			flag[i] = 'm';
		} else if (queryPart[i] != '-' && subjectPart[i] == '-') {
			flag[i] = '$';
		} else if (queryPart[i] == '-' && subjectPart[i] != '-') {
			flag[i] = '!';
			queryGaps += 1;
		}
	}

	//get the 3d coordinates for subject
	Point subjectBigNumber(10000, 10000, 10000);
	Point* subject3DCoords = (Point*) malloc(
			sizeof(Point) * (subjectPart.size()));
	int gapShift = 0;
	for (int i = 0; i < subjectPart.size(); i++) {
		if (flag[i] == '$') {
			subject3DCoords[i] = subjectBigNumber;
			gapShift++;
		} else {
			subject3DCoords[i] = templateCarbonAlphaCoords[subjectStart + i - 1
					- gapShift];
		}

	}
	//debugging
	/*
	 std::cout << "subject3DCoords" << std::endl;
	 for (int i = 0; i < subjectPart.size(); i++) {
	 std::cout << subject3DCoords[i].getX() << ","
	 << subject3DCoords[i].getY() << "," << subject3DCoords[i].getZ()
	 << std::endl;
	 }
	 std::cout << "subject3DCoords end" << std::endl;
	 */
	//debugging
	//local alignment 3D coordinates
	localAlignment3DCoords = (Point*) malloc(
			sizeof(Point) * (queryPart.size() - queryGaps));
	int index = 0;
	for (int i = 0; i < queryPart.size(); i++) {
		if (flag[i] == '!') {
			continue;
		} else {
			localAlignment3DCoords[index] = subject3DCoords[i];
			index++;
		}
	}

	//debugging
	/*
	 std::cout << "localAlignment3DCoords" << std::endl;
	 for (int i = 0; i < queryPart.size() - queryGaps; i++) {
	 if (i % 10 == 0) {
	 std::cout << std::endl;
	 }
	 std::cout << localAlignment3DCoords[i].getX() << "\t";
	 }
	 for (int i = 0; i < queryPart.size() - queryGaps; i++) {
	 if (i % 10 == 0) {
	 std::cout << std::endl;
	 }
	 std::cout << localAlignment3DCoords[i].getY() << "\t";
	 }
	 for (int i = 0; i < queryPart.size() - queryGaps; i++) {
	 if (i % 10 == 0) {
	 std::cout << std::endl;
	 }
	 std::cout << localAlignment3DCoords[i].getZ() << "\t";
	 }
	 std::cout << "localAlignment3DCoords end" << std::endl;
	 */
	//debugging
	//local alignment start, part, end
	localAlignmentStart = queryStart;
	localAlignmentEnd = queryEnd;
	for (int i = 0; i < queryPart.size(); i++) {
		if (flag[i] == '!') {
			continue;
		} else {
			localAlignmentPart += queryPart[i];
		}

	}

	//std::cout << "local alignment start: " << localAlignmentStart << std::endl;
	//std::cout << "local alignment end: " << localAlignmentEnd << std::endl;
	//std::cout << "local alignment part: " << localAlignmentPart << std::endl;
	//debug
	/*
	 Point* result = localAlignment3DCoords;
	 int localAlignment3DCoordsSize = localAlignmentEnd - localAlignmentStart
	 + 1;

	 for (int i = 0; i < localAlignment3DCoordsSize; i++) {
	 if (i % 10 == 0) {
	 std::cout << std::endl;
	 }
	 std::cout << result[i].getX() << "\t";
	 }
	 std::cout << std::endl;
	 */
	//debug
	//**********************************************************
	//fully extended part
	int numberOfHeadToBeExtended = 0;
	if (queryStart - 1 < subjectStart - 1) {
		numberOfHeadToBeExtended = queryStart - 1;
	} else {
		numberOfHeadToBeExtended = subjectStart - 1;
	}

	//std::cout << "number of head extended: " << numberOfHeadToBeExtended
	//		<< std::endl;

	fullyExtendedStart = localAlignmentStart - numberOfHeadToBeExtended;
	fullyExtendedHeadPart3DCoords = (Point*) malloc(
			sizeof(Point) * numberOfHeadToBeExtended);
	for (int i = 0; i < numberOfHeadToBeExtended; i++) {
		fullyExtendedHeadPart3DCoords[i] =
				templateCarbonAlphaCoords[fullyExtendedStart + i - 1];
		fullyExtendedHeadPart += targetSequence[fullyExtendedStart + i - 1];
	}

	//debug
	/*
	 std::cout << "fully extended head part:" << fullyExtendedHeadPart
	 << std::endl;
	 std::cout << "fullyExtendedHeadPart" << std::endl;
	 for (int i = 0; i < numberOfHeadToBeExtended; i++) {
	 std::cout << fullyExtendedHeadPart3DCoords[i].getX() << ","
	 << fullyExtendedHeadPart3DCoords[i].getY() << ","
	 << fullyExtendedHeadPart3DCoords[i].getZ() << std::endl;
	 }
	 std::cout << "fullyExtendedHeadPart finish" << std::endl;
	 */
	//debug
	int numberOfTailToBeExtended = 0;
	if (targetLength - queryEnd > templateSequenceLength - subjectEnd) {
		numberOfTailToBeExtended = templateSequenceLength - subjectEnd;
	} else {
		numberOfTailToBeExtended = targetLength - queryEnd;
	}

	//std::cout << "number of tail extended: " << numberOfTailToBeExtended
	//		<< std::endl;

	fullyExtendedEnd = localAlignmentEnd + numberOfTailToBeExtended;
	fullyExtendedTailPart3DCoords = (Point*) malloc(
			sizeof(Point) * numberOfTailToBeExtended);

	for (int i = 0; i < numberOfTailToBeExtended; i++) {
		fullyExtendedTailPart3DCoords[i] = templateCarbonAlphaCoords[subjectEnd
				+ i];
		fullyExtendedTailPart += targetSequence[localAlignmentEnd + i];
	}

	//debug
	/*
	 std::cout << "fully extended tail part:" << fullyExtendedTailPart
	 << std::endl;
	 std::cout << "fullyExtendedTailPart" << std::endl;
	 for (int i = 0; i < numberOfTailToBeExtended; i++) {
	 if (i % 10 == 0) {
	 std::cout << std::endl;
	 }
	 std::cout << fullyExtendedTailPart3DCoords[i].getX() << "\t";
	 }
	 std::cout << std::endl;
	 std::cout << "fullyExtendedTailPart finish" << std::endl;
	 */
	//debug
}

void Alignment::storeInCoordsFormat(std::string experimentLocation, int flag,
		int id) {
	std::ofstream myfile;
	std::string outputFile(experimentLocation);
	outputFile += targetName;
	outputFile += "/";
	mkdir(outputFile.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	outputFile += methodUsed;
	outputFile += "_";
	outputFile += targetName;
	outputFile += "_";
	char buffer[10];
	sprintf(buffer, "%d", id);
	outputFile += buffer;
	outputFile += "_";
	outputFile += templateName;
	outputFile += ".coords";
	myfile.open((char*) outputFile.c_str());
	//myfile << "head Part" << "\n";
	if (flag == 1) {	//add head part
		for (int i = 0; i < fullyExtendedHeadPart.size(); i++) {
			myfile << fullyExtendedHeadPart3DCoords[i].getX() << ","
					<< fullyExtendedHeadPart3DCoords[i].getY() << ","
					<< fullyExtendedHeadPart3DCoords[i].getZ() << "\n";
		}
	}
	//myfile << "middle Part" << "\n";
	//local Alignment Part
	for (int i = 0; i < localAlignmentPart.size(); i++) {
		myfile << localAlignment3DCoords[i].getX() << ","
				<< localAlignment3DCoords[i].getY() << ","
				<< localAlignment3DCoords[i].getZ() << "\n";
	}
	//myfile << "tail Part" << "\n";
	if (flag == 1) {	//add tail part
		for (int i = 0; i < fullyExtendedTailPart.size(); i++) {
			myfile << fullyExtendedTailPart3DCoords[i].getX() << ","
					<< fullyExtendedTailPart3DCoords[i].getY() << ","
					<< fullyExtendedTailPart3DCoords[i].getZ() << "\n";
		}
	}
	myfile.close();
}

void Alignment::storeInPDBFormat(std::string experimentLocation, int flag,
		int id) {
	std::ofstream myfile;
	std::string outputFile(experimentLocation);
	outputFile += targetName;
	outputFile += "/";
	mkdir(outputFile.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	outputFile += methodUsed;
	outputFile += "_";
	outputFile += targetName;
	outputFile += "_";
	char buffer[10];
	sprintf(buffer, "%d", id);
	outputFile += buffer;
	outputFile += "_";
	outputFile += templateName;
	outputFile += ".pdb";
	FILE *pFile = fopen((char*) outputFile.c_str(), "w");
	//fprintf(pFile, "head part:\n");
	if (flag == 1) {	//add head part
		for (int i = 0; i < fullyExtendedHeadPart.size(); i++) {
			string aminoAcid(shortName2LongName(fullyExtendedHeadPart[i]));
			fprintf(pFile, "ATOM  %5d  CA  %3s  %4d    %8.3f%8.3f%8.3f\n",
					fullyExtendedStart + i, (char*) aminoAcid.c_str(),
					fullyExtendedStart + i,
					fullyExtendedHeadPart3DCoords[i].getX(),
					fullyExtendedHeadPart3DCoords[i].getY(),
					fullyExtendedHeadPart3DCoords[i].getZ());

		}
	}
	//fprintf(pFile, "middle part\n");
	//local Alignment Part
	for (int i = 0; i < localAlignmentPart.size(); i++) {
		string aminoAcid(shortName2LongName(localAlignmentPart[i]));
		fprintf(pFile, "ATOM  %5d  CA  %3s  %4d    %8.3f%8.3f%8.3f\n",
				localAlignmentStart + i, (char*) aminoAcid.c_str(),
				localAlignmentStart + i, localAlignment3DCoords[i].getX(),
				localAlignment3DCoords[i].getY(),
				localAlignment3DCoords[i].getZ());
	}
	//fprintf(pFile, "tail part\n");
	if (flag == 1) {	//add tail part
		for (int i = 0; i < fullyExtendedTailPart.size(); i++) {
			string aminoAcid(shortName2LongName(fullyExtendedTailPart[i]));
			fprintf(pFile, "ATOM  %5d  CA  %3s  %4d    %8.3f%8.3f%8.3f\n",
					localAlignmentEnd + i + 1, (char*) aminoAcid.c_str(),
					localAlignmentEnd + i + 1,
					fullyExtendedTailPart3DCoords[i].getX(),
					fullyExtendedTailPart3DCoords[i].getY(),
					fullyExtendedTailPart3DCoords[i].getZ());
		}
	}
	fprintf(pFile, "TER\n");
	fprintf(pFile, "END\n");
	fclose(pFile);
}

string Alignment::shortName2LongName(char name) {
	if (name == 'A') {
		return "ALA";
	} else if (name == 'R') {
		return "ARG";
	} else if (name == 'N') {
		return "ASN";
	} else if (name == 'D') {
		return "ASP";
	} else if (name == 'C') {
		return "CYS";
	} else if (name == 'Q') {
		return "GLN";
	} else if (name == 'E') {
		return "GLU";
	} else if (name == 'G') {
		return "GLY";
	} else if (name == 'H') {
		return "HIS";
	} else if (name == 'I') {
		return "ILE";
	} else if (name == 'L') {
		return "LEU";
	} else if (name == 'K') {
		return "LYS";
	} else if (name == 'M') {
		return "MET";
	} else if (name == 'F') {
		return "PHE";
	} else if (name == 'P') {
		return "PRO";
	} else if (name == 'S') {
		return "SER";
	} else if (name == 'T') {
		return "THR";
	} else if (name == 'W') {
		return "TRP";
	} else if (name == 'Y') {
		return "TYR";
	} else if (name == 'V') {
		return "VAL";
	} else if (name == 'B') {
		return "ASX";
	} else if (name == 'Z') {
		return "GLX";
	}
}

int Alignment::getFullyExtendedEnd() {
	return fullyExtendedEnd;
}

void Alignment::setFullyExtendedEnd(int fullyExtendedEnd) {
	this->fullyExtendedEnd = fullyExtendedEnd;
}

std::string& Alignment::getFullyExtendedHeadPart() {
	return fullyExtendedHeadPart;
}

void Alignment::setFullyExtendedHeadPart(std::string& fullyExtendedHeadPart) {
	this->fullyExtendedHeadPart = fullyExtendedHeadPart;
}

Point*& Alignment::getFullyExtendedHeadPart3DCoords() {
	return fullyExtendedHeadPart3DCoords;
}

void Alignment::setFullyExtendedHeadPart3DCoords(
		Point*& fullyExtendedHeadPart3DCoords) {
	this->fullyExtendedHeadPart3DCoords = fullyExtendedHeadPart3DCoords;
}

int Alignment::getFullyExtendedStart() {
	return fullyExtendedStart;
}

void Alignment::setFullyExtendedStart(int fullyExtendedStart) {
	this->fullyExtendedStart = fullyExtendedStart;
}

std::string& Alignment::getFullyExtendedTailPart() {
	return fullyExtendedTailPart;
}

void Alignment::setFullyExtendedTailPart(std::string& fullyExtendedTailPart) {
	this->fullyExtendedTailPart = fullyExtendedTailPart;
}

Point*& Alignment::getFullyExtendedTailPart3DCoords() {
	return fullyExtendedTailPart3DCoords;
}

void Alignment::setFullyExtendedTailPart3DCoords(
		Point*& fullyExtendedTailPart3DCoords) {
	this->fullyExtendedTailPart3DCoords = fullyExtendedTailPart3DCoords;
}

Point*& Alignment::getLocalAlignment3DCoords() {
	return localAlignment3DCoords;
}

void Alignment::setLocalAlignment3DCoords(Point*& localAlignment3DCoords) {
	this->localAlignment3DCoords = localAlignment3DCoords;
}

int Alignment::getLocalAlignmentEnd() {
	return localAlignmentEnd;
}

void Alignment::setLocalAlignmentEnd(int localAlignmentEnd) {
	this->localAlignmentEnd = localAlignmentEnd;
}

std::string& Alignment::getLocalAlignmentPart() {
	return localAlignmentPart;
}

void Alignment::setLocalAlignmentPart(std::string& localAlignmentPart) {
	this->localAlignmentPart = localAlignmentPart;
}

int Alignment::getLocalAlignmentStart() {
	return localAlignmentStart;
}

void Alignment::setLocalAlignmentStart(int localAlignmentStart) {
	this->localAlignmentStart = localAlignmentStart;
}

int Alignment::getQueryEnd() {
	return queryEnd;
}

void Alignment::setQueryEnd(int queryEnd) {
	this->queryEnd = queryEnd;
}

std::string& Alignment::getQueryPart() {
	return queryPart;
}

void Alignment::setQueryPart(std::string& queryPart) {
	this->queryPart = queryPart;
}

int Alignment::getQueryStart() {
	return queryStart;
}

void Alignment::setQueryStart(int queryStart) {
	this->queryStart = queryStart;
}

int Alignment::getSubjectEnd() {
	return subjectEnd;
}

void Alignment::setSubjectEnd(int subjectEnd) {
	this->subjectEnd = subjectEnd;
}

std::string& Alignment::getSubjectPart() {
	return subjectPart;
}

void Alignment::setSubjectPart(std::string& subjectPart) {
	this->subjectPart = subjectPart;
}

int Alignment::getSubjectStart() {
	return subjectStart;
}

void Alignment::setSubjectStart(int subjectStart) {
	this->subjectStart = subjectStart;
}

std::string& Alignment::getTrimHit() {
	return trimHit;
}

void Alignment::setTrimHit(std::string& trimHit) {
	this->trimHit = trimHit;
}

std::string& Alignment::getPredictedSaInfo() {
	return predicted_sa_info;
}

void Alignment::setPredictedSaInfo(std::string& predictedSaInfo) {
	predicted_sa_info = predictedSaInfo;
}

std::string& Alignment::getPredictedSsConf() {
	return predicted_ss_conf;
}

void Alignment::setPredictedSsConf(std::string& predictedSsConf) {
	predicted_ss_conf = predictedSsConf;
}

std::string& Alignment::getPredictedSsInfo() {
	return predicted_ss_info;
}

void Alignment::setPredictedSsInfo(std::string& predictedSsInfo) {
	predicted_ss_info = predictedSsInfo;
}
