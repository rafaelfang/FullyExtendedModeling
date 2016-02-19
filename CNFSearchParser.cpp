/*
 * CNFSearchParser.cpp
 *
 *  Created on: Feb 18, 2016
 *      Author: Chao
 */

#include "CNFSearchParser.h"

CNFSearchParser::CNFSearchParser() {
	// TODO Auto-generated constructor stub

}
CNFSearchParser::CNFSearchParser(string _rootName) {
	// TODO Auto-generated constructor stub
	setRootName(_rootName);
}

void CNFSearchParser::loadSecondaryStructureAndSolventAccessibility(
		std::string SSandSALocation) {
	std::string predictedSecondaryStructure;
	std::string predictedSecondaryStructureConfidence;
	std::string predictedSolventAccessibility;

	std::string ssFile(SSandSALocation);
	ssFile += rootName;
	ssFile += "/QueryInfo/psipred_SS.txt";
	FILE* fptr = fopen((char*) ssFile.c_str(), "r");
	if (fptr == NULL) {
		std::cout << "input file: " << ssFile << " can't open" << std::endl;
	} else {
		int lineLength = 5000;
		char line[lineLength];
		fgets(line, lineLength, fptr); //get target sequence

		fgets(line, lineLength, fptr); //get predicted secondary structure;
		std::string s(line);
		predictedSecondaryStructure = s.erase(
				s.find_last_not_of(" \n\r\t") + 1);

		fgets(line, lineLength, fptr); //get predicted_ss_conf
		std::string ss(line);
		predictedSecondaryStructureConfidence = ss.erase(
				ss.find_last_not_of(" \n\r\t") + 1);

	}
	//std::cout << predictedSecondaryStructure << std::endl;
	//std::cout << predictedSecondaryStructureConfidence << std::endl;

	std::string solventAccessibility;
	std::string saFile(SSandSALocation);
	saFile += rootName;
	saFile += "/QueryInfo/sspro_SA.txt";
	FILE* fptr2 = fopen((char*) saFile.c_str(), "r");
	if (fptr2 == NULL) {
		std::cout << "input file: " << saFile << " can't open" << std::endl;
	} else {
		int lineLength = 5000;
		char line[lineLength];
		fgets(line, lineLength, fptr2); //get target name

		fgets(line, lineLength, fptr2); //get target sequence;

		fgets(line, lineLength, fptr2); //get solvent accessibility
		std::string s(line);
		predictedSolventAccessibility = s.erase(
				s.find_last_not_of(" \n\r\t") + 1);

	}

	//std::cout << predictedSolventAccessibility << std::endl;
	for (int i = 0; i < cnfsearchRecords.size(); i++) {
		cnfsearchRecords[i].setPredictedSsInfo(predictedSecondaryStructure);
		cnfsearchRecords[i].setPredictedSsConf(
				predictedSecondaryStructureConfidence);
		cnfsearchRecords[i].setPredictedSaInfo(predictedSolventAccessibility);

	}
}

