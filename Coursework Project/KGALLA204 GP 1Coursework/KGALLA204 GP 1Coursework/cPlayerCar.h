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
#include "cInputMgr.h"

class cPlayerCar : public cSprite
{

private:
	cInputMgr* m_InputMgr;
	float speedX = 10.0f;

public:

	void render();	//default render function
	void update(float deltaTime); //Player Car Update function
	void attachInputMgr(cInputMgr* InputMgr); //attaches Input manager
};


#endif
