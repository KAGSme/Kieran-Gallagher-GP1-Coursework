/*
== == == == == == == == =
cInputMgr.h
- Header file for class definition - SPECIFICATION
- Header file for the InputMgr class
== == == == == == == == =
*/
#ifndef _CINPUTMGR_H
#define _CINPUTMGR_H
#include "GameConstants.h"

class cInputMgr
{
private:

	bool keysDownBuffer[256];     // true if specified key is down
	bool keysPressedBuffer[256];  // true if specified key was pressed

	static cInputMgr* pInstance;

	Xcontroller* Xctrl[4];

public:
	static cInputMgr* getInstance();

	// Values for clearing keysDown, KeysPressed and Mouse buffer
	const BYTE KEYS_DOWN_BUFFER = 1;
	const BYTE KEYS_PRESSED_BUFFER = 2;

	cInputMgr();								// Constructor
	void keyDown(WPARAM);						// Save key down state
	void keyUp(WPARAM);							// Save key up state
	bool isKeyDown(int vkey);					// Returns true if the specified VIRTUAL KEY is down, otherwise false.
	bool wasKeyPressed(int vkey);				// Return true if the specified VIRTUAL KEY has been pressed
	bool anyKeyPressed();						// Return true if any key was pressed
	void clearKeyPress(int vkey);				// Clear the specified key press
	void clearBuffers(BYTE bufferToClear);		// Clear buffers, single or combined
	void addController(Xcontroller* Xgamepad, int number); //adds controller to input manager(assigns to Xctrl[number])
	Xcontroller getController(int number);//returns controller 

};

#endif