void CNFSearchParser::loadAlignmentsInfo(string cnfsearchResultFileLocation,
		string targetLocation, string templateLocation) {
	string cnfsearchResultFile(cnfsearchResultFileLocation);
	cnfsearchResultFile += rootName;
	cnfsearchResultFile += "/query.rank";
	cout << cnfsearchResultFile << endl;
	FILE* fptr = fopen((char*) cnfsearchResultFile.c_str(), "r");
	if (fptr == NULL) {
		cout << "input file: " << cnfsearchResultFile << " can't open" << endl;
	} else {
		int lineLength = 5000;
		char line[lineLength];
		CNFSearchAlignment cnfsearchRecord;
		vector<double> pValueArray;
		vector<double> scoreArray;
		vector<int> alignColsArray;
		char prevState = 'N';
		char currentState = 'N';

		while (fgets(line, lineLength, fptr) != NULL) {

			if (strstr(line, "No   Template    Pvalue") != NULL) {

				while (1) {

					char templateName[5];
					double pValue;
					double score;
					int alignCols;
					fgets(line, lineLength, fptr);
					//cout<<"===="<<line<<endl;
					//cout<<strlen(line)<<endl;
					if (strlen(line) == 1) {
						break;
					}
					sscanf(line, "%*d %s %lf %lf %*s %*s %*d %d %*d %*d %*d",
							templateName, &pValue, &score, &alignCols);
					pValueArray.push_back(pValue);
					scoreArray.push_back(score);
					alignColsArray.push_back(alignCols);
					//cout << templateName << "," << pValue << "," << score << ","
					//		<< alignCols << "," << endl;

				}
				//cout << pValueArray[99] << endl;
			} else if (strstr(line, ">") != NULL) {
				currentState = 'A';
			} else if (strstr(line, "T sse_real") != NULL && prevState == 'A') {
				currentState = 'B';
			} else if ((strstr(line, "T sse_real") != NULL && prevState == 'B')
					|| (strstr(line, "T sse_real") != NULL && prevState == 'C')) {
				currentState = 'C';
			} else {
				continue;
			}
			if ((prevState == 'B' && currentState == 'A')
					|| (prevState == 'C' && currentState == 'A')) {
				cnfsearchRecords.push_back(cnfsearchRecord);
				string emptyString("");
				cnfsearchRecord.setQueryPart(emptyString);
				cnfsearchRecord.setSubjectPart(emptyString);
			}

			if (currentState == 'A') {
				string nameLine(line);
				string hitName = nameLine.substr(1, 5);
				for (int i = 0; i < hitName.size(); i++) {
					if (islower(hitName[i])) {
						hitName[i] = std::toupper(hitName[i]);
					}
				}
				hitName.insert(4, "_");
				//cout << "hitName is " << hitName << endl;
				cnfsearchRecord.setTargetName(rootName);
				cnfsearchRecord.loadTargetInfo(targetLocation);
				cnfsearchRecord.setTemplateName(hitName);
				cnfsearchRecord.loadTemplateInfo(templateLocation);
				//cout<<cnfsearchRecord.getTemplateRealSequenceInfo()<<endl;
			} else if (currentState == 'B') {
				fgets(line, lineLength, fptr);	//skip T sse_real
				fgets(line, lineLength, fptr);	//skip T acc_real
				char subjectPart[200];
				int subjectStart, subjectEnd;
				sscanf(line, "%*s %*s %d %s %d", &subjectStart, subjectPart,
						&subjectEnd);
				//cout << "state B,subject info: " << subjectStart << subjectPart
				//		<< subjectEnd << endl;
				string _subjectPart(subjectPart);
				fgets(line, lineLength, fptr);
				fgets(line, lineLength, fptr); //get query
				char queryPart[200];
				int queryStart, queryEnd;
				sscanf(line, "%*s %*s %d %s %d", &queryStart, queryPart,
						&queryEnd);
				//cout << "state B" << queryStart << queryPart << queryEnd
				//		<< endl;
				string _queryPart(queryPart);

				cnfsearchRecord.setSubjectStart(subjectStart);
				cnfsearchRecord.setSubjectPart(_subjectPart);
				cnfsearchRecord.setSubjectEnd(subjectEnd);

				cnfsearchRecord.setQueryStart(queryStart);
				cnfsearchRecord.setQueryPart(_queryPart);
				cnfsearchRecord.setQueryEnd(queryEnd);

			} else if (currentState == 'C') {
				fgets(line, lineLength, fptr);	//skip T sse_real
				fgets(line, lineLength, fptr);	//skip T acc_real
				char subjectPart[200];
				int subjectStart, subjectEnd;
				sscanf(line, "%*s %*s %d %s %d", &subjectStart, subjectPart,
						&subjectEnd);
				//cout << "stateC subject info: " << subjectStart << subjectPart
				//		<< subjectEnd << endl;
				string _subjectPart(subjectPart);
				string oldSubjectPart = cnfsearchRecord.getSubjectPart();
				oldSubjectPart += _subjectPart;
				cnfsearchRecord.setSubjectPart(oldSubjectPart);
				cnfsearchRecord.setSubjectEnd(subjectEnd);

				fgets(line, lineLength, fptr);
				fgets(line, lineLength, fptr); //get query
				char queryPart[200];
				int queryStart, queryEnd;
				sscanf(line, "%*s %*s %d %s %d", &queryStart, queryPart,
						&queryEnd);
				//cout << "stateC" << queryStart << queryPart << queryEnd << endl;
				string _queryPart(queryPart);
				string oldQueryPart = cnfsearchRecord.getQueryPart();
				oldQueryPart += _queryPart;
				cnfsearchRecord.setQueryPart(oldQueryPart);
				cnfsearchRecord.setQueryEnd(queryEnd);
			}
			prevState = currentState;
		}
		cnfsearchRecords.push_back(cnfsearchRecord);
		for (int i = 0; i < cnfsearchRecords.size(); i++) {
			cnfsearchRecords[i].setValue(pValueArray[i]);
			cnfsearchRecords[i].setScore(scoreArray[i]);
			cnfsearchRecords[i].setAlignedColumns(alignColsArray[i]);
		}
	}
}

