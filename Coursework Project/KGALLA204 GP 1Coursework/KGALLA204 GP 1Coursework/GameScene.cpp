/*
============
GameScene.cpp
- Header file for class definition - Implementation
============
*/
#include "GameScene.h"
GameScene::GameScene(int &windowWidthValue, int &windowHeightValue, int &lanesValue, cInputMgr* theInputMgrValue, cSoundMgr* theSoundMgrValue, cFontMgr* theFontMgrValue)
{
	scenes = scene_main_game;
	windowHeight = windowHeightValue;
	windowWidth = windowWidthValue;
	lanes = lanesValue;
	theInputMgr = theInputMgrValue;
	theFontMgr = theFontMgrValue;
	theSoundMgr = theSoundMgrValue;

	sceneIsInitialised = false;

	//Loading in-game assets
	//load font
	LPCSTR UIfont = "Fonts/Dense-Regular.ttf";

	theFontMgr->addFont("Dense", UIfont, 90);

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

}

void GameScene::update(double deltaTime)
{
	if (scenes == scene_main_game)
	{
		MainGame(deltaTime);
	}
}

void GameScene::MainGame(double deltaTime)
{
	if (!sceneIsInitialised)
	{
		spriteBkgd[3] = new cBkGround();
		for (int lane = 0; lane < lanes; lane++)
		{
			spriteBkgd[lane]->setSpritePos(glm::vec2((textureBkgd[1].getTWidth() * lane) + windowWidth / 2 - (textureBkgd[1].getTWidth() * lanes) / 2, 0.0f));
			spriteBkgd[lane]->setTexture(textureBkgd[1].getTexture());
			spriteBkgd[lane]->setTextureDimensions(textureBkgd[1].getTWidth(), textureBkgd[1].getTHeight());
		}

		// setting up the road tiles that appear at the ends of the screen
		spriteBkgdEnds[2] = new cBkGround();
		spriteBkgdEnds[0]->setSpritePos(glm::vec2(spriteBkgd[0]->getSpritePos().x - textureBkgd[0].getTWidth(), 0.0f));
		spriteBkgdEnds[0]->setTexture(textureBkgd[0].getTexture());
		spriteBkgdEnds[0]->setTextureDimensions(textureBkgd[0].getTWidth(), textureBkgd[0].getTHeight());
		boundriesX[0] = spriteBkgd[0]->getSpritePos().x;

		spriteBkgdEnds[1]->setSpritePos(glm::vec2(spriteBkgd[lanes - 1]->getSpritePos().x + textureBkgd[1].getTWidth(), 0.0f));
		spriteBkgdEnds[1]->setTexture(textureBkgd[2].getTexture());
		spriteBkgdEnds[1]->setTextureDimensions(textureBkgd[2].getTWidth(), textureBkgd[2].getTHeight());
		boundriesX[1] = spriteBkgd[lanes - 1]->getSpritePos().x + textureBkgd[1].getTWidth();

		spriteUIbg = new cBkGround();
		spriteUIbg->setSpritePos(glm::vec2(0.0f, 500.0f));
		spriteUIbg->setTexture(gameUItexture.getTexture());
		spriteUIbg->setTextureDimensions(windowWidth, 100);

		// setting up the Player controlled Car
		playerCar = new cPlayerCar();
		playerCar->attachInputMgr(theInputMgr);
		playerCar->attachSoundMgr(theSoundMgr);
		playerCar->setSpritePos(glm::vec2(windowWidth / 2, 400.0f));
		playerCar->setSpriteTranslation(glm::vec2(5.0f, 0.0f));
		playerCar->setTexture(texturePlayer.getTexture());
		playerCar->setTextureDimensions(texturePlayer.getTWidth(), texturePlayer.getTHeight());
		playerCar->setSpriteCentre();
		playerCar->SetSpeedX(600);
		playerCar->SetBoundriesX(boundriesX[0], boundriesX[1]);
		playerCar->SetPlayerHealth(3);

		enemySpawner = new cEnemySpawner(playerCar, boundriesX, 120, 300);

		theSoundMgr->getSnd("ThemeMusic")->playAudio(AL_TRUE);

		timer = 0;

		sceneIsInitialised = true;
	}

	if (sceneIsInitialised)
	{
		for (int lane = 0; lane < lanes; lane++)
		{
			spriteBkgd[lane]->render();
			spriteBkgd[lane]->update(deltaTime);
		}
		spriteBkgdEnds[0]->update(deltaTime);
		spriteBkgdEnds[0]->render();
		spriteBkgdEnds[1]->update(deltaTime);
		spriteBkgdEnds[1]->render();

		if (playerCar->IsAlive()){
			playerCar->update(deltaTime);
			playerCar->render();

			enemySpawner->update(deltaTime);

			if (timer < 9999)timer += deltaTime;
		}

		spriteUIbg->render();

		ostringstream timerBuffer;
		timerBuffer << setprecision(4) << timer;
		string timerDisplay;
		timerDisplay.append("TIMER: ");
		timerDisplay.append(timerBuffer.str());

		ostringstream playerHealthBuffer;
		playerHealthBuffer << playerCar->GetPlayerHealth();
		string healthDisplay;
		healthDisplay.append("HEALTH: ");
		healthDisplay.append(playerHealthBuffer.str());

		ostringstream finalScoreMessage;
		finalScoreMessage << setprecision(4) << (timer * 100);
		string scoreDisplay;
		scoreDisplay.append("YOU DIE WITH ");
		scoreDisplay.append(finalScoreMessage.str());
		scoreDisplay.append(" POINTS");

		theFontMgr->getFont("Dense")->printText(healthDisplay.c_str(), FTPoint(50, -580, 0.f));
		theFontMgr->getFont("Dense")->printText(timerDisplay.c_str(), FTPoint(650, -580, 0.f));
		if (!playerCar->IsAlive())
		{
			theFontMgr->getFont("Dense")->printText(scoreDisplay.c_str(), FTPoint(300, -windowHeight / 2, 0.f));
		}
	}
}