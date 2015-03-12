#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include <Windows.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSprite.h"

int WINAPI WinMain(HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR cmdLine,
					int cmdShow)
{
	//Set our window settings, this is currently dependant on how many lanes we want to have in the game

	const int lanes = 4;
	const int windowWidth = 200 * lanes;
	const int windowHeight = 600;
	const int windowBPP = 16;

	//This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	//This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	//The example OpenGL code
	windowOGL theOGLWnd;

	//Attach the OpenGL window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	//Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);

	//Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
	{
		//if it fails

		MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND();//Reset the display and exit
		return 1;
	}

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
	{
		MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); // Reset the display and exit
		return 1;
	}

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	// Create the background texture
	cTexture textureBkgd[lanes];
	for (int lane = 0; lane < lanes; lane++)
	{
		textureBkgd.createTexture("ArtAssets//RoadTile.png");
	}

	//Main Loop of game, it will keep rendering frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
	{

	}

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

	return 0; //Return success
}