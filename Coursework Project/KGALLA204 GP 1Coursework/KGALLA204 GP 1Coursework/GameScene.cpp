/*
============
GameScene.cpp
- Header file for class definition - Implementation
============
*/
#include "GameScene.h"
GameScene::GameScene(int windowWidthValue, int windowHeightValue, cInputMgr* theInputMgrValue, cSoundMgr* theSoundMgrValue, cFontMgr* theFontMgrValue)
{
	scenes = scene_menu;
	windowHeight = windowHeightValue;
	windowWidth = windowWidthValue;
	theInputMgr = theInputMgrValue;
	theFontMgr = theFontMgrValue;
	theSoundMgr = theSoundMgrValue;

	sceneIsInitialised = false;

	//Loading in-game assets-----------------------------------------------------

	//load font
	LPCSTR UIfont[2] = { "Fonts/Dense-Regular.ttf", "Fonts/wendy.ttf" };
	theFontMgr->addFont("Dense", UIfont[0], 50);
	theFontMgr->addFont("8-BIT", UIfont[1], 100);
	theFontMgr->addFont("8-BIT_small", UIfont[1], 30);
	theFontMgr->addFont("8-BIT_reallySmall", UIfont[1], 20);
	theFontMgr->addFont("8-BIT_black", UIfont[1], 100);
	theFontMgr->getFont("8-BIT_black")->SetColour(0, 0, 0);

	//load game sounds
	LPCSTR gameSounds[] = { "Audio/222804__gthall__engine-idle.wav", "Audio/Evan King - 20XX - 01 Thermal.wav", "Audio/Evan King - 20XX - 31 explosion_1_small.wav", "Audio/Evan King - 20XX - 42 jingle_failure_3.wav" };

	theSoundMgr->add("Engine", gameSounds[0]);
	theSoundMgr->add("ThemeMusic", gameSounds[1]);
	theSoundMgr->add("Explosion", gameSounds[2]);
	theSoundMgr->add("Failure", gameSounds[3]);

	// Create the background texture

	textureBkgd[1].createTexture("ArtAssets\\RoadTile.png");
	textureBkgd[2].createTexture("ArtAssets\\RoadTileEdgeRight.png");
	textureBkgd[0].createTexture("ArtAssets\\RoadTileEdgeLeft.png");

	gameUItexture.createTexture("ArtAssets\\BlackBox.png");

	//load player texture
	texturePlayer.createTexture("ArtAssets\\PlayerCar.png");

	//load menu textures
	startScreenTexture.createTexture("ArtAssets\\StartScreen.png");
	endScreenTexture.createTexture("ArtAssets\\EndScreen.png");

	controlsUITexture[0].createTexture("ArtAssets\\Arrows.png");
	controlsUITexture[1].createTexture("ArtAssets\\Enter.png");

	//Instantiating/Initializing in-game componetnts-------------------------------------------
	//setting up road tiles that the player drives on
	for (int lane = 0; lane < 3; lane++)
	{
		spriteBkgd[lane].setSpritePos(glm::vec2((textureBkgd[1].getTWidth() * lane) + windowWidth / 2 - (textureBkgd[1].getTWidth() * 3) / 2, 0.0f));
		spriteBkgd[lane].setTexture(textureBkgd[1].getTexture());
		spriteBkgd[lane].setTextureDimensions(textureBkgd[1].getTWidth(), textureBkgd[1].getTHeight());
	}

	// setting up the road tiles that appear at the ends of the screen
	spriteBkgdEnds[0].setSpritePos(glm::vec2(spriteBkgd[0].getSpritePos().x - textureBkgd[0].getTWidth(), 0.0f));
	spriteBkgdEnds[0].setTexture(textureBkgd[0].getTexture());
	spriteBkgdEnds[0].setTextureDimensions(textureBkgd[0].getTWidth(), textureBkgd[0].getTHeight());
	boundriesX[0] = spriteBkgd[0].getSpritePos().x;

	spriteBkgdEnds[1].setSpritePos(glm::vec2(spriteBkgd[3 - 1].getSpritePos().x + textureBkgd[1].getTWidth(), 0.0f));
	spriteBkgdEnds[1].setTexture(textureBkgd[2].getTexture());
	spriteBkgdEnds[1].setTextureDimensions(textureBkgd[2].getTWidth(), textureBkgd[2].getTHeight());
	boundriesX[1] = spriteBkgd[3 - 1].getSpritePos().x + textureBkgd[1].getTWidth();
	// setting up a box to contain hud elemets at the bottom of screen
	spriteUIbg.setSpritePos(glm::vec2(0.0f, 500.0f));
	spriteUIbg.setTexture(gameUItexture.getTexture());
	spriteUIbg.setTextureDimensions(windowWidth, 100);

	// Instantiating the Player controlled Car
	playerCar.attachInputMgr(theInputMgr);
	playerCar.attachSoundMgr(theSoundMgr);

	//Instantiating Menu & End Game components-----------------------------------------
	//backgrounds
	StartScreen.setSpritePos(glm::vec2(0.0f, 0.0f));
	StartScreen.setTexture(startScreenTexture.getTexture());
	StartScreen.setTextureDimensions(startScreenTexture.getTWidth(), startScreenTexture.getTHeight());

	EndScreen.setSpritePos(glm::vec2(0.0f, 0.0f));
	EndScreen.setTexture(endScreenTexture.getTexture());
	EndScreen.setTextureDimensions(endScreenTexture.getTWidth(), endScreenTexture.getTHeight());
	//arrow keys
	controlsUI[0].setSpritePos(glm::vec2(520, 410));
	controlsUI[0].setTexture(controlsUITexture[0].getTexture());
	controlsUI[0].setTextureDimensions(controlsUITexture[0].getTWidth()/3, controlsUITexture[0].getTHeight()/3);
	//enter keys
	controlsUI[1].setSpritePos(glm::vec2(450, 510));
	controlsUI[1].setTexture(controlsUITexture[1].getTexture());
	controlsUI[1].setTextureDimensions(controlsUITexture[1].getTWidth()/3, controlsUITexture[1].getTHeight()/3);

	musicThemeLoopTimer = 0;

}
//Update Function--------------------------------------------------------------------
void GameScene::update(double elapsedTime)
{
	if (musicThemeLoopTimer <= 0)
	{
		theSoundMgr->getSnd("ThemeMusic")->playAudio(AL_TRUE);
		musicThemeLoopTimer = 155;
	}
	musicThemeLoopTimer -= elapsedTime;
	
	switch (scenes)//checks for scene to currently render
	{
		case scene_menu:
			MainMenu(elapsedTime);
			break;
		case scene_main_game:
			MainGame(elapsedTime);
			break;
		case scene_end_game:
			EndScene(elapsedTime);
			break;
	}
}

