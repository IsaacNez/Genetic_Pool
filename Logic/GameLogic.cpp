/*
 * GameLogic.cpp
 *
 *  Created on: 25 de oct. de 2015
 *      Author: isaac
 */

#include "GameLogic.h"

Game_Logic::Game_Logic() {
	// TODO Auto-generated constructor stub
	_ListNewParents = new LinkedList<Individual*>();
	_ListParents = new LinkedList<Individual*>();
	_ListBlackBalls = new LinkedList<Individual*>();
	_Player = new Individual();
	_Friccion = 0.5;
	GeneratePopulation();
	GenerateBlackBalls();

}

bool Game_Logic::instanceFlag = false;

Game_Logic* Game_Logic::_Game = NULL;

Game_Logic* Game_Logic::getInstance(){
	if (!instanceFlag){
		_Game = new Game_Logic();
		instanceFlag = true;
		return _Game;
	}else
		return _Game;
}

void Game_Logic::GeneratePopulation()
{
	_SetX = (rand()%(Constants::MAX_X - Constants::MIN_X) + Constants::MIN_X);
	_SetY = (rand()%(Constants::MAX_Y - Constants::MIN_Y) + Constants::MIN_Y);

	for(int i = 0; i < Constants::NUM_GENERATIONS; i++)
	{
		Individual *ball = new Individual();
		unsigned short tmpAngle = ball->getAngle();
		unsigned short tmpStrenght = ball->getStrenght();
		int ChanAngle= rand()%65535;
		int ChanStrenght = rand()%65535;
		tmpAngle = ~ChanAngle;
		tmpStrenght = ~ChanStrenght;
		ball->setAngle(tmpAngle);
		ball->setStrenght(tmpStrenght);
		ball->setX(_SetX);
		ball->setY(_SetY);
		_ListParents->insertData(ball);
		//cout  << ball->getAngle()%360 << ", " << ball->getStrenght()%100 << endl;
	}

	short XPos = (rand()%(Constants::MAX_X - Constants::MIN_X) + Constants::MIN_X);
	short YPos = (rand()%(Constants::MAX_Y - Constants::MIN_Y) + Constants::MIN_Y);
	_Player->setX(XPos);
	_Player->setY(YPos);

}

float Game_Logic::getSetX() const {
	return _SetX;
}

void Game_Logic::setSetX(float setX) {
	_SetX = setX;
}

float Game_Logic::getSetY() const {
	return _SetY;
}

void Game_Logic::setSetY(float setY) {
	_SetY = setY;
}

void Game_Logic::GenerateBlackBalls()
{
	int RanBallNumber = rand()%200;
	LinkedList<int>* Xs = new LinkedList<int>();
	LinkedList<int>* Ys = new LinkedList<int>();
	for (int i = 0; i < RanBallNumber; i++)
	{
		Individual* BlackBall = new Individual();
		short X = (rand()%(Constants::MAX_X - Constants::MIN_X) + Constants::MIN_X);
		short Y = (rand()%(Constants::MAX_Y - Constants::MIN_Y) + Constants::MIN_Y);
		Individual* tmp = _ListParents->getHead()->getData();
		if ((tmp->getX()== X && tmp->getY() == Y)||(_Player->getX() == X && _Player->getY() == Y))
		{
			X = (rand()%(Constants::MAX_X - Constants::MIN_X) + Constants::MIN_X);
			Y = (rand()%(Constants::MAX_Y - Constants::MIN_Y) + Constants::MIN_Y);
		}
		for(int j = 0; j < Xs->getLen(); j++)
		{
			if (X == Xs->getDatabyIndex(j))
				X = (rand()%(Constants::MAX_X - Constants::MIN_X) + Constants::MIN_X);
		}
		for(int n = 0; n < Ys->getLen(); n++)
		{
			if (Y == Ys->getDatabyIndex(n))
				Y = (rand()%(Constants::MAX_Y - Constants::MIN_Y) + Constants::MIN_Y);
		}
		Xs->insertData(X);
		Ys->insertData(Y);
		BlackBall->setX(X);
		BlackBall->setY(Y);
		cout << "X " << X << " Y " << Y << endl;
		_ListBlackBalls->insertData(BlackBall);
	}

}

void Game_Logic::Fitness()
{
	for(int i = 0; i < _ListParents->getLen(); i++)
	{
		cout << "NUEVO!!!" << endl;
		Individual* tmp = _ListParents->getDatabyIndex(i);
		float angle = tmp->getAngle()%360;
		float fuerza = tmp->getStrenght()%100;
		if (angle < 90 && angle > 0)
		{
			float mov_x = 1;
			float mov_y = -mov_x*tan(angle*M_PI/180);
			tmp->setTmpAngle(angle);
			short fit = Move(mov_x,mov_y, fuerza, tmp);
			_ListParents->getDatabyIndex(i)->setFitness(fit);
		}
		else if ( angle > 90 && angle < 180)
		{
			float mov_x = -1;
			float mov_y = -mov_x*tan((angle)*M_PI/180);
			tmp->setTmpAngle(angle);
			short fit = Move(mov_x,mov_y, fuerza, tmp);
			_ListParents->getDatabyIndex(i)->setFitness(fit);
		}
		else if (angle > 180 && angle < 270)
		{
			float mov_x = -1;
			float mov_y = -mov_x*tan((angle)*M_PI/180);
			tmp->setTmpAngle(angle);
			short fit = Move(mov_x,mov_y, fuerza, tmp);
			_ListParents->getDatabyIndex(i)->setFitness(fit);
		}
		else if (angle > 270 && angle < 360)
		{
			float mov_x = 1;
			float mov_y = - (mov_x*tan((angle)*M_PI/180));
			tmp->setTmpAngle(angle);
			short fit = Move(mov_x,mov_y, fuerza, tmp);
			_ListParents->getDatabyIndex(i)->setFitness(fit);
		}
	}
}

const LinkedList<Individual*>*& Game_Logic::getListBlackBalls() const {
	return _ListBlackBalls;
}

void Game_Logic::setListBlackBalls(
		const LinkedList<Individual*>*& listBlackBalls) {
	_ListBlackBalls = listBlackBalls;
}

const Individual*& Game_Logic::getPlayer() const {
	return _Player;
}

void Game_Logic::setPlayer(const Individual*& player) {
	_Player = player;
}

