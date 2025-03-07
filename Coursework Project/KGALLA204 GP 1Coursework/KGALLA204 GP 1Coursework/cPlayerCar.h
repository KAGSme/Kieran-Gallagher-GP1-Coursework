/*
============
cPlayerCar.h
- Header file for class definition - SPECIFICATION
============
*/
#ifndef CPLAYERCAR_H
#define CPLAYERCAR_H
#include "cSprite.h"


class cPlayerCar : public cSprite
{

private:
	float speedX = 0.0f;
	float boundryX[2];
	int playerHealth;
	bool isAlive;
	float engineEffectTimer = 0;
	bool dpadLeft;
	bool dpadRight;
	int vibrateStrength = 0;
	float vibrateTimer = 0;

public:
	cPlayerCar();//constructor
	int GetPlayerHealth();//returns player health
	void SetBoundriesX(float boundriesX1, float boundriesX2);	//sets the boundry along the ends of the road which the player can't cross
	void SetSpeedX(float velX);	//Change the default horizontal speed for player car 
	void SetPlayerHealth(int value);
	void render();	//default render function
	void update(double deltaTime); //Player Car Update function
	void ReduceHealth(); //Reduces player health
};


#endif
