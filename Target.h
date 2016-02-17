/*
 * Target.h
 *
 *  Created on: Dec 14, 2015
 *      Author: Chao
 */

#ifndef TARGET_H_
#define TARGET_H_
#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include <cwchar>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "Point.h"

class Target {
public:
	Target();
	Target(std::string);
	virtual ~Target();
	int getTargetLength();
	void setTargetLength(int targetLength);
	std::string& getTargetName();
	void setTargetName(std::string& targetName);
	std::string& getTargetSequence();
	void setTargetSequence(std::string& targetSequence);

	void loadTargetInfo(std::string targetLocation);

protected:
	std::string targetName;
	std::string targetSequence;
	int targetLength;
};

#endif /* TARGET_H_ */
