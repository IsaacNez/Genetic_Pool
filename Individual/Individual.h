/*
 * Individual.h
 *
 *  Created on: 25 de oct. de 2015
 *      Author: isaac
 */

#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include <iostream>

using namespace std;

class Individual {
public:
	Individual();
	virtual ~Individual();
	unsigned short getAngle() const;
	void setAngle(unsigned short angle);
	unsigned short getStrenght() const;
	void setStrenght(unsigned short strenght);
	float getX() const;
	void setX(float x);
	float getY() const;
	void setY(float y);
	short getFitness() const;
	void setFitness(short fitness);
	float getTmpAngle() const;
	void setTmpAngle(float tmpAngle);

private:
	unsigned short _Strenght;
	unsigned short _Angle;
	float _X;
	float _Y;
	short _Fitness;
	float _TmpAngle;
};

#endif /* INDIVIDUAL_H_ */
