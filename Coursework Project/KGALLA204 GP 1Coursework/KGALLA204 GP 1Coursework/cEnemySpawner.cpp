/*
============
cEnemySpawner.cpp
- Header file for class definition - SPECIFICATION
- Spawns enemies for the player car to dodge while also checking for collisions between player car and enemies
============
*/
#include "cEnemySpawner.h"

cEnemySpawner::cEnemySpawner(cPlayerCar* playerCar, int boundries[2], int speedYValue, int speedBoundryYValue, cTexture* playerTex) // Default Constructer
{
	playerTexture = playerTex;
	spawnBoundries[0] = boundries[0];
	spawnBoundries[1] = boundries[1];
	srand((unsigned int)time(NULL));
	cars.reserve(10);
	thePlayerCar = playerCar;	
	textureEnemy.createTexture("ArtAssets\\EnemyCar_Mini.png");
	spawnTimer = rand() % 3 + 0.5;
	difficultyTimer = 0;
	difficultyTimeTier = 10;
	speedY = 120;
	previousPosition = 0;
	minSpawnTime = 0.8f;
	maxSpawnRange = 2;
}
// spawns a new enemy car and places them in a randomised position along the x-axis---------------------------------------
void cEnemySpawner::spawnEnemy()
{
	cEnemyCar* car = new cEnemyCar();
	car->setTexture(textureEnemy.getTexture());
	car->setTextureDimensions(textureEnemy.getTWidth(), textureEnemy.getTHeight());
	car->setSpriteCentre();
	car->SetSpeedY(speedY);
	cars.push_back(car);
	cars.back()->setSpritePos(glm::vec2(rand() % (spawnBoundries[1] - spawnBoundries[0]) + spawnBoundries[0], -200));
	
	//prevents new car from spawning too close to the x position of the previous car, prevents the possibilty of these 2 cars from overlapping to a certain extent
	while (car->getSpritePos().x >= previousPosition - textureEnemy.getTWidth() / 2 && car->getSpritePos().x <= previousPosition + textureEnemy.getTWidth() / 2){
		cars.back()->setSpritePos(glm::vec2(rand() % (spawnBoundries[1] - spawnBoundries[0]) + spawnBoundries[0], -200));
	}

	previousPosition = cars.back()->getSpritePos().x;
}

// Update function for cEnemySpawner-------------------------------------------------------------------------------------
void cEnemySpawner::update(double deltaTime)
{
	if (speedY == speedBoundryY)
	{
		speedY = speedBoundryY;
	}

	spawnTimer -= deltaTime;
	difficultyTimer += deltaTime;
	//spawn enemy if spawnTimer reaches 0 
	if (spawnTimer <= 0)
	{
		spawnEnemy();
		spawnTimer = rand() % maxSpawnRange + minSpawnTime;
		cout << "\n CarSpawn";
	}
	//erases cars that leave screen via the bottom
	if (!cars.empty()){
		if (cars.front()->IsOffScreen_Bottom())
		{
			cars.erase(cars.begin());
			cout << "\n CarErase";
		}
	}
	//check collisions between player car and enemy cars(must iterate through vector)
	for (vector<cEnemyCar*>::iterator carIterator = cars.begin(); carIterator != cars.end();)
	{
		(*carIterator)->update(deltaTime);
		(*carIterator)->render();
		if ((*carIterator)->PixelCollisionWith((*carIterator), thePlayerCar, &textureEnemy, playerTexture))
		{
			thePlayerCar->ReduceHealth();
			carIterator = cars.erase(carIterator); //erase enemy car
		}
		else (*carIterator++); //continue iterating
	}
	//increase difficulty for player by increasing speed of new enemies by 1.5 each time
	if (difficultyTimer > difficultyTimeTier)
	{
		speedY += speedY / 2;
		difficultyTimeTier += difficultyTimeTier / 1.5;
		cout << "\n SpeedIncrease";
	}
	//increase difficulty for player by reducing the spawn intervals for cars 40 seconds after game start
	if (difficultyTimer > 40)
	{
		minSpawnTime = 0.5;
		maxSpawnRange = 1;
	}
}

