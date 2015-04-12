/*
============
GameScene.h
- Header file for class definition - SPECIFICATION
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

enum SCENES_ENUM
{
	scene_menu = 0,
	scene_main_game,
	sceen_end_game,
};

class GameScene
{
private:
	int windowWidth;
	int windowHeight;
	int lanes;
	cInputMgr* theInputMgr;
	cSoundMgr* theSoundMgr;
	cFontMgr* theFontMgr;
	SCENES_ENUM scenes;
	bool sceneIsInitialised;

	cTexture texturePlayer;
	cTexture gameUItexture;
	cTexture textureBkgd[3];
	cPlayerCar* playerCar;
	cBkGround* spriteUIbg;
	cBkGround* spriteBkgdEnds[2];
	cBkGround* spriteBkgd[3];
	cEnemySpawner* enemySpawner;
	float timer;
	int boundriesX[2];

public:
	GameScene(int &windowWidthValue, int &windowHeightValue, int &lanesValue, cInputMgr* theInputMgrValue, cSoundMgr* theSoundMgrValue, cFontMgr* theFontMgrValue); //default constructor
	void update(double deltaTime); //Update function
	void MainGame(double deltaTime);
	void DestroyMainGame();
};
#endif