/*
 * Point.h
 *
 *  Created on: Oct 20, 2015
 *      Author: Chao
 */

#ifndef POINT_H_
#define POINT_H_

#include <string>

using namespace std;
class Point {
public:
	Point();
	Point(double, double, double);
	virtual ~Point();
	double getX();
	void setX(double x);
	double getY();
	void setY(double y);
	double getZ();
	void setZ(double z);


private:
	double x, y, z;

};

#endif /* POINT_H_ */
