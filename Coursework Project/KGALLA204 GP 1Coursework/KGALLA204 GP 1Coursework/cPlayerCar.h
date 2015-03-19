/*
============
cPlayerCar.cpp
- Header file for class definition - SPECIFICATION
- header file for the cPlayerCar class which is a child of the cSprite class
============
*/
#ifndef CPLAYERCAR_H
#define CPLAYERCAR_H
#include "cSprite.h"


class cPlayerCar : public cSprite
{

private:
	float speedX = 0.0f;
	int boundryX[2];

public:
	void SetBoundriesX(int boundriesX1, int boundriesX2);	//sets the boundry along the ends of the road which the player can't cross
	void SetSpeedX(float acceleration);	//Change the default horizontal speed for player car 
	void render();	//default render function
	void update(double deltaTime); //Player Car Update function
};


#endif
