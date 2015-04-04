#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include <Windows.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSprite.h"
#include "cBkGround.h"
#include "cPlayerCar.h"

int WINAPI WinMain(HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR cmdLine,
					int cmdShow)
{
	//Set our window settings, this is currently dependant on how many lanes we want to have in the game

	const int lanes = 6;
	const int windowWidth = 1600;
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
	cTexture textureBkgd[3];
	textureBkgd[1].createTexture("ArtAssets\\RoadTile.png");
	textureBkgd[2].createTexture("ArtAssets\\RoadTileEdgeRight.png");
	textureBkgd[0].createTexture("ArtAssets\\RoadTileEdgeLeft.png");

	cBkGround spriteBkgd[lanes];
	for (int lane = 0; lane < lanes; lane++)
	{
		spriteBkgd[lane].setSpritePos(glm::vec2((textureBkgd[1].getTWidth() * lane) + windowWidth / 2 - (textureBkgd[1].getTWidth() * lanes) / 2, 0.0f));
		spriteBkgd[lane].setTexture(textureBkgd[1].getTexture());
		spriteBkgd[lane].setTextureDimensions(textureBkgd[1].getTWidth(), textureBkgd[1].getTHeight());
	}
	int boundriesX[2];
	// setting up the road tiles that appear at the ends of the screen
	cBkGround spriteBkgdEnds[2];
	spriteBkgdEnds[0].setSpritePos(glm::vec2(spriteBkgd[0].getSpritePos().x - textureBkgd[0].getTWidth(), 0.0f));
	spriteBkgdEnds[0].setTexture(textureBkgd[0].getTexture());
	spriteBkgdEnds[0].setTextureDimensions(textureBkgd[0].getTWidth(), textureBkgd[0].getTHeight());
	boundriesX[0] = spriteBkgd[0].getSpritePos().x;

	spriteBkgdEnds[1].setSpritePos(glm::vec2(spriteBkgd[lanes - 1].getSpritePos().x + textureBkgd[1].getTWidth(), 0.0f));
	spriteBkgdEnds[1].setTexture(textureBkgd[2].getTexture());
	spriteBkgdEnds[1].setTextureDimensions(textureBkgd[2].getTWidth(), textureBkgd[2].getTHeight());
	boundriesX[1] = spriteBkgd[lanes - 1].getSpritePos().x + textureBkgd[1].getTWidth();

	// Instantiating the Player controlled Car
	cTexture texturePlayer;
	texturePlayer.createTexture("ArtAssets\\PlayerCar.png");
	cPlayerCar playerCar;
	playerCar.attachInputMgr(theInputMgr);
	playerCar.setSpritePos(glm::vec2(windowWidth / 2, 400.0f));
	playerCar.setSpriteTranslation(glm::vec2(5.0f, 0.0f));
	playerCar.setTexture(texturePlayer.getTexture());
	playerCar.setTextureDimensions(texturePlayer.getTWidth(), texturePlayer.getTHeight());
	playerCar.setSpriteCentre();
	playerCar.SetSpeedX(250);
	playerCar.SetBoundriesX(boundriesX[0], boundriesX[1]);

	//Main Loop of game, it will keep rendering frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
	{
		pgmWNDMgr->processWNDEvents(); //Process any window events

		//We get the time that passed since the last frame
		double elapsedTime = pgmWNDMgr->getElapsedSeconds();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (int lane = 0; lane < lanes; lane++)
		{
			spriteBkgd[lane].render();
			spriteBkgd[lane].update(elapsedTime);
		}
		spriteBkgdEnds[0].update(elapsedTime);
		spriteBkgdEnds[0].render();
		spriteBkgdEnds[1].update(elapsedTime);
		spriteBkgdEnds[1].render();

		playerCar.update(elapsedTime);
		playerCar.render();

		pgmWNDMgr->swapBuffers();
		theInputMgr->clearBuffers(theInputMgr->KEYS_PRESSED_BUFFER);
	}

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

	return 0; //Return success
}