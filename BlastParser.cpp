/*
 * BlastParser.cpp
 *
 *  Created on: Sep 27, 2015
 *      Author: Chao
 */

#include "BlastParser.h"

BlastParser::BlastParser() {
	// TODO Auto-generated ructor stub

}
BlastParser::BlastParser(string _rootName) {
	// TODO Auto-generated ructor stub
	setRootName(_rootName);
}

void BlastParser::batchGenerateTMScore(std::string experimentLocation,
		std::string TMScoreToolLocation, std::string targetTruePDBLocation) {
	for (int i = 0; i < blastRecords.size(); i++) {
		//blastRecords[i].generateTMScoreFiles(experimentLocation,
		//		TMScoreToolLocation, targetTruePDBLocation, i);
		blastRecords[i].fetchTMScore(experimentLocation, i);
	}
}
void BlastParser::batchGenerateDSSP(std::string experimentLocation,
		std::string templatePDBLocation) {
	for (int i = 0; i < blastRecords.size(); i++) {
		//blastRecords[i].generateDSSPFiles(experimentLocation,
		//		templatePDBLocation, i);
		blastRecords[i].generateBetaSheetFile(experimentLocation, i);
		blastRecords[i].generateACCFileFromDSSP(experimentLocation, i);
	}
}
void BlastParser::loadSecondaryStructureAndSolventAccessibility(
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

	//std::cout<<predictedSolventAccessibility<<std::endl;
	for (int i = 0; i < blastRecords.size(); i++) {
		blastRecords[i].setPredictedSsInfo(predictedSecondaryStructure);
		blastRecords[i].setPredictedSsConf(
				predictedSecondaryStructureConfidence);
		blastRecords[i].setPredictedSaInfo(predictedSolventAccessibility);

	}
}

