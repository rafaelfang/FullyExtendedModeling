/*
 * CNFSearchAlignment.h
 *
 *  Created on: Feb 18, 2016
 *      Author: Chao
 */

#ifndef CNFSEARCHALIGNMENT_H_
#define CNFSEARCHALIGNMENT_H_

#include "Alignment.h"

class CNFSearchAlignment: public Alignment {
public:
	CNFSearchAlignment();
	virtual ~CNFSearchAlignment();
	int getAlignedColumns();
	void setAlignedColumns(int alignedColumns);
	double getValue();
	void setValue(double value);
	double getScore();
	void setScore(double score);

private:
	double pValue;
	double score;
	int alignedColumns;

};

#endif /* CNFSEARCHALIGNMENT_H_ */
