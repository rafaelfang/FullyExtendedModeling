/*
 * Parser.h
 *
 *  Created on: Oct 24, 2015
 *      Author: Chao
 */

#ifndef PARSER_H_
#define PARSER_H_
#include <string>

class Parser {
public:
	Parser();

	virtual ~Parser();

	virtual void loadSecondaryStructureAndSolventAccessibility(std::string)=0;
	virtual void loadAlignmentsInfo(std::string, std::string, std::string)=0;
	virtual void storeJsonRecords(std::string)=0;
	virtual void storeCoordsAndPDB(std::string)=0;
	virtual void storeTrimmedString(std::string)=0;

	std::string& getRootName();
	void setRootName(std::string& rootName);
	int getGlobalFlag();
	void setGlobalFlag(int globalFlag);


protected:
	std::string rootName;
	int globalFlag;
};

#endif /* PARSER_H_ */
