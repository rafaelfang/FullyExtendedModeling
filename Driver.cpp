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

#include <stdlib.h>

int main(int argc, char* argv[]) {

	std::string targetLocation("/home/cf797/test/casp10Seq/");
	std::string alignmentResultLocation(
			"/home/cf797/test/casp10_01092013_blastpgp_hhsearch_glob/");
	std::string experimentLocation(
			"/home/cf797/test/FullyExtendedModeling/");
	std::string proteinDatabaseLocation("/home/lihongb/DATABASE/DBInfo/");

	Alignment alignment;

	//load target information
	std::string _targetName("T0681");
	alignment.setTargetName(_targetName);
	alignment.loadTargetInfo(targetLocation);

	//load template information
	std::string _templateName("3HN5_A");
	alignment.setTemplateName(_templateName);
	alignment.loadTemplateInfo(proteinDatabaseLocation);

	//print out alignment basic information

	//std::cout << "alignment basic information:" << std::endl;
	//std::cout << alignment.getTargetName() << std::endl;
	//std::cout << "target length: "<<alignment.getTargetLength() << std::endl;
	//std::cout << alignment.getTargetSequence() << std::endl;
	//std::cout << alignment.getTemplateName() << std::endl;
	// std::cout << alignment.getTemplateSequenceInfo() << std::endl;
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
	alignment.setQueryStart(20);
	std::string _queryPart(
			"CSYDNFEEPKATLTGRAIYDGEAVGVRS-GSSEFALFQDGYALHGSIPVYVAQDGSYSVSLFNGDYKLV-RMGNAPWERPSNDTIYITVKGNTVQDIPVTPYFSVRNVSFARNGNKVTARFTINKVVADANLENVGIYLGTGILTDEKQKE----------AE-LALGNTVSLNQENTAEIEIPSGLLNESYLYARVGVKSDKSSEYCYSQSIKVA");
	alignment.setQueryPart(_queryPart);
	alignment.setQueryEnd(222);

	alignment.setSubjectStart(1);
	std::string _subjectPart(
			"GMKDNYDAPESMLTGRVMYNGEALQLRGNEAVQLQLYQHGYAKHDPINVYVNQDGMYSANLFDGEYQMITKSGNGPWTSEGRDTINVTVAGNTVQDVEVTPYYLVRDAQMTLEGNKVNASFKVEKVA-GGGIDRVFFMLSTTQFVNDAEHNVDRYDETDNLDAYDETGKLYTFATRDYTDNSMFQTALKRGTLFGRICIWPKGSDQGIYSKVIRLK");
	alignment.setSubjectPart(_subjectPart);
	alignment.setSubjectEnd(215);

	alignment.fetchFullyExtended3DCoords();
	std::string _methodUsed("hhsearch");
	alignment.setMethodUsed(_methodUsed);
	alignment.storeInCoordsFormat(experimentLocation,1,1);
	alignment.storeInPDBFormat(experimentLocation,1,1);
	return 0;
}
