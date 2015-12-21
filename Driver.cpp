//============================================================================
// Name        : AlignmentOOD.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "Point.h"
#include "Alignment.h"
#include "BlastParser.h"
#include "HHSearchParser.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {

	std::string targetLocation("/home/cf797/test/casp10Seq/");
	std::string alignmentResultLocation(
			"/home/cf797/test/casp10_01092013_blastpgp_hhsearch_glob/");
	std::string experimentLocation("/home/cf797/test/FullyExtendedModeling/");
	std::string proteinDatabaseLocation("/home/lihongb/DATABASE/DBInfo/");
	if (strcmp(argv[1], "-blast") == 0) {
		BlastParser blastParser(argv[2]);
		blastParser.loadAlignmentsInfo(alignmentResultLocation, targetLocation,
				proteinDatabaseLocation);
		blastParser.storeJsonRecords(experimentLocation);
		blastParser.storeCoordsAndPDB(experimentLocation);
	} else if (strcmp(argv[1], "-hhsearch") == 0) {

		HHSearchParser hhsearchParser(argv[2]);
		hhsearchParser.loadAlignmentsInfo(alignmentResultLocation,
				targetLocation, proteinDatabaseLocation);
		hhsearchParser.storeJsonRecords(experimentLocation);
		hhsearchParser.storeCoordsAndPDB(experimentLocation);
	}

	/*
	 Alignment alignment;

	 //load target information
	 std::string _targetName("T0681");
	 alignment.setTargetName(_targetName);
	 alignment.loadTargetInfo(targetLocation);

	 //load template information
	 std::string _templateName("4EIU_A");
	 alignment.setTemplateName(_templateName);
	 alignment.loadTemplateInfo(proteinDatabaseLocation);
	 */
	//print out alignment basic information
	//std::cout << "alignment basic information:" << std::endl;
	//std::cout << alignment.getTargetName() << std::endl;
	//std::cout << "target length: "<<alignment.getTargetLength() << std::endl;
	//std::cout << alignment.getTargetSequence() << std::endl;
	//std::cout << alignment.getTemplateName() << std::endl;
	//std::cout << alignment.getTemplateSequenceInfo() << std::endl;
	//std::cout << "template length: "<<alignment.getTemplateSequenceLength() << std::endl;
	/*
	 Point* templateCarbonAlphaCoords = alignment.getTemplateCarbonAlphaCoords();
	 for (int i = 0; i < alignment.getTemplateSequenceLength(); i++) {
	 std::cout << templateCarbonAlphaCoords[i].getX() << ","
	 << templateCarbonAlphaCoords[i].getY() << ","
	 << templateCarbonAlphaCoords[i].getZ() << std::endl;
	 }
	 std::cout << "alignment basic information end" << std::endl;
	 */
	/*
	 alignment.setQueryStart(21);
	 std::string _queryPart("SYDNFEEPKATLTGKAIY--DGEAVGVRSG--SSEFALFQDGYAL--KGSIPVYIAQDGSY-SVSLFNGDYKLVRMGNA-PWERPSND-------TIYITVRGNTVQDIPVTPYFFV-RNVSFAKNGNKITARFTINKVVANA-----------------NMENVGIYLGTGILTDEKQKEAELKLGNTVSLD-----QENTAEIEIPSGLVNESYLYARVGVKSD-------KSSEYCYSQSIKV");
	 alignment.setQueryPart(_queryPart);
	 alignment.setQueryEnd(221);

	 alignment.setSubjectStart(1);
	 std::string _subjectPart("GIDNYEEPSETIWGEVVDEATGKRVLTDQGSEGIRVRLTELSWGDNVQHNPDFYCMMDGTFQNTKIFKGEYNVRIDGPFIPLVRENTDGTLLHDGSVNTEISGTTKVKFEVQPFLNVEFVGNPQVSNGVIKAQVRVTRGVSDEVFREKIQPMGNWKDEYLNVTDIQFFVSYSNTVGYRARDERWSSSINYEGKSFEGLLGKEVTIQSNGNVPSGRKVFVRAAARINYDTPVGSGTRRWNYSEPMEV");
	 alignment.setSubjectPart(_subjectPart);
	 alignment.setSubjectEnd(246);

	 alignment.fetchFullyExtended3DCoords();
	 std::string _methodUsed("blast");
	 alignment.setMethodUsed(_methodUsed);
	 alignment.storeInCoordsFormat(experimentLocation,1,1);
	 alignment.storeInPDBFormat(experimentLocation,1,1);
	 */
	return 0;
}
