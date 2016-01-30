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

	int getTemplateSequenceLength();
	void setTemplateSequenceLength(int templateSequenceLength);

	int loadTemplateInfo(std::string templateLocation);
	std::string& getTemplateReferenceSequenceInfo();
	void setTemplateReferenceSequenceInfo(
			std::string& templateReferenceSequenceInfo);
	std::string& getTemplateRealSequenceInfo();
	void setTemplateRealSequenceInfo(std::string& templateRealSequenceInfo);
	std::string& getTemplateTrueSecondaryStructure();
	void setTemplateTrueSecondaryStructure(
			std::string& templateTrueSecondaryStructure);

protected:
	std::string templateName;
	std::string templateReferenceSequenceInfo;
	std::string templateRealSequenceInfo;
	std::string templateTrueSecondaryStructure;
	int templateSequenceLength;
	std::string methodUsed;
	Point* templateCarbonAlphaCoords;

};

#endif /* TEMPLATE_H_ */
