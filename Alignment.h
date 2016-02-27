/*
 * Alignment.h
 *
 *  Created on: Dec 14, 2015
 *      Author: Chao
 */

#ifndef ALIGNMENT_H_
#define ALIGNMENT_H_

#include "Template.h"

class Alignment: public Template {
public:
	Alignment();
	virtual ~Alignment();

	void generateDSSPFiles(std::string,std::string,int id);
	void generateBetaSheetFile(std::string,int id);
	void fetchTrimHit();
	void fetchFullyExtended3DCoords();
	void storeInCoordsFormat(std::string, int flag, int id);
	void storeInPDBFormat(std::string, int flag, int id);
	string shortName2LongName(char name);

	int getFullyExtendedEnd();
	void setFullyExtendedEnd(int fullyExtendedEnd);
	std::string& getFullyExtendedHeadPart();
	void setFullyExtendedHeadPart(std::string& fullyExtendedHeadPart);
	Point*& getFullyExtendedHeadPart3DCoords();
	void setFullyExtendedHeadPart3DCoords(
			Point*& fullyExtendedHeadPart3DCoords);
	int getFullyExtendedStart();
	void setFullyExtendedStart(int fullyExtendedStart);
	std::string& getFullyExtendedTailPart();
	void setFullyExtendedTailPart(std::string& fullyExtendedTailPart);
	Point*& getFullyExtendedTailPart3DCoords();
	void setFullyExtendedTailPart3DCoords(
			Point*& fullyExtendedTailPart3DCoords);
	Point*& getLocalAlignment3DCoords();
	void setLocalAlignment3DCoords(Point*& localAlignment3DCoords);
	int getLocalAlignmentEnd();
	void setLocalAlignmentEnd(int localAlignmentEnd);
	std::string& getLocalAlignmentPart();
	void setLocalAlignmentPart(std::string& localAlignmentPart);
	int getLocalAlignmentStart();
	void setLocalAlignmentStart(int localAlignmentStart);
	int getQueryEnd();
	void setQueryEnd(int queryEnd);
	std::string& getQueryPart();
	void setQueryPart(std::string& queryPart);
	int getQueryStart();
	void setQueryStart(int queryStart);
	int getSubjectEnd();
	void setSubjectEnd(int subjectEnd);
	std::string& getSubjectPart();
	void setSubjectPart(std::string& subjectPart);
	int getSubjectStart();
	void setSubjectStart(int subjectStart);
	std::string& getTrimHit();
	void setTrimHit(std::string& trimHit);
	std::string& getPredictedSaInfo();
	void setPredictedSaInfo(std::string& predictedSaInfo);
	std::string& getPredictedSsConf();
	void setPredictedSsConf(std::string& predictedSsConf);
	std::string& getPredictedSsInfo();
	void setPredictedSsInfo(std::string& predictedSsInfo);

protected:
	int queryStart;
	std::string queryPart;
	int queryEnd;

	int subjectStart;
	std::string subjectPart;
	int subjectEnd;

	int localAlignmentStart;
	std::string localAlignmentPart;
	int localAlignmentEnd;

	int fullyExtendedStart;
	std::string fullyExtendedHeadPart;

	int fullyExtendedEnd;
	std::string fullyExtendedTailPart;

	Point* localAlignment3DCoords;
	Point* fullyExtendedHeadPart3DCoords;
	Point* fullyExtendedTailPart3DCoords;

	std::string trimHit;

	std::string predicted_ss_info;
	std::string predicted_sa_info;
	std::string predicted_ss_conf;

};

#endif /* ALIGNMENT_H_ */
