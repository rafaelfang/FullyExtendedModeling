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
#include "CNFSearchParser.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {

	std::string targetLocation("/home/cf797/test/casp11Seq/");
	std::string alignmentResultLocation(
			"/home/spnf2f/dataset/casp11/old_mufold_gen/");
	std::string experimentLocation(
			"/home/cf797/test/casp11_04302014_blastpgp_hhsearch_global_fullyExtended/");
	std::string proteinDatabaseLocation("/home/lihongb/DATABASE/DBInfo/");
	std::string templatePDBLocation("/home/lihongb/DATABASE/PDBALL/");
	std::string secondaryStructureAndSolventAccessibilityLocation(
			"/home/spnf2f/dataset/casp11/old_mufold_gen/");
	std::string cnfResultLocation("/home/cf797/test/casp11Alignment/");
	std::string TMScoreToolLocation("/home/cf797/Tools/");
	std::string targetTruePDBLocation("/home/spnf2f/dataset/casp11/native/");
	if (strcmp(argv[1], "-blast") == 0) {
		BlastParser blastParser(argv[2]);
		blastParser.loadAlignmentsInfo(alignmentResultLocation, targetLocation,
				proteinDatabaseLocation);
		blastParser.loadSecondaryStructureAndSolventAccessibility(
				secondaryStructureAndSolventAccessibilityLocation);
		blastParser.storeCoordsAndPDB(experimentLocation);

		blastParser.storeTrimmedString(experimentLocation);
		blastParser.batchGenerateDSSP(experimentLocation, templatePDBLocation);
		blastParser.batchGenerateTMScore(experimentLocation,
				TMScoreToolLocation, targetTruePDBLocation);
		blastParser.storeJsonRecords(experimentLocation);
	} else if (strcmp(argv[1], "-hhsearch") == 0) {

		HHSearchParser hhsearchParser(argv[2]);
		hhsearchParser.loadAlignmentsInfo(alignmentResultLocation,
				targetLocation, proteinDatabaseLocation);
		hhsearchParser.loadSecondaryStructureAndSolventAccessibility(
				secondaryStructureAndSolventAccessibilityLocation);
		hhsearchParser.storeCoordsAndPDB(experimentLocation);

		hhsearchParser.storeTrimmedString(experimentLocation);
		hhsearchParser.batchGenerateDSSP(experimentLocation,
				templatePDBLocation);
		hhsearchParser.batchGenerateTMScore(experimentLocation,
				TMScoreToolLocation, targetTruePDBLocation);
		hhsearchParser.storeJsonRecords(experimentLocation);

	} else if (strcmp(argv[1], "-cnf") == 0) {
		CNFSearchParser cnfsearchParser(argv[2]);
		cnfsearchParser.loadAlignmentsInfo(cnfResultLocation, targetLocation,
				proteinDatabaseLocation);
		cnfsearchParser.loadSecondaryStructureAndSolventAccessibility(
				secondaryStructureAndSolventAccessibilityLocation);
		cnfsearchParser.storeCoordsAndPDB(experimentLocation);

		cnfsearchParser.storeTrimmedString(experimentLocation);
		cnfsearchParser.batchGenerateDSSP(experimentLocation,
				templatePDBLocation);
		cnfsearchParser.batchGenerateTMScore(experimentLocation,
				TMScoreToolLocation, targetTruePDBLocation);
		cnfsearchParser.storeJsonRecords(experimentLocation);

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