void BlastParser::loadAlignmentsInfo(string blastResultFileLocation,
		string targetLocation, string templateLocation) {
	//************************************************************************

	//************************************************************************
	//Alignments information
	string blastResultFile(blastResultFileLocation);
	blastResultFile += rootName;
	blastResultFile += "/QueryInfo/query.blaPDB";
	cout << blastResultFile << endl;
	FILE* fptr = fopen((char*) blastResultFile.c_str(), "r");
	if (fptr == NULL) {
		cout << "input file: " << blastResultFile << " can't open" << endl;
	} else {
		int lineLength = 5000;
		char line[lineLength];

		BlastAlignment blastRecord;
		char prevState = 'N';
		char currentState = 'N';
		while (fgets(line, lineLength, fptr) != NULL) {

			//cout << line << endl;

			if (strstr(line, ">") != NULL) {
				currentState = 'A';
			} else if (strstr(line, "Score =") != NULL) {
				currentState = 'B';
			} else if (strstr(line, "Query: ") != NULL && prevState == 'B') {
				currentState = 'C';
			} else if ((strstr(line, "Query: ") != NULL && prevState == 'C')
					|| (strstr(line, "Query: ") != NULL && prevState == 'D')) {
				currentState = 'D';
			} else {
				continue;
			}
			/*cout << "prev: " << prevState << " current: " << currentState
			 << endl;*/
			if ((prevState == 'D' && currentState == 'B')
					|| (prevState == 'C' && currentState == 'B')
					|| (prevState == 'D' && currentState == 'A')
					|| (prevState == 'C' && currentState == 'A')) {

				blastRecords.push_back(blastRecord);
				//blastRecord.displayRecordInfo();
				string emptyString("");
				blastRecord.setQueryPart(emptyString);
				blastRecord.setSubjectPart(emptyString);
			}

			if (currentState == 'A') {
				string nameLine(line);
				string hitName = nameLine.substr(1, 6);
				//cout << "hitName is " << hitName << endl;
				blastRecord.setTargetName(rootName);
				blastRecord.loadTargetInfo(targetLocation);
				blastRecord.setTemplateName(hitName);
				blastRecord.loadTemplateInfo(templateLocation);

			} else if (currentState == 'B') {

				char* pch = strstr(line, "=");
				double score;
				sscanf(pch + 1, "%lf", &score);

				char* pch2 = strstr(pch + 1, "=");
				double expect;
				sscanf(pch2 + 1, "%lf", &expect);

				blastRecord.setScore(score);
				blastRecord.setExpect(expect);
				/*cout << "score: " << score << endl;
				 cout << "expect: " << expect << endl;*/
				fgets(line, lineLength, fptr); //fetch identities line

				char* pch3 = strstr(line, "(");
				double identities;
				sscanf(pch3 + 1, "%lf", &identities);
				blastRecord.setIdentities(identities);

				char* pch4 = strstr(pch3 + 1, "(");
				double positives;
				sscanf(pch4 + 1, "%lf", &positives);
				//cout<<positives<<endl;
				blastRecord.setPositives(positives);

				char* pch5 = strstr(pch4 + 1, "(");
				if (pch5 == NULL) {
					blastRecord.setGaps(0);
				} else {
					int gaps;
					sscanf(pch5 + 1, "%d", &gaps);
					blastRecord.setGaps(gaps);
				}

			} else if (currentState == 'C') {

				char info0[6], queryPart[200];
				int queryStart, queryEnd;

				sscanf(line, "%s %d %s %d", info0, &queryStart, queryPart,
						&queryEnd);
				string _queryPart(queryPart);
				fgets(line, lineLength, fptr); //skip a line
				fgets(line, lineLength, fptr); //fetch subject line info

				char info1[6], subjectPart[200];
				int subjectStart, subjectEnd;

				sscanf(line, "%s %d %s %d", info1, &subjectStart, subjectPart,
						&subjectEnd);
				string _subjectPart(subjectPart);

				blastRecord.setQueryStart(queryStart);
				blastRecord.setQueryPart(_queryPart);
				blastRecord.setQueryEnd(queryEnd);

				blastRecord.setSubjectStart(subjectStart);
				blastRecord.setSubjectPart(_subjectPart);
				blastRecord.setSubjectEnd(subjectEnd);
				/*
				 cout << "query info: " << queryStart << queryPart << queryEnd
				 << endl;
				 cout << "subject info: " << subjectStart << subjectPart
				 << subjectEnd << endl;*/
			} else if (currentState == 'D') {

				char info0[6], queryPart[200];
				int queryStart, queryEnd;

				sscanf(line, "%s %d %s %d", info0, &queryStart, queryPart,
						&queryEnd);
				string _queryPart(queryPart);
				fgets(line, lineLength, fptr); //skip a line
				fgets(line, lineLength, fptr); //fetch subject line info

				char info1[6], subjectPart[200];
				int subjectStart, subjectEnd;

				sscanf(line, "%s %d %s %d", info1, &subjectStart, subjectPart,
						&subjectEnd);
				string _subjectPart(subjectPart);

				string oldQueryPart = blastRecord.getQueryPart();
				oldQueryPart += _queryPart;
				blastRecord.setQueryPart(oldQueryPart);

				blastRecord.setQueryEnd(queryEnd);

				string oldSubjectPart = blastRecord.getSubjectPart();
				oldSubjectPart += _subjectPart;
				blastRecord.setSubjectPart(oldSubjectPart);

				blastRecord.setSubjectEnd(subjectEnd);
				/*
				 cout << "query info: " << blastRecord.getQueryStart()
				 << blastRecord.getQueryPart()
				 << blastRecord.getQueryEnd() << endl;
				 cout << "subject info: " << blastRecord.getSubjectStart()
				 << blastRecord.getSubjectPart()
				 << blastRecord.getSubjectEnd() << endl;*/
			}
			prevState = currentState;

		}
		blastRecords.push_back(blastRecord); //don't forget the last hit
		//blastRecord.displayRecordInfo();

	}
}

