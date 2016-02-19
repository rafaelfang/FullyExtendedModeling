/*
 * CNFSearchAlignment.cpp
 *
 *  Created on: Feb 18, 2016
 *      Author: Chao
 */

#include "CNFSearchAlignment.h"

CNFSearchAlignment::CNFSearchAlignment() {
	// TODO Auto-generated ructor stub

}

CNFSearchAlignment::~CNFSearchAlignment() {
	// TODO Auto-generated destructor stub
}

int CNFSearchAlignment::getAlignedColumns() {
	return alignedColumns;
}

void CNFSearchAlignment::setAlignedColumns(int alignedColumns) {
	this->alignedColumns = alignedColumns;
}

double CNFSearchAlignment::getValue() {
	return pValue;
}

void CNFSearchAlignment::setValue(double value) {
	pValue = value;
}

double CNFSearchAlignment::getScore() {
	return score;
}

void CNFSearchAlignment::setScore(double score) {
	this->score = score;
}
