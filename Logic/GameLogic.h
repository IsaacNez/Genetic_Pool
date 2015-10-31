/*
 * GameLogic.h
 *
 *  Created on: 25 de oct. de 2015
 *      Author: isaac
 */

#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <math.h>
#include <unistd.h>

#include "Constants.h"
#include "../Data_Structure/LinkedList.h"
#include "../Individual/Individual.h"

using namespace std;
class Game_Logic {
public:
	void Fitness();
	Game_Logic();
	Game_Logic* getInstance();
	virtual ~Game_Logic();
	float getSetX() const;
	void setSetX(float setX);
	float getSetY() const;
	void setSetY(float setY);
	const LinkedList<Individual*>*& getListBlackBalls() const;
	void setListBlackBalls(const LinkedList<Individual*>*& listBlackBalls);
	const Individual*& getPlayer() const;
	void setPlayer(const Individual*& player);

private:
	static Game_Logic* _Game;
	static bool instanceFlag;
	void GeneratePopulation();
	void GenerateBlackBalls();
	short Move(float pX, float pY, float pStrenght, Individual* pIndividuo);

	float _SetX;
	float _SetY;
	float _Friccion;
	LinkedList<Individual*>* _ListParents;
	LinkedList<Individual*>* _ListNewParents;
	LinkedList<Individual*>* _ListBlackBalls;
	Individual* _Player;
};

#endif /* GAMELOGIC_H_ */
