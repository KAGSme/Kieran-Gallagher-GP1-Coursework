/*
============
cEnemySpawner.cpp
- Header file for class definition - SPECIFICATION
============
*/
#include "cEnemySpawner.h"

cEnemySpawner::cEnemySpawner(cPlayerCar* playerCar, int boundries[2]) // Default Constructer
{
	spawnBoundries[0] = boundries[0];
	spawnBoundries[1] = boundries[1];
	srand((unsigned int)time(NULL));
	cars.reserve(10);
	thePlayerCar = playerCar;	
	textureEnemy.createTexture("ArtAssets\\EnemyCar_Mini.png");
	timer = rand() % 3 + 0.5;
	overallTimer = 0;
	difficultyTimeTier = 5;
	speedY = 120;
}

void cEnemySpawner::spawnEnemy()
{
	cEnemyCar* car = new cEnemyCar();
	car->setTexture(textureEnemy.getTexture());
	car->setTextureDimensions(textureEnemy.getTWidth(), textureEnemy.getTHeight());
	car->setSpriteCentre();
	car->SetSpeedY(speedY);
	cars.push_back(car);
	cars.back()->setSpritePos(glm::vec2(rand() % (spawnBoundries[1] - spawnBoundries[0]) + spawnBoundries[0], -200));
}

void cEnemySpawner::update(double deltaTime)
{
	timer -= deltaTime;
	overallTimer += deltaTime;

	if (timer <= 0)
	{
		spawnEnemy();
		timer = rand() % 3 + 1;
		cout << "\n CarSpawn";
	}

	if (!cars.empty()){
		if (cars.front()->IsOffScreen_Bottom())
		{
			cars.erase(cars.begin());
			cout << "\n CarErase";
		}
	}

	for (int i = 0; i < cars.size(); i++)
	{
		cars[i]->update(deltaTime);
		cars[i]->render();
	}
	
	if (overallTimer > difficultyTimeTier)
	{
		speedY += speedY / 2;
		difficultyTimeTier += difficultyTimeTier / 1.5;
		cout << "\n SpeedIncrease";
	}
}

