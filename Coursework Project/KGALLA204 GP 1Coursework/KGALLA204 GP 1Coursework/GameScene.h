/*
============
GameScene.h
- Header file for class definition - SPECIFICATION
============
*/
#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "cSprite.h"
#include "cBkGround.h"
#include "cPlayerCar.h"

class GameScene
{
private:

public:
	GameScene(int* windowWidth, int* windowHeight, int* lanes, cInputMgr* theInputMgr); //default constructor
	void update(double deltaTime);
};
#endif