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
	Xcontroller(int num);//constructer
	bool IsXControllerConnected();//returns true if controller is connected
	XINPUT_STATE GetState();//returns the state of the controller
	void Vibrate(float left, float right);//set the vibration of the left and right motors
};


#endif