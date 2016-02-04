/*
 * Parser.cpp
 *
 *  Created on: Oct 24, 2015
 *      Author: Chao
 */

#include "Parser.h"

Parser::Parser() {
	// TODO Auto-generated ructor stub

}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}



std::string & Parser::getRootName() {
	return rootName;
}

void Parser::setRootName(std::string& rootName) {
	this->rootName = rootName;
}

int Parser::getGlobalFlag() {
	return globalFlag;
}

void Parser::setGlobalFlag(int globalFlag) {
	this->globalFlag = globalFlag;
}
