/*
== == == == == == == == =
cInputMgr.h
- Header file for class definition - SPECIFICATION
- Header file for the InputMgr class
== == == == == == == == =
*/

#include "cInputMgr.h"

cInputMgr* cInputMgr::pInstance=NULL;

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cInputMgr* cInputMgr::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cInputMgr();
	}
	return cInputMgr::pInstance;
}

/*
=================================================================================
Constructor
=================================================================================
*/
cInputMgr::cInputMgr()
{
	for (int key = 0; key < 256; key++)		// clear key down buffer
	{
		keysDownBuffer[key] = false;
	}
	for (int key = 0; key < 256; key++)			// clear key pressed array
	{
		keysPressedBuffer[key] = false;
	}
	
}

/*
=============================================================================
   Set true in the keysDown and keysPessed array for this key
=============================================================================
*/
void cInputMgr::keyDown(WPARAM wParam)
{
	if (wParam < 256)
	{
		keysDownBuffer[wParam] = true;    // update keysDown array
		keysPressedBuffer[wParam] = true; // update keysPressed array
	}
}

/*
=============================================================================
   Set false in the keysDown array for this key
=============================================================================
*/
void cInputMgr::keyUp(WPARAM wParam)
{
	if (wParam < 256)
	{
		keysDownBuffer[wParam] = false;
	}
}
/*
=============================================================================
   Returns true if the specified VIRTUAL KEY is down, otherwise false.
=============================================================================
*/
bool cInputMgr::isKeyDown(int vkey)
{
	if (vkey < 256)
	{
		return keysDownBuffer[vkey];
	}
	else
	{
		return false;
	}
}
/*
=============================================================================
   Return true if the specified VIRTUAL KEY has been pressed
=============================================================================
*/
bool cInputMgr::wasKeyPressed(int vkey)
{
	if (vkey < 256)
	{
		return keysPressedBuffer[vkey];
	}		
	else
	{
		return false;
	}	
}
/*
=============================================================================
   Return true if any key was pressed
=============================================================================
*/
bool cInputMgr::anyKeyPressed()
{
	for (BYTE keys = 0; keys < 256; keys++)
	{
		if (keysPressedBuffer[keys] == false)
		{
			return true;
		}
	}
	return false;
}
/*
=============================================================================
   Clear the specified key press
=============================================================================
*/
void cInputMgr::clearKeyPress(int vkey)
{
	if (vkey < 256)
	{
		keysPressedBuffer[vkey] = false;
	}
}
/*
=============================================================================
   Clear buffers, single or combined
=============================================================================
*/
void cInputMgr::clearBuffers(BYTE bufferToClear)
{
	if (bufferToClear & KEYS_DOWN_BUFFER)       // if clear keys down
	{
		for (int key = 0; key < 256; key++)
		{
			keysDownBuffer[key] = false;
		}
	}
	if (bufferToClear & KEYS_PRESSED_BUFFER)    // if clear keys pressed
	{
		for (int key = 0; key < 256; key++)
		{
			keysPressedBuffer[key] = false;
		}
	}
}

void cInputMgr::addController(Xcontroller* Xgamepad, int number)
{
	Xctrl[number] = Xgamepad;
}

Xcontroller cInputMgr::getController(int number)
{
	return *Xctrl[number];
}



