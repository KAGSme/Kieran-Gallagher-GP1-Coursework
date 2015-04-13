/*
============
Xcontroller.h
- Header file for class definition - IMPLEMENTATION
============
*/
#include "Xcontroller.h"

Xcontroller::Xcontroller(int num)
{
	XBOX_CONTROLLER_NUM = num;
}
//code was taken from: http://fisnikhasani.com/xbox-360-controller-input-with-c-using-xinput-h-api/
//returns true if controller is connected
bool Xcontroller::IsXControllerConnected()
{
	//Invoke the memset(); function to zero the XBOX_CONTROLLER_State. 
	memset(&XBOX_CONTROLLER_State, 0, sizeof(XINPUT_STATE));

	//We store the XInputGetState value inside result, note that result is a DWORD which is a typedef unsigned long. 
	DWORD result = XInputGetState(XBOX_CONTROLLER_NUM, &XBOX_CONTROLLER_State);

	//Check if the controller is disconnected using the Ternary Operator. 
	return  result == ERROR_DEVICE_NOT_CONNECTED ? false : true;
}
//code was taken from: http://fisnikhasani.com/xbox-360-controller-input-with-c-using-xinput-h-api/
//returns the state of the controller
XINPUT_STATE Xcontroller::GetState()
{
	memset(&XBOX_CONTROLLER_State, 0, sizeof(XINPUT_STATE));
	XInputGetState(XBOX_CONTROLLER_NUM, &XBOX_CONTROLLER_State);
	return XBOX_CONTROLLER_State;
}
//code was taken from: http://fisnikhasani.com/xbox-360-controller-input-with-c-using-xinput-h-api/
//set the vibration of the left and right motors
void Xcontroller::Vibrate(float left, float right)
{
	XINPUT_VIBRATION vibration;

	//Invoke memset to zero out the XINPUT_VIBRATION. 
	memset(&vibration, 0, sizeof(XINPUT_VIBRATION));

	/*
	According to MSDN Documentation on this,
	speed of the left or right motor. Valid values are
	in the range 0 to 65,535. Zero signifies no motor
	use; 65,535 signifies 100 percent motor use.
	*/

	vibration.wLeftMotorSpeed = (int)(left*65535.0f);
	vibration.wRightMotorSpeed = (int)(right*65535.0f);

	//Vibrate the controller 
	XInputSetState(XBOX_CONTROLLER_NUM, &vibration);
}