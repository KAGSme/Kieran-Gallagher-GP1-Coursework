/*
============
cEnemyCar.cpp
- Header file for class definition - SPECIFICATION
- header file for the cEnemyCar class which is a child of the cSprite class
============
*/
#ifndef CENEMYCAR_H
#define CENEMYCAR_H
#include "cSprite.h"


class cEnemyCar : public cSprite
{

private:
	float speedY = 500;

public:
	void SetSpeedY(float velY);	//Change the default horizontal speed for player car 
	void render();	//default render function
	void update(double deltaTime); //Enemy Car Update function
	bool IsOffScreen_Bottom();
};

#endif