/*
============
GameScene.h
- Header file for class definition - SPECIFICATION
- Keeps track of each scene and loads the neccessary game components
============
*/
#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "GameConstants.h"
#include "cInputMgr.h"
#include "cSprite.h"
#include "cBkGround.h"
#include "cPlayerCar.h"
#include "cEnemySpawner.h"
#include "cSoundMgr.h"
#include "cFontMgr.h"

enum SCENES_ENUM//used for tracking which scene the game should render
{
	scene_menu = 0,
	scene_main_game,
	scene_end_game,
};

class GameScene
{
private:
	int windowWidth;
	int windowHeight;
	cInputMgr* theInputMgr;
	cSoundMgr* theSoundMgr;
	cFontMgr* theFontMgr;
	SCENES_ENUM scenes;
	bool sceneIsInitialised;
	//Main game scene objects------------------------
	cTexture texturePlayer;
	cTexture gameUItexture;
	cTexture textureBkgd[3];
	cPlayerCar playerCar;
	cBkGround spriteUIbg;
	cBkGround spriteBkgdEnds[2];
	cBkGround spriteBkgd[3];
	cEnemySpawner* enemySpawner;
	float timer;
	int boundriesX[2];
	//Menu and End scene objects----------------------
	cTexture startScreenTexture;
	cTexture endScreenTexture;
	cTexture controlsUITexture[2];
	cBkGround StartScreen;
	cBkGround EndScreen;
	cBkGround controlsUI[2];
	string scoreDisplay = "";

	float musicThemeLoopTimer = 0;

public:
	GameScene(int windowWidthValue, int windowHeightValue, cInputMgr* theInputMgrValue, cSoundMgr* theSoundMgrValue, cFontMgr* theFontMgrValue); // constructor
	void update(double deltaTime); //Update function
	void MainGame(double elapsedTime);//Mian Game Scene 
	void MainMenu(double elapsedTime);//Main Menu Scene(start screen)
	void EndScene(double elapsedTime);//End Game Scene(game over)
};
#endif