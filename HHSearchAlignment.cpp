/*
 * HHSearchAlignment.cpp
 *
 *  Created on: Nov 14, 2015
 *      Author: Chao
 */

#include "HHSearchAlignment.h"

HHSearchAlignment::HHSearchAlignment() {
	// TODO Auto-generated ructor stub

}

HHSearchAlignment::~HHSearchAlignment() {
	// TODO Auto-generated destructor stub
}

int HHSearchAlignment::getAlignedColumns() {
	return alignedColumns;
}

void HHSearchAlignment::setAlignedColumns(int alignedColumns) {
	this->alignedColumns = alignedColumns;
}

double HHSearchAlignment::getProbab() {
	return probab;
}

void HHSearchAlignment::setProbab(double probab) {
	this->probab = probab;
}

double HHSearchAlignment::getExpect() {
	return expect;
}

void HHSearchAlignment::setExpect(double expect) {
	this->expect = expect;
}

int HHSearchAlignment::getIdentities() {
	return identities;
}

void HHSearchAlignment::setIdentities(int identities) {
	this->identities = identities;
}

double HHSearchAlignment::getScore() {
	return score;
}

void HHSearchAlignment::setScore(double score) {
	this->score = score;
}