//Main Game Mode---------------------------------------------------------------------
void GameScene::MainGame(double elapsedTime)
{
	if (!sceneIsInitialised)// Initializing the scene
	{
		//initializes player's car
		cout << "\n Main Game";
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
		playerCar.setActive(true);

		//intsantiates new enemy spawner
		enemySpawner = new cEnemySpawner(&playerCar, boundriesX, 150, 300, &texturePlayer);

		//sets timer
		timer = 0;

		sceneIsInitialised = true;
	}

	if (sceneIsInitialised)//Updates/renders scene
	{
		for (int lane = 0; lane < 3; lane++)
		{
			spriteBkgd[lane].render();
			spriteBkgd[lane].update(elapsedTime);
		}
		spriteBkgdEnds[0].update(elapsedTime);
		spriteBkgdEnds[0].render();
		spriteBkgdEnds[1].update(elapsedTime);
		spriteBkgdEnds[1].render();

		if (playerCar.isActive()){
			playerCar.update(elapsedTime);
			playerCar.render();

			enemySpawner->update(elapsedTime);

			if (timer < 9999)timer += elapsedTime;
		}

		spriteUIbg.render();

		ostringstream timerBuffer;//buffer to store timer as string that is displayed
		timerBuffer << setprecision(4) << timer;
		string timerDisplay;
		timerDisplay.append("TIMER: ");
		timerDisplay.append(timerBuffer.str());

		ostringstream playerHealthBuffer;//buffer to store health as string that is displayed
		playerHealthBuffer << playerCar.GetPlayerHealth();
		string healthDisplay;
		healthDisplay.append("HEALTH: ");
		healthDisplay.append(playerHealthBuffer.str());
		//display GUI(HUD) for player
		theFontMgr->getFont("8-BIT")->printText(healthDisplay.c_str(), FTPoint(50, -580, 0.f));
		theFontMgr->getFont("8-BIT")->printText(timerDisplay.c_str(), FTPoint(650, -580, 0.f));

		if (!playerCar.isActive())//switches scene if player is 'dead'
		{
			delete enemySpawner;//delete instance of enemySpawner
			Sleep(1000);//pause the game for a second to prevent making the game feel too jarring when stopping
			sceneIsInitialised = false;
			scenes = scene_end_game;
		}
	}
}