void CNFSearchParser::storeTrimmedString(std::string resultPosition) {
	ofstream myfile;
	string outputFile(resultPosition);
	outputFile += rootName;
	outputFile += "_cnf_trimmedString.txt";
	myfile.open((char*) outputFile.c_str());

	for (int i = 0; i < cnfsearchRecords.size(); i++) {
		myfile << cnfsearchRecords[i].getTemplateName() << "\t"
				<< cnfsearchRecords[i].getTrimHit() << endl;

	}
	myfile << endl;
	myfile.close();
}
void CNFSearchParser::storeJsonRecords(string resultPosition) {
	ofstream myfile;
	string outputFile(resultPosition);
	outputFile += rootName;
	outputFile += "_cnfsearch.json";
	myfile.open((char*) outputFile.c_str());

	myfile << "{\"" << rootName << "\":[" << endl;
	for (int i = 0; i < cnfsearchRecords.size(); i++) {
		myfile << "\t{" << endl;
		myfile << "\t\"targetName\":\"" << cnfsearchRecords[i].getTargetName()
				<< "\"," << endl;
		myfile << "\t\"targetFullSequence\":\""
				<< cnfsearchRecords[i].getTargetSequence() << "\"," << endl;
		myfile << "\t\"targetLength\":\""
				<< cnfsearchRecords[i].getTargetLength() << "\"," << endl;
		myfile << "\t\"templateName\":\""
				<< cnfsearchRecords[i].getTemplateName() << "\"," << endl;
		myfile << "\t\"templateReferenceSequenceInfo\":\""
				<< cnfsearchRecords[i].getTemplateReferenceSequenceInfo()
				<< "\"," << endl;
		myfile << "\t\"templateRealSequenceInfo\":\""
				<< cnfsearchRecords[i].getTemplateRealSequenceInfo() << "\","
				<< endl;
		myfile << "\t\"templateTrueSecondaryStructure\":\""
				<< cnfsearchRecords[i].getTemplateTrueSecondaryStructure()
				<< "\"," << endl;
		myfile << "\t\"targetPredictedSecondaryStructure\":\""
				<< cnfsearchRecords[i].getPredictedSsInfo() << "\"," << endl;
		myfile << "\t\"targetPredictedSecondaryStrucutreConfidence\":\""
				<< cnfsearchRecords[i].getPredictedSsConf() << "\"," << endl;
		myfile << "\t\"targetPredictedSolventAccessibility\":\""
				<< cnfsearchRecords[i].getPredictedSaInfo() << "\"," << endl;
		myfile << "\t\"templateSequenceLength\":\""
				<< cnfsearchRecords[i].getTemplateSequenceLength() << "\","
				<< endl;

		myfile << "\t\"pValue\":\"" << cnfsearchRecords[i].getValue() << "\","
				<< endl;

		myfile << "\t\"score\":\"" << cnfsearchRecords[i].getScore() << "\","
				<< endl;
		myfile << "\t\"alignedColumns\":\""
				<< cnfsearchRecords[i].getAlignedColumns() << "\"," << endl;

		myfile << "\t\"trimHit\":\"" << cnfsearchRecords[i].getTrimHit()
				<< "\"," << endl;
		myfile << "\t\"queryStart\":\"" << cnfsearchRecords[i].getQueryStart()
				<< "\"," << endl;
		myfile << "\t\"queryPart\":\"" << cnfsearchRecords[i].getQueryPart()
				<< "\"," << endl;

		myfile << "\t\"queryEnd\":\"" << cnfsearchRecords[i].getQueryEnd()
				<< "\"," << endl;
		myfile << "\t\"subjectStart\":\""
				<< cnfsearchRecords[i].getSubjectStart() << "\"," << endl;

		myfile << "\t\"subjectPart\":\"" << cnfsearchRecords[i].getSubjectPart()
				<< "\"," << endl;

		myfile << "\t\"subjectEnd\":\"" << cnfsearchRecords[i].getSubjectEnd()
				<< "\"}";

		if (i == cnfsearchRecords.size() - 1) {
			myfile << endl;
		} else {
			myfile << "," << endl;
		}
	}
	myfile << "]}" << endl;
	myfile.close();
}
void CNFSearchParser::storeCoordsAndPDB(string experimentLocation) {
	for (int i = 0; i < cnfsearchRecords.size(); i++) {
		cnfsearchRecords[i].fetchFullyExtended3DCoords();
		cnfsearchRecords[i].fetchTrimHit();
		std::string _methodUsed("cnf");
		cnfsearchRecords[i].setMethodUsed(_methodUsed);
		cnfsearchRecords[i].storeInCoordsFormat(experimentLocation, 1, i);
		cnfsearchRecords[i].storeInPDBFormat(experimentLocation, 1, i);
	}
}
CNFSearchParser::~CNFSearchParser() {
// TODO Auto-generated destructor stub
}

