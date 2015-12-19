/*
 * Template.h
 *
 *  Created on: Dec 14, 2015
 *      Author: Chao
 */

#ifndef TEMPLATE_H_
#define TEMPLATE_H_

#include "Target.h"

class Template: public Target {
public:
	Template();
	virtual ~Template();
	std::string& getMethodUsed();
	void setMethodUsed(std::string& methodUsed);
	Point*& getTemplateCarbonAlphaCoords();
	void setTemplateCarbonAlphaCoords(Point*& templateCarbonAlphaCoords);
	std::string& getTemplateName();
	void setTemplateName(std::string& templateName);
	std::string& getTemplateSequenceInfo();
	void setTemplateSequenceInfo(std::string& templateSequenceInfo);
	int getTemplateSequenceLength();
	void setTemplateSequenceLength(int templateSequenceLength);

	int loadTemplateInfo(std::string templateLocation);
protected:
	std::string templateName;
	std::string templateSequenceInfo;
	int templateSequenceLength;
	std::string methodUsed;
	Point* templateCarbonAlphaCoords;

};

#endif /* TEMPLATE_H_ */
