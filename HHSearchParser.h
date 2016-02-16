/*
 * HHSearchParser.h
 *
 *  Created on: Oct 24, 2015
 *      Author: Chao
 */

#ifndef HHSEARCHPARSER_H_
#define HHSEARCHPARSER_H_
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "HHSearchAlignment.h"
#include "Parser.h"

class HHSearchParser: public Parser {
public:
	HHSearchParser();
	HHSearchParser(string);
	virtual ~HHSearchParser();

	void parseFile(string);

	void storeCoordinates(string, string);

	void storeRecords(string);
	void processQueryInsertedResiduesAndSubjectGapsAligned();
private:
	vector<HHSearchAlignment> hhsearchRecords;
};

#endif /* HHSEARCHPARSER_H_ */