void BlastParser::storeTrimmedString(std::string resultPosition) {

	ofstream myfile;
	string outputFile(resultPosition);
	outputFile += rootName;
	outputFile += "_blast_trimmedString.txt";
	myfile.open((char*) outputFile.c_str());

	for (int i = 0; i < blastRecords.size(); i++) {

		myfile << blastRecords[i].getTemplateName() << "\t"
				<< blastRecords[i].getTrimHit() << endl;

	}
	myfile << endl;
	myfile.close();
}
void BlastParser::storeJsonRecords(string resultPosition) {
	ofstream myfile;
	string outputFile(resultPosition);
	outputFile += rootName;
	outputFile += "_blast.json";
	myfile.open((char*) outputFile.c_str());

	myfile << "{\"" << rootName << "\":[" << endl;
	for (int i = 0; i < blastRecords.size(); i++) {
		myfile << "\t{" << endl;
		myfile << "\t\"fileID\":\"" << "blast_"
				<< blastRecords[i].getTargetName() << "_" << i << "_"
				<< blastRecords[i].getTemplateName() << "\"," << endl;
		myfile << "\t\"targetName\":\"" << blastRecords[i].getTargetName()
				<< "\"," << endl;
		myfile << "\t\"targetFullSequence\":\""
				<< blastRecords[i].getTargetSequence() << "\"," << endl;
		myfile << "\t\"targetLength\":\"" << blastRecords[i].getTargetLength()
				<< "\"," << endl;
		myfile << "\t\"templateName\":\"" << blastRecords[i].getTemplateName()
				<< "\"," << endl;
		myfile << "\t\"templateReferenceSequenceInfo\":\""
				<< blastRecords[i].getTemplateReferenceSequenceInfo() << "\","
				<< endl;
		myfile << "\t\"templateRealSequenceInfo\":\""
				<< blastRecords[i].getTemplateRealSequenceInfo() << "\","
				<< endl;
		myfile << "\t\"templateTrueSecondaryStrucutre\":\""
				<< blastRecords[i].getTemplateTrueSecondaryStructure() << "\","
				<< endl;
		myfile << "\t\"targetPredictedSecondaryStrucutre\":\""
				<< blastRecords[i].getPredictedSsInfo() << "\"," << endl;
		myfile << "\t\"targetPredictedSecondaryStructureConfidence\":\""
				<< blastRecords[i].getPredictedSsConf() << "\"," << endl;
		myfile << "\t\"targetPredictedSolventAccessibility\":\""
				<< blastRecords[i].getPredictedSaInfo() << "\"," << endl;
		myfile << "\t\"templateSequenceLength\":\""
				<< blastRecords[i].getTemplateSequenceLength() << "\"," << endl;
		myfile << "\t\"TMscore\":\"" << blastRecords[i].getTmScore() << "\","
				<< endl;
		myfile << "\t\"GDTTS\":\"" << blastRecords[i].getGdttsScore() << "\","
				<< endl;
		myfile << "\t\"score\":\"" << blastRecords[i].getScore() << "\","
				<< endl;
		myfile << "\t\"expect\":\"" << blastRecords[i].getExpect() << "\","
				<< endl;
		myfile << "\t\"identities\":\"" << blastRecords[i].getIdentities()
				<< "%\"," << endl;
		myfile << "\t\"positives\":\"" << blastRecords[i].getPositives()
				<< "%\"," << endl;
		myfile << "\t\"gaps\":\"" << blastRecords[i].getGaps() << "%\","
				<< endl;
		myfile << "\t\"trimString\":\"" << blastRecords[i].getTrimHit() << "\","
				<< endl;
		myfile << "\t\"queryStart\":\"" << blastRecords[i].getQueryStart()
				<< "\"," << endl;
		myfile << "\t\"queryPart\":\"" << blastRecords[i].getQueryPart()
				<< "\"," << endl;
		;
		myfile << "\t\"queryEnd\":\"" << blastRecords[i].getQueryEnd() << "\","
				<< endl;
		myfile << "\t\"subjectStart\":\"" << blastRecords[i].getSubjectStart()
				<< "\"," << endl;
		;
		myfile << "\t\"subjectPart\":\"" << blastRecords[i].getSubjectPart()
				<< "\"," << endl;
		;
		myfile << "\t\"subjectEnd\":\"" << blastRecords[i].getSubjectEnd()
				<< "\"}";

		if (i == blastRecords.size() - 1) {
			myfile << endl;
		} else {
			myfile << "," << endl;
		}
	}
	myfile << "]}" << endl;
	myfile.close();
}

void BlastParser::storeCoordsAndPDB(string experimentLocation) {
	for (int i = 0; i < blastRecords.size(); i++) {
		blastRecords[i].fetchFullyExtended3DCoords();
		blastRecords[i].fetchTrimHit();
		std::string _methodUsed("blast");
		blastRecords[i].setMethodUsed(_methodUsed);
		blastRecords[i].storeInCoordsFormat(experimentLocation, 1, i);
		blastRecords[i].storeInPDBFormat(experimentLocation, 1, i);
	}
}
BlastParser::~BlastParser() {
	// TODO Auto-generated destructor stub
}

