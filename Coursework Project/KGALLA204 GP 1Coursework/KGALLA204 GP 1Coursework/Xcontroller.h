/*
============
Xcontroller.h
- Header file for class definition - SPECIFICATION
============
*/
#ifndef XINPUT_H
#define XINPUT_H
#include "GameConstants.h"


class Xcontroller
{

private:
	XINPUT_STATE XBOX_CONTROLLER_State;
	int XBOX_CONTROLLER_NUM;

public:
	Xcontroller(int num);
	bool IsXControllerConnected();
	XINPUT_STATE GetState();
	void Vibrate(float left, float right);
};


#endif