//Main Menu---------------------------------------------------------------------
void GameScene::MainMenu(double elapsedTime)
{
	if (!sceneIsInitialised)//initializes scene
	{
		theInputMgr->getController(0).Vibrate(0, 0);
		cout << "\n Main Menu";
		sceneIsInitialised = true;
	}
	if (sceneIsInitialised)//Updates/renders scene
	{
		//switches scene if player presses 'a' on game pad or return on the keyboard
		if (theInputMgr->isKeyDown(VK_RETURN) || theInputMgr->getController(0).GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			sceneIsInitialised = false;
			scenes = scene_main_game;
		}

		StartScreen.render();
		controlsUI[0].render();
		controlsUI[1].render();


		theFontMgr->getFont("8-BIT")->printText("SPEEDY TRAFFIC", FTPoint(650, -200, 0.f));
		theFontMgr->getFont("8-BIT_small")->printText("Left/right Arrow Keys or use D-PAD to move left/right!", FTPoint(520, -400, 0.f));
		theFontMgr->getFont("8-BIT_small")->printText("Press Enter Key or 'A'button to Start!", FTPoint(450, -500, 0.f));
		theFontMgr->getFont("8-BIT_reallySmall")->printText("Game By Kieran Gallagher", FTPoint(10, -20, 0.f));
		theFontMgr->getFont("8-BIT_reallySmall")->printText("Royalty free Music /sound effects By Evan King", FTPoint(10, -40, 0.f));

	}
}

//End Scene(game over)---------------------------------------------------------------------
void GameScene::EndScene(double elapsedTime)
{
	if (!sceneIsInitialised)//initializing scene
	{
		cout << "\n End Scene";

		theInputMgr->getController(0).Vibrate(0, 0);
	
		ostringstream finalScoreMessage; // buffer to store score as string that is displayed
		finalScoreMessage << setprecision(4) << (timer * 100);//generates score based off of how long player survived
		scoreDisplay = "";
		scoreDisplay.append("YOU DIE WITH ");
		scoreDisplay.append(finalScoreMessage.str());
		scoreDisplay.append(" POINTS");

		sceneIsInitialised = true;
	}
	if (sceneIsInitialised)//updates/render scene
	{
		//switches scene if player presses 'a' on game pad or return on the keyboard
		if (theInputMgr->isKeyDown(VK_RETURN) || theInputMgr->getController(0).GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			sceneIsInitialised = false;
			scenes = scene_main_game;
		}

		EndScreen.render();
		controlsUI[1].render();

		theFontMgr->getFont("8-BIT_black")->printText(scoreDisplay.c_str(), FTPoint(300, -windowHeight / 2 - 30, 0.f));
		theFontMgr->getFont("8-BIT_small")->printText("Press Enter Key or 'A'button to Retry!", FTPoint(450, -500, 0.f));
	}
}