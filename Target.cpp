/*
 * Target.cpp
 *
 *  Created on: Dec 14, 2015
 *      Author: Chao
 */

#include "Target.h"



Target::Target() {
	// TODO Auto-generated ructor stub

}
Target::Target(std::string _targetName) {
	targetName = _targetName;
}
Target::~Target() {
	// TODO Auto-generated destructor stub
}

int Target::getTargetLength() {
	return targetLength;
}

void Target::setTargetLength(int targetLength) {
	this->targetLength = targetLength;
}

std::string& Target::getTargetName() {
	return targetName;
}

void Target::setTargetName(std::string& targetName) {
	this->targetName = targetName;
}

std::string& Target::getTargetSequence() {
	return targetSequence;
}

void Target::setTargetSequence(std::string& targetSequence) {
	this->targetSequence = targetSequence;
}

void Target::loadTargetInfo(std::string targetLocation) {
	//target information

	std::string fastaFile(targetLocation);
	fastaFile += targetName;
	fastaFile += ".fasta";
	FILE* f = fopen((char*) fastaFile.c_str(), "r");
	if (f == NULL) {
		std::cout << "fasta file: " << fastaFile << " can't open" << std::endl;
	} else {

		int lineLength = 5000;
		char line[lineLength];

		fgets(line, lineLength, f);
		fscanf (f, "%s", line);

		//cout<<line<<endl;
		targetSequence=line;


		//cout<<targetSequence.size()<<endl;
		targetLength = targetSequence.size();
	}
	fclose(f);
}
