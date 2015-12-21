/*
 * HHSearchAlignment.h
 *
 *  Created on: Nov 14, 2015
 *      Author: Chao
 */

#ifndef HHSEARCHALIGNMENT_H_
#define HHSEARCHALIGNMENT_H_

#include "Alignment.h"

class HHSearchAlignment: public Alignment {
public:
	HHSearchAlignment();
	virtual ~HHSearchAlignment();
	int getAlignedColumns();
	void setAlignedColumns(int alignedColumns);
	double getProbab();
	void setProbab(double probab);
	double getExpect();
	void setExpect(double expect);
	int getIdentities();
	void setIdentities(int identities);
	double getScore();
	void setScore(double score);

private:
	double probab;
	double expect;
	double score;
	int alignedColumns;
	int identities;
};

#endif /* HHSEARCHALIGNMENT_H_ */
