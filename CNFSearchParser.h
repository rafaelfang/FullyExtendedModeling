/*
 * CNFSearchParser.h
 *
 *  Created on: Feb 18, 2016
 *      Author: Chao
 */

#ifndef CNFSEARCHPARSER_H_
#define CNFSEARCHPARSER_H_
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "CNFSearchAlignment.h"
#include "Parser.h"

class CNFSearchParser: public Parser {
public:
	CNFSearchParser();
	CNFSearchParser(string);
	virtual ~CNFSearchParser();
	void loadSecondaryStructureAndSolventAccessibility(std::string);
	void loadAlignmentsInfo(string, string, string);
	void storeJsonRecords(string);
	void storeCoordsAndPDB(string);
	void storeTrimmedString(std::string);
private:
	vector<CNFSearchAlignment> cnfsearchRecords;
};

#endif /* CNFSEARCHPARSER_H_ */
