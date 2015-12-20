/*
 * BlastAlignment.cpp
 *
 *  Created on: Oct 24, 2015
 *      Author: Chao
 */

#include "BlastAlignment.h"

BlastAlignment::BlastAlignment() {
	// TODO Auto-generated ructor stub

}

BlastAlignment::~BlastAlignment() {
	// TODO Auto-generated destructor stub
}

int BlastAlignment::getGaps() {
	return gaps;
}

void BlastAlignment::setGaps(int gaps) {
	this->gaps = gaps;
}

double BlastAlignment::getPositives() {
	return positives;
}

void BlastAlignment::setPositives(double positives) {
	this->positives = positives;
}

double BlastAlignment::getExpect() {
	return expect;
}

void BlastAlignment::setExpect(double expect) {
	this->expect = expect;
}

double BlastAlignment::getIdentities() {
	return identities;
}

void BlastAlignment::setIdentities(double identities) {
	this->identities = identities;
}

double BlastAlignment::getScore() {
	return score;
}

void BlastAlignment::setScore(double score) {
	this->score = score;
}
