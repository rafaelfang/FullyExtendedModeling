/*
 * HHSearchParser.cpp
 *
 *  Created on: Nov 14, 2015
 *      Author: Chao
 */

#include "HHSearchParser.h"

HHSearchParser::HHSearchParser() {
	// TODO Auto-generated constructor stub

}
HHSearchParser::HHSearchParser(string _rootName) {
	// TODO Auto-generated constructor stub
	setRootName(_rootName);
}
void HHSearchParser::loadSecondaryStructureAndSolventAccessibility(
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
	for (int i = 0; i < hhsearchRecords.size(); i++) {
		hhsearchRecords[i].setPredictedSsInfo(predictedSecondaryStructure);
		hhsearchRecords[i].setPredictedSsConf(
				predictedSecondaryStructureConfidence);
		hhsearchRecords[i].setPredictedSaInfo(predictedSolventAccessibility);

	}
}

void HHSearchParser::loadAlignmentsInfo(string hhsearchResultFileLocation,
		string targetLocation, string templateLocation) {
	//************************************************************************

	//************************************************************************
	//Alignments information

	string hhsearchResultFile(hhsearchResultFileLocation);
	hhsearchResultFile += rootName;
	hhsearchResultFile += "/QueryInfo/query.hhr";
	cout << hhsearchResultFile << endl;
	FILE* fptr = fopen((char*) hhsearchResultFile.c_str(), "r");
	if (fptr == NULL) {
		cout << "input file: " << hhsearchResultFile << " can't open" << endl;
	} else {
		int lineLength = 5000;
		char line[lineLength];

		HHSearchAlignment hhsearchRecord;
		char prevState = 'N';
		char currentState = 'N';

		while (fgets(line, lineLength, fptr) != NULL) {

			if (strstr(line, ">") != NULL) {
				currentState = 'A';
			} else if (strstr(line, "Probab=") != NULL) {
				currentState = 'B';
			} else if (strstr(line, "Q ") != NULL && prevState == 'B') {
				currentState = 'C';
			} else if ((strstr(line, "Q ") != NULL && prevState == 'C')
					|| (strstr(line, "Q ") != NULL && prevState == 'D')) {
				currentState = 'D';
			} else {
				continue;
			}

			if ((prevState == 'D' && currentState == 'B')
					|| (prevState == 'C' && currentState == 'B')
					|| (prevState == 'D' && currentState == 'A')
					|| (prevState == 'C' && currentState == 'A')) {

				hhsearchRecords.push_back(hhsearchRecord);
				//hhsearchRecord.displayRecordInfo();
				string emptyString("");
				hhsearchRecord.setQueryPart(emptyString);
				hhsearchRecord.setSubjectPart(emptyString);
			}

			if (currentState == 'A') {
				string nameLine(line);
				string hitName = nameLine.substr(1, 6);
				//cout << "hitName is " << hitName << endl;
				hhsearchRecord.setTargetName(rootName);
				hhsearchRecord.loadTargetInfo(targetLocation);
				hhsearchRecord.setTemplateName(hitName);
				//**********load template information here*****************
				hhsearchRecord.loadTemplateInfo(templateLocation);

			} else if (currentState == 'B') {

				char* pch = strstr(line, "=");
				double probab;
				sscanf(pch + 1, "%lf", &probab);

				char* pch2 = strstr(pch + 1, "=");
				double expect;
				sscanf(pch2 + 1, "%lf", &expect);

				char* pch3 = strstr(pch2 + 1, "=");
				double score;
				sscanf(pch3 + 1, "%lf", &score);

				char* pch4 = strstr(pch3 + 1, "=");
				int alignedColumns;
				sscanf(pch4 + 1, "%d", &alignedColumns);

				char* pch5 = strstr(pch4 + 1, "=");
				int identities;
				sscanf(pch5 + 1, "%d", &identities);

				hhsearchRecord.setProbab(probab);
				hhsearchRecord.setExpect(expect);
				hhsearchRecord.setScore(score);
				hhsearchRecord.setAlignedColumns(alignedColumns);
				hhsearchRecord.setIdentities(identities);
				/*
				 cout << "probab: " << probab << endl;
				 cout << "expect: " << expect << endl;
				 cout << "score: " << score << endl;
				 cout << "aligned columns: " << alignedColumns << endl;
				 cout << "identities: " << identities << endl;
				 */
			} else if (currentState == 'C') {

				if (strstr(line, "ss_pred") != NULL) {
					fgets(line, lineLength, fptr);	//skip Q ss_pred
				}
				//cout<<line<<endl;
				char queryPart[200];
				int queryStart, queryEnd;

				sscanf(line, "%*s %*s %d %s %d", &queryStart, queryPart,
						&queryEnd);
				//cout << line << endl;
				string _queryPart(queryPart);
				//cout << "=====" << queryStart << queryPart << queryEnd << endl;
				fgets(line, lineLength, fptr); //skip q consensus
				fgets(line, lineLength, fptr); //skip alignment
				fgets(line, lineLength, fptr); //skip T Consensus
				fgets(line, lineLength, fptr); //get T info

				char subjectPart[200];
				int subjectStart, subjectEnd;

				sscanf(line, "%*s %*s %d %s %d", &subjectStart, subjectPart,
						&subjectEnd);

				string _subjectPart(subjectPart);

				hhsearchRecord.setQueryStart(queryStart);
				hhsearchRecord.setQueryPart(_queryPart);
				hhsearchRecord.setQueryEnd(queryEnd);

				hhsearchRecord.setSubjectStart(subjectStart);
				hhsearchRecord.setSubjectPart(_subjectPart);
				hhsearchRecord.setSubjectEnd(subjectEnd);
				/*
				 cout << "query info: " << queryStart << queryPart << queryEnd
				 << endl;
				 cout << "subject info: " << subjectStart << subjectPart
				 << subjectEnd << endl;
				 */
			} else if (currentState == 'D') {

				if (strstr(line, "ss_pred") != NULL) {
					fgets(line, lineLength, fptr); //skip Q ss_pred
				}

				char queryPart[200];
				int queryStart, queryEnd;

				sscanf(line, "%*s %*s %d %s %d", &queryStart, queryPart,
						&queryEnd);
				string _queryPart(queryPart);
				fgets(line, lineLength, fptr); //skip q consensus
				fgets(line, lineLength, fptr); //skip alignment
				fgets(line, lineLength, fptr); //skip T Consensus
				fgets(line, lineLength, fptr); //get T info

				char subjectPart[200];
				int subjectStart, subjectEnd;

				sscanf(line, "%*s %*s %d %s %d", &subjectStart, subjectPart,
						&subjectEnd);
				string _subjectPart(subjectPart);

				string oldQueryPart = hhsearchRecord.getQueryPart();
				oldQueryPart += _queryPart;
				hhsearchRecord.setQueryPart(oldQueryPart);

				hhsearchRecord.setQueryEnd(queryEnd);

				string oldSubjectPart = hhsearchRecord.getSubjectPart();
				oldSubjectPart += _subjectPart;
				hhsearchRecord.setSubjectPart(oldSubjectPart);

				hhsearchRecord.setSubjectEnd(subjectEnd);
				/*
				 cout << "query info: " << hhsearchRecord.getQueryStart()
				 << hhsearchRecord.getQueryPart()
				 << hhsearchRecord.getQueryEnd() << endl;
				 cout << "subject info: " << hhsearchRecord.getSubjectStart()
				 << hhsearchRecord.getSubjectPart()
				 << hhsearchRecord.getSubjectEnd() << endl;
				 */
			}
			prevState = currentState;
		}
		hhsearchRecords.push_back(hhsearchRecord);
	}

}
void HHSearchParser::storeTrimmedString(std::string resultPosition) {
	ofstream myfile;
	string outputFile(resultPosition);
	outputFile += rootName;
	outputFile += "_hhsearch_trimmedString.txt";
	myfile.open((char*) outputFile.c_str());

	for (int i = 0; i < hhsearchRecords.size(); i++) {
		myfile << hhsearchRecords[i].getTrimHit() << endl;

	}
	myfile << endl;
	myfile.close();
}
void HHSearchParser::storeJsonRecords(string resultPosition) {
	ofstream myfile;
	string outputFile(resultPosition);
	outputFile += rootName;
	outputFile += "_hhsearch.json";
	myfile.open((char*) outputFile.c_str());

	myfile << "{\"" << rootName << "\":[" << endl;
	for (int i = 0; i < hhsearchRecords.size(); i++) {
		myfile << "\t{" << endl;
		myfile << "\t\"targetName\":\"" << hhsearchRecords[i].getTargetName()
				<< "\"," << endl;
		myfile << "\t\"targetFullSequence\":\""
				<< hhsearchRecords[i].getTargetSequence() << "\"," << endl;
		myfile << "\t\"targetLength\":\""
				<< hhsearchRecords[i].getTargetLength() << "\"," << endl;
		myfile << "\t\"templateName\":\""
				<< hhsearchRecords[i].getTemplateName() << "\"," << endl;
		myfile << "\t\"templateReferenceSequenceInfo\":\""
				<< hhsearchRecords[i].getTemplateReferenceSequenceInfo()
				<< "\"," << endl;
		myfile << "\t\"templateRealSequenceInfo\":\""
				<< hhsearchRecords[i].getTemplateRealSequenceInfo() << "\","
				<< endl;
		myfile << "\t\"templateTrueSecondaryStructure\":\""
				<< hhsearchRecords[i].getTemplateTrueSecondaryStructure()
				<< "\"," << endl;
		myfile << "\t\"templatePredictedSecondaryStructure\":\""
				<< hhsearchRecords[i].getPredictedSsInfo() << "\"," << endl;
		myfile << "\t\"templatePredictedSecondaryStrucutreConfidence\":\""
				<< hhsearchRecords[i].getPredictedSsConf() << "\"," << endl;
		myfile << "\t\"templatePredictedSolventAccessibility\":\""
				<< hhsearchRecords[i].getPredictedSaInfo() << "\"," << endl;
		myfile << "\t\"templateSequenceLength\":\""
				<< hhsearchRecords[i].getTemplateSequenceLength() << "\","
				<< endl;

		myfile << "\t\"probab\":\"" << hhsearchRecords[i].getProbab() << "\","
				<< endl;
		myfile << "\t\"expect\":\"" << hhsearchRecords[i].getExpect() << "\","
				<< endl;
		myfile << "\t\"score\":\"" << hhsearchRecords[i].getScore() << "\","
				<< endl;
		myfile << "\t\"Aligned Columns\":\""
				<< hhsearchRecords[i].getAlignedColumns() << "\"," << endl;
		myfile << "\t\"identities\":\"" << hhsearchRecords[i].getIdentities()
				<< "%\"," << endl;
		myfile << "\t\"queryStart\":\"" << hhsearchRecords[i].getQueryStart()
				<< "\"," << endl;
		myfile << "\t\"queryPart\":\"" << hhsearchRecords[i].getQueryPart()
				<< "\"," << endl;

		myfile << "\t\"queryEnd\":\"" << hhsearchRecords[i].getQueryEnd()
				<< "\"," << endl;
		myfile << "\t\"subjectStart\":\""
				<< hhsearchRecords[i].getSubjectStart() << "\"," << endl;

		myfile << "\t\"subjectPart\":\"" << hhsearchRecords[i].getSubjectPart()
				<< "\"," << endl;

		myfile << "\t\"subjectEnd\":\"" << hhsearchRecords[i].getSubjectEnd()
				<< "\"}";

		if (i == hhsearchRecords.size() - 1) {
			myfile << endl;
		} else {
			myfile << "," << endl;
		}
	}
	myfile << "]}" << endl;
	myfile.close();
}
void HHSearchParser::storeCoordsAndPDB(string experimentLocation) {
	for (int i = 0; i < hhsearchRecords.size(); i++) {
		hhsearchRecords[i].fetchFullyExtended3DCoords();
		hhsearchRecords[i].fetchTrimHit();
		std::string _methodUsed("hhsearch");
		hhsearchRecords[i].setMethodUsed(_methodUsed);
		hhsearchRecords[i].storeInCoordsFormat(experimentLocation, 1, i);
		hhsearchRecords[i].storeInPDBFormat(experimentLocation, 1, i);
	}
}
HHSearchParser::~HHSearchParser() {
// TODO Auto-generated destructor stub
}
