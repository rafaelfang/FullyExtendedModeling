/*
 * Template.cpp
 *
 *  Created on: Dec 14, 2015
 *      Author: Chao
 */

#include "Template.h"

Template::Template() {
	// TODO Auto-generated ructor stub

}
Template::~Template() {
	// TODO Auto-generated destructor stub
}

std::string& Template::getMethodUsed() {
	return methodUsed;
}

void Template::setMethodUsed(std::string& methodUsed) {
	this->methodUsed = methodUsed;
}

Point*& Template::getTemplateCarbonAlphaCoords() {
	return templateCarbonAlphaCoords;
}

void Template::setTemplateCarbonAlphaCoords(Point*& templateCarbonAlphaCoords) {
	this->templateCarbonAlphaCoords = templateCarbonAlphaCoords;
}

std::string& Template::getTemplateName() {
	return templateName;
}

void Template::setTemplateName(std::string& templateName) {
	this->templateName = templateName;
}

std::string& Template::getTemplateReferenceSequenceInfo() {
	return templateReferenceSequenceInfo;
}

void Template::setTemplateReferenceSequenceInfo(
		std::string& templateReferenceSequenceInfo) {
	this->templateReferenceSequenceInfo = templateReferenceSequenceInfo;
}

int Template::getTemplateSequenceLength() {
	return templateSequenceLength;
}

void Template::setTemplateSequenceLength(int templateSequenceLength) {
	this->templateSequenceLength = templateSequenceLength;
}

int Template::loadTemplateInfo(std::string templateLocation) {
	//open protein db file, read and store protein infomation
	std::string proteinFile(templateLocation);
	proteinFile += templateName;
	proteinFile += ".db";
	//cout<<templateName<<endl;
	FILE* fptr = fopen((char*) proteinFile.c_str(), "r");
	if (fptr == NULL) {
		std::cout << "The template file: " << proteinFile << " can't open"
				<< std::endl;
		return -1;
	} else {
		int lineLength = 5000;
		char line[lineLength];
		while (fgets(line, lineLength, fptr) != NULL) {
			if ((strstr(line, ">Reference Sequence Info:") != NULL)) {

				fgets(line, lineLength, fptr);

				int numberOfChars = 0;
				while (line[numberOfChars] != '\0') {

					numberOfChars++;
				}
				numberOfChars--;

				std::string _referenceSequenceInfo(line);
				_referenceSequenceInfo = _referenceSequenceInfo.erase(
						_referenceSequenceInfo.find_last_not_of(" \n\r\t") + 1);
				setTemplateReferenceSequenceInfo(_referenceSequenceInfo);

				//cout << templateSequenceInfo << endl;
				setTemplateSequenceLength(numberOfChars);
				//cout << templateSequenceLength << endl;
			}

			if ((strstr(line, ">Real Sequence Info:") != NULL)) {

				fgets(line, lineLength, fptr);

				int numberOfChars = 0;
				while (line[numberOfChars] != '\0') {

					numberOfChars++;
				}
				numberOfChars--;

				std::string _referenceRealSequenceInfo(line);
				_referenceRealSequenceInfo = _referenceRealSequenceInfo.erase(
						_referenceRealSequenceInfo.find_last_not_of(" \n\r\t")
								+ 1);
				setTemplateRealSequenceInfo(_referenceRealSequenceInfo);

			}

			if ((strstr(line, ">True Secondary Structure:") != NULL)) {

				fgets(line, lineLength, fptr);

				int numberOfChars = 0;
				while (line[numberOfChars] != '\0') {

					numberOfChars++;
				}
				numberOfChars--;

				std::string _referenceTrueSecondaryStructure(line);
				_referenceTrueSecondaryStructure =
						_referenceTrueSecondaryStructure.erase(
								_referenceTrueSecondaryStructure.find_last_not_of(
										" \n\r\t") + 1);
				setTemplateTrueSecondaryStructure(
						_referenceTrueSecondaryStructure);

			}
			if ((strstr(line, ">Ca XYZ:") != NULL)) {

				double Xs[templateSequenceLength];
				double Ys[templateSequenceLength];
				double Zs[templateSequenceLength];

				double temp;
				for (int i = 0; i < templateSequenceLength; i++) {
					fscanf(fptr, "%lf", &temp);
					Xs[i] = temp;
					//if (i % 10 == 0) {
					//	cout << endl;
					//}
					//cout << Xs[i] << " ";
				}
				//cout << endl;

				for (int i = 0; i < templateSequenceLength; i++) {
					fscanf(fptr, "%lf", &temp);
					Ys[i] = temp;
					//if (i % 10 == 0) {
					//cout << endl;
					//}
					//cout << Ys[i] << " ";
				}
				//cout << endl;
				for (int i = 0; i < templateSequenceLength; i++) {
					fscanf(fptr, "%lf", &temp);
					Zs[i] = temp;
					//if (i % 10 == 0) {
					//	cout << endl;
					//}
					//cout << Zs[i] << " ";
				}
				//cout << endl;

				templateCarbonAlphaCoords = (Point*) malloc(
						sizeof(Point) * templateSequenceLength);

				for (int i = 0; i < templateSequenceLength; i++) {
					Point point(Xs[i], Ys[i], Zs[i]);
					templateCarbonAlphaCoords[i] = point;
				}

			}
		}
	}
	return 0;
}

std::string& Template::getTemplateRealSequenceInfo() {
	return templateRealSequenceInfo;
}

void Template::setTemplateRealSequenceInfo(
		std::string& templateRealSequenceInfo) {
	this->templateRealSequenceInfo = templateRealSequenceInfo;
}

std::string& Template::getTemplateTrueSecondaryStructure() {
	return templateTrueSecondaryStructure;
}

void Template::setTemplateTrueSecondaryStructure(
		std::string& templateTrueSecondaryStructure) {
	this->templateTrueSecondaryStructure = templateTrueSecondaryStructure;
}


