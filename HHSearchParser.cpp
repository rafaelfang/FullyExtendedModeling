/*
 * HHSearchParser.cpp
 *
 *  Created on: Oct 24, 2015
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

void HHSearchParser::storeRecords(string resultPosition) {
	ofstream myfile;
	string outputFile(resultPosition);
	outputFile += rootName;
	outputFile += "_hhsearch.json";
	myfile.open((char*) outputFile.c_str());

	myfile << "{\"" << rootName << "\":[" << endl;
	for (int i = 0; i < hhsearchRecords.size(); i++) {
		myfile << "\t{" << endl;
		myfile << "\t\"hitName\":\"" << hhsearchRecords[i].getTemplateName()
				<< "\"," << endl;
		myfile << "\t\"probab\":\"" << hhsearchRecords[i].getProbab() << "\","
				<< endl;
		myfile << "\t\"expect\":\"" << hhsearchRecords[i].getExpectedValue()
				<< "\"," << endl;
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
		;
		myfile << "\t\"queryEnd\":\"" << hhsearchRecords[i].getQueryEnd()
				<< "\"," << endl;
		myfile << "\t\"subjectStart\":\""
				<< hhsearchRecords[i].getSubjectStart() << "\"," << endl;
		;
		myfile << "\t\"subjectPart\":\"" << hhsearchRecords[i].getSubjectPart()
				<< "\"," << endl;
		;
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

void HHSearchParser::processQueryInsertedResiduesAndSubjectGapsAligned() {
	for (int i = 0; i < hhsearchRecords.size(); i++) {
			string queryPart = hhsearchRecords[i].getQueryPart();

			string subjectPart = hhsearchRecords[i].getSubjectPart();

			string newQueryPart;
			string newSubjectPart;
			for (int j = 0; j < queryPart.size(); j++) {
				if (islower(queryPart[j])) {
					newQueryPart += toupper(queryPart[j]);
				} else {
					newQueryPart += queryPart[j];
				}

			}

			for (int j = 0; j < subjectPart.size(); j++) {

				if (subjectPart[j] == '.') {
					newSubjectPart += '-';
				} else {
					newSubjectPart += subjectPart[j];
				}
			}

			hhsearchRecords[i].setQueryPart(newQueryPart);
			hhsearchRecords[i].setSubjectPart(newSubjectPart);
		/*cout << hhsearchRecords[i].getQueryStart()
				<< hhsearchRecords[i].getQueryPart()
				<< hhsearchRecords[i].getQueryEnd()
				<< hhsearchRecords[i].getSubjectStart()
				<< hhsearchRecords[i].getSubjectPart()
				<< hhsearchRecords[i].getSubjectEnd() << endl;*/
	}
}

void HHSearchParser::storeCoordinates(string experimentLocation,
		string proteinDatabaseLocation) {
	ofstream myfile;
	string outputFile(experimentLocation);
	outputFile += rootName;
	outputFile += "/";
	mkdir(outputFile.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	for (int i = 0; i < hhsearchRecords.size(); i++) {
		ofstream myfile;
		string partFilename(outputFile);
		partFilename += "hhsearch_";
		char buffer[10];
		sprintf(buffer, "%d", i);
		partFilename += buffer;
		partFilename += "_";
		partFilename += hhsearchRecords[i].getTemplateName();
		partFilename += ".txt";
		myfile.open((char*) partFilename.c_str());
		int queryStart = hhsearchRecords[i].getQueryStart();
		int queryEnd = hhsearchRecords[i].getQueryEnd();
		hhsearchRecords[i].loadTemplateInfo(proteinDatabaseLocation);
		int queryPointsArrSize = queryEnd - queryStart + 1;
		Point *queryPoints = (Point*) malloc(
				sizeof(Point) * queryPointsArrSize);
		queryPoints =
				hhsearchRecords[i].fetchSubjectAlignedPart3DPointsForQuery();

		for (int j = 0; j < queryPointsArrSize; j++) {
			myfile << "\t" << queryPoints[j].getX() << ","
					<< queryPoints[j].getY() << "," << queryPoints[j].getZ()
					<< endl;
		}
		free(queryPoints);
		myfile.close();
	}

}

void HHSearchParser::parseFile(string hhsearchResultFileLocation) {
	string hhsearchResultFile(hhsearchResultFileLocation);
	hhsearchResultFile += rootName;
	hhsearchResultFile += "/query.hhr";
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
				hhsearchRecord.setTemplateName(hitName);

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
				hhsearchRecord.setExpectedValue(expect);
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

				char info[14], queryPart[200];
				int queryStart, queryEnd;

				sscanf(line, "%*s %s %d %s %d", info, &queryStart, queryPart,
						&queryEnd);
				string _queryPart(queryPart);

				fgets(line, lineLength, fptr); //skip q consensus
				fgets(line, lineLength, fptr); //skip alignment
				fgets(line, lineLength, fptr); //skip T Consensus
				fgets(line, lineLength, fptr); //get T info

				char info1[6], subjectPart[200];
				int subjectStart, subjectEnd;

				sscanf(line, "%*s %s %d %s %d", info1, &subjectStart,
						subjectPart, &subjectEnd);

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

				char info[14], queryPart[200];
				int queryStart, queryEnd;

				sscanf(line, "%*s %s %d %s %d", info, &queryStart, queryPart,
						&queryEnd);
				string _queryPart(queryPart);
				fgets(line, lineLength, fptr); //skip q consensus
				fgets(line, lineLength, fptr); //skip alignment
				fgets(line, lineLength, fptr); //skip T Consensus
				fgets(line, lineLength, fptr); //get T info

				char info1[6], subjectPart[200];
				int subjectStart, subjectEnd;

				sscanf(line, "%*s %s %d %s %d", info1, &subjectStart,
						subjectPart, &subjectEnd);
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
HHSearchParser::~HHSearchParser() {
// TODO Auto-generated destructor stub
}