short Game_Logic::Move(float pX, float pY, float pStrenght, Individual* pIndividuo)
{
	float Fuerza = pStrenght;
	float tmp;
	float X = pX;
	float Y = pY;
	cout << "X & Y " << pX << ", " << pY << ", "<<pIndividuo->getTmpAngle() <<endl;
	short fitness = 0;
	float pos_x = pIndividuo->getX();
	float pos_y = pIndividuo->getY();
	while(Fuerza > 0){
		if (floorf(pos_x) +5 >= Constants::MAX_X)
		{
			if (pIndividuo->getTmpAngle() > 0 && pIndividuo->getTmpAngle() < 90)
			{
				tmp = 180 - pIndividuo->getTmpAngle();
				X = -X;
				Y = X*tan(tmp*M_PI/180);
				Fuerza -= Fuerza*0.2;
				pIndividuo->setTmpAngle(tmp);
			}
			else if (pIndividuo->getTmpAngle() > 270 && pIndividuo->getTmpAngle() < 360)
			{
				 tmp = 90+pIndividuo->getTmpAngle()+270;
				X = -X;
				Y = X*tan(tmp*M_PI/180);
				Fuerza -= Fuerza*(0.2);
				pIndividuo->setTmpAngle(180+tmp);
			}
		}
		if (floorf(pos_x) - 5 <= Constants::MIN_X)
		{
			if (pIndividuo->getTmpAngle() > 90 && pIndividuo->getTmpAngle() < 180)
			{
				 tmp = 180 - pIndividuo->getTmpAngle();
				X = abs(X);
				Y = -X*tan(tmp*M_PI/180);
				Fuerza -= Fuerza*0.2;
				pIndividuo->setTmpAngle(tmp);
			}
			else if (pIndividuo->getTmpAngle() > 180 && pIndividuo->getTmpAngle() < 270)
			{
				 tmp = pIndividuo->getTmpAngle() - 180;
				X = abs(X);
				Y = X*tan((360-tmp)*M_PI/180);
				Fuerza -= Fuerza*0.2;
				pIndividuo->setTmpAngle(360-tmp);
			}
		}
		if (floorf(pos_y)+5 >= Constants::MAX_Y)
		{
			if (pIndividuo->getTmpAngle() >180 && pIndividuo->getTmpAngle() < 270)
			{
				 tmp = 360 - pIndividuo->getTmpAngle();
				Y = -X*tan(tmp*M_PI/180);
				Fuerza -= Fuerza*0.2;
				pIndividuo->setTmpAngle(tmp);
			}
			else if (pIndividuo->getTmpAngle() > 270 && pIndividuo->getTmpAngle() < 360)
			{
				 tmp = pIndividuo->getTmpAngle() - 270;
				X = abs(X);
				Y = -X*tan((90-tmp)*M_PI/180);
				Fuerza -= Fuerza*0.2;
				pIndividuo->setTmpAngle(90-tmp);
			}
		}
		if (floorf(pos_y)-5 <= Constants::MIN_Y)
		{
			cout << "HOLA" << endl;
			if (pIndividuo->getTmpAngle() > 90 && pIndividuo->getTmpAngle() < 180)
			{
				 tmp = 180 - pIndividuo->getTmpAngle();
				X = -X;
				Y = X*tan(tmp*M_PI/180);
				cout << "Y " << Y << endl;
				Fuerza -= Fuerza*0.2;
				pIndividuo->setTmpAngle(tmp);
			}
			else if (pIndividuo->getTmpAngle() > 0 && pIndividuo->getTmpAngle() < 90)
			{
				 tmp = 360 - pIndividuo->getTmpAngle();
				X = abs(X);
				Y = -X*tan(tmp*M_PI/180);
				Fuerza -= Fuerza*0.2;
				pIndividuo->setTmpAngle(tmp);
			}

		}
		for(int i = 0; i < _ListBlackBalls->getLen(); i++)
		{
			Individual* tmp = _ListBlackBalls->getDatabyIndex(i);
			if (((pos_y - tmp->getY()) > -3.54) && ((pos_y - tmp->getY()) < 3.54))
			{
				if ((pos_x < tmp->getX()) && (sqrt(pow(pos_x-tmp->getX(),2)+pow(pos_y - tmp->getY(),2))) <= 10)
				{
					if (pIndividuo->getTmpAngle() > 270 && pIndividuo->getTmpAngle() < 360)
					{
						float tmpA = 360 -(pIndividuo->getTmpAngle()+(360-pIndividuo->getTmpAngle())*0.3);
						X = -X;
						Y = -X*tan(tmpA*M_PI/180);
						Fuerza -= Fuerza*0.3;
						pIndividuo->setTmpAngle(tmpA);
						break;
					}
					if (pIndividuo->getTmpAngle() > 0 && pIndividuo->getTmpAngle() < 90)
					{
						float tmpA = 180 - (pIndividuo->getTmpAngle()+(180-pIndividuo->getTmpAngle())*0.3);
						X = -X;
						Y = -X*tan(tmpA*M_PI/180);
						Fuerza -= Fuerza*0.3;
						pIndividuo->setTmpAngle(tmpA);
						break;
					}
				}
				if ((pos_x > tmp->getX()) && (sqrt(pow(pos_x-tmp->getX(),2)+pow(pos_y - tmp->getY(),2))) <= 10)
				{
					if (pIndividuo->getTmpAngle() > 90 && pIndividuo->getTmpAngle() < 180)
					{
						float tmpA = 180-pIndividuo->getTmpAngle()+(180 -pIndividuo->getTmpAngle())*0.3;
						X = abs(X);
						Y = -X*tan(tmpA*M_PI/180);
						Fuerza -= Fuerza*0.3;
						pIndividuo->setTmpAngle(tmpA);
						break;
					}
					if (pIndividuo->getTmpAngle() > 180 && pIndividuo->getTmpAngle() < 270)
					{
						float tmpA = 540-pIndividuo->getTmpAngle()-(pIndividuo->getTmpAngle()-180)*0.3;
						X = abs(X);
						Y = -X*tan(tmpA*M_PI/180);
						Fuerza -= Fuerza*0.3;
						pIndividuo->setTmpAngle(tmpA);
						break;
					}
				}
			}
			if ((((pos_y - tmp->getY()) > -6.46) && ((pos_y - tmp->getY()) < -3.54)))
			{
				if ((pos_x > tmp->getX()) && (sqrt(pow(pos_x-tmp->getX(),2)+pow(pos_y - tmp->getY(),2))) <= 10)
				{
					cout << tmp->getX() << ",1 " << tmp->getY() <<endl;
					float tmpA = 360-pIndividuo->getTmpAngle()+(360-pIndividuo->getTmpAngle())*0.3;
					X = -X;
					Y = -X*tan(tmpA*M_PI/180);
					Fuerza -= Fuerza*0.3;
					pIndividuo->setTmpAngle(tmpA);
					break;
				}
				if ((pos_x < tmp->getX()) && (sqrt(pow(pos_x-tmp->getX(),2)+pow(pos_y - tmp->getY(),2))) <= 10)
				{
					cout << tmp->getX() << ",2 " << tmp->getY() <<endl;
					float tmpA = 360-pIndividuo->getTmpAngle()-(360-pIndividuo->getTmpAngle())*0.3;
					X = abs(X);
					Y = -X*tan(tmpA*M_PI/180);
					Fuerza -= Fuerza*0.3;
					pIndividuo->setTmpAngle(tmpA);
					break;
				}
			}
			if ((((pos_y - tmp->getY()) < 6.46) && ((pos_y - tmp->getY()) > 3.54)))
			{
				if ((pos_x > tmp->getX()) && (sqrt(pow(pos_x-tmp->getX(),2)+pow(pos_y - tmp->getY(),2))) <= 10)
				{
					cout << tmp->getX() << ",3 " << tmp->getY() <<endl;
					float tmpA = 360-pIndividuo->getTmpAngle()-(360-pIndividuo->getTmpAngle())*0.3;
					X = -X;
					Y = -X*tan(tmpA*M_PI/180);
					Fuerza -= Fuerza*0.3;
					pIndividuo->setTmpAngle(tmpA);
					break;
				}
				if ((pos_x < tmp->getX()) && (sqrt(pow(pos_x-tmp->getX(),2)+pow(pos_y - tmp->getY(),2))) <= 10)
				{
					cout << tmp->getX() << ",4 " << tmp->getY() <<endl;
					float tmpA = 360-pIndividuo->getTmpAngle()-(360-pIndividuo->getTmpAngle())*0.3;
					X = abs(X);
					Y = -X*tan(tmpA*M_PI/180);
					Fuerza -= Fuerza*0.3;
					pIndividuo->setTmpAngle(tmpA);
					break;
				}
			}
		}

		pos_x += X;
		pos_y += Y;
		Fuerza -=_Friccion;
		cout << pos_x << ", " << pos_y << ", " << pIndividuo->getTmpAngle()<< " FUERZA "<< Fuerza << endl;
		sleep(0.5);

	}
	fitness = sqrt(pow((_Player->getX()- pos_x),2)+pow((_Player->getY()-pos_y),2));
	cout << "FITNESS" << fitness <<"\n" << endl;
	return fitness;


}

Game_Logic::~Game_Logic() {
	// TODO Auto-generated destructor stub
	instanceFlag = false;
}

