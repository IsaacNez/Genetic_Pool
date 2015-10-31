/*
 * Individual.cpp
 *
 *  Created on: 25 de oct. de 2015
 *      Author: isaac
 */

#include "Individual.h"

Individual::Individual() {
	// TODO Auto-generated constructor stub
	_Strenght = -1;
	_Angle = -1;
	_X = 0;
	_Y = 0;
	_Fitness = 0;
	_TmpAngle = 0;

}

Individual::~Individual() {
	// TODO Auto-generated destructor stub
}

unsigned short Individual::getAngle() const {
	return _Angle;
}

void Individual::setAngle(unsigned short angle) {
	_Angle = angle;
	short tmp = _Angle%360;
	setTmpAngle(tmp);
}

unsigned short Individual::getStrenght() const {
	return _Strenght;
}

void Individual::setStrenght(unsigned short strenght) {
	_Strenght = strenght;
}

float Individual::getX() const {
	return _X;
}

void Individual::setX(float x) {
	_X = x;
}

float Individual::getY() const {
	return _Y;
}

void Individual::setY(float y) {
	_Y = y;
}

short Individual::getFitness() const {
	return _Fitness;
}

void Individual::setFitness(short fitness) {
	_Fitness = fitness;
}

float Individual::getTmpAngle() const {
	return _TmpAngle;
}

void Individual::setTmpAngle(float tmpAngle) {
	_TmpAngle = tmpAngle;
}
