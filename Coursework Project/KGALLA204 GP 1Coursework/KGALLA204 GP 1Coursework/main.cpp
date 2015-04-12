#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSprite.h"
#include "cBkGround.h"
#include "cPlayerCar.h"
#include "cEnemySpawner.h"
#include "cSoundMgr.h"
#include "cFontMgr.h"

int WINAPI WinMain(HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR cmdLine,
					int cmdShow)
{
	//Set our window settings, this is currently dependant on how many lanes we want to have in the game

	const int lanes = 3;
	const int windowWidth = 1200;
	const int windowHeight = 600;
	const int windowBPP = 16;

	//for debug
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);

	//This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	//This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	//The example OpenGL code
	windowOGL theOGLWnd;

	//Attach the OpenGL window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// This is the sound manager
	static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();

	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

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

	LPCSTR UIfont = "Fonts/Dense-Regular.ttf";

	theFontMgr->addFont("Dense", UIfont, 90);

	//load game sounds
	LPCSTR gameSounds[] = { "Audio/222804__gthall__engine-idle.wav", "Audio/Evan King - 20XX - 01 Thermal.wav", "Audio/Evan King - 20XX - 31 explosion_1_small.wav" , "Audio/Evan King - 20XX - 42 jingle_failure_3.wav" };

	theSoundMgr->add("Engine", gameSounds[0]);
	theSoundMgr->add("ThemeMusic", gameSounds[1]);
	theSoundMgr->add("Explosion", gameSounds[2]);
	theSoundMgr->add("Failure", gameSounds[3]);

	// Create the background texture
	cTexture textureBkgd[3];
	textureBkgd[1].createTexture("ArtAssets\\RoadTile.png");
	textureBkgd[2].createTexture("ArtAssets\\RoadTileEdgeRight.png");
	textureBkgd[0].createTexture("ArtAssets\\RoadTileEdgeLeft.png");
	cTexture gameUItexture;
	gameUItexture.createTexture("ArtAssets\\BlackBox.png");

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

	cBkGround spriteUIbg;
	spriteUIbg.setSpritePos(glm::vec2(0.0f, 500.0f));
	spriteUIbg.setTexture(gameUItexture.getTexture());
	spriteUIbg.setTextureDimensions(windowWidth, 100);

	// Instantiating the Player controlled Car
	cTexture texturePlayer;
	texturePlayer.createTexture("ArtAssets\\PlayerCar.png");
	cPlayerCar playerCar;
	playerCar.attachInputMgr(theInputMgr);
	playerCar.attachSoundMgr(theSoundMgr);
	playerCar.setSpritePos(glm::vec2(windowWidth / 2, 400.0f));
	playerCar.setSpriteTranslation(glm::vec2(5.0f, 0.0f));
	playerCar.setTexture(texturePlayer.getTexture());
	playerCar.setTextureDimensions(texturePlayer.getTWidth(), texturePlayer.getTHeight());
	playerCar.setSpriteCentre();
	playerCar.SetSpeedX(600);
	playerCar.SetBoundriesX(boundriesX[0], boundriesX[1]);
	playerCar.SetPlayerHealth(3);

	cEnemySpawner enemySpawner(&playerCar, boundriesX, 120, 300);

	theSoundMgr->getSnd("ThemeMusic")->playAudio(AL_TRUE);

	float timer = 0;

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

		if (playerCar.IsAlive()){
			playerCar.update(elapsedTime);
			playerCar.render();

			enemySpawner.update(elapsedTime);

			if(timer < 9999)timer += elapsedTime;
		}

		spriteUIbg.render();

		ostringstream timerBuffer;
		timerBuffer << setprecision(4) << timer;
		string timerDisplay;
		timerDisplay.append("TIMER: ");
		timerDisplay.append(timerBuffer.str());

		ostringstream playerHealthBuffer;
		playerHealthBuffer << playerCar.GetPlayerHealth();
		string healthDisplay;
		healthDisplay.append("HEALTH: ");
		healthDisplay.append(playerHealthBuffer.str());

		ostringstream finalScoreMessage;
		finalScoreMessage << setprecision(4) << (timer * 100);
		string scoreDisplay;
		scoreDisplay.append("YOU DIE WITH ");
		scoreDisplay.append(finalScoreMessage.str());
		scoreDisplay.append(" POINTS");

		theFontMgr->getFont("Dense")->printText(healthDisplay.c_str() , FTPoint(50, -580, 0.f));
		theFontMgr->getFont("Dense")->printText(timerDisplay.c_str(), FTPoint(650, -580, 0.f));
		if (!playerCar.IsAlive())
		{
			theFontMgr->getFont("Dense")->printText(scoreDisplay.c_str(), FTPoint(300, -windowHeight/2, 0.f));
		}

		pgmWNDMgr->swapBuffers();
		theInputMgr->clearBuffers(theInputMgr->KEYS_PRESSED_BUFFER);

	}

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

	return 0; //Return success
}