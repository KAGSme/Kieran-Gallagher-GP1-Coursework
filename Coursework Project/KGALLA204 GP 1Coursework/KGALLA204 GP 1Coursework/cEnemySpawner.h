/*
============
cEnemySpawner.h
- Header file for class definition - SPECIFICATION
- Spawns enemies for the player car to dodge while also checking for collisions between player car and enemies
============
*/
#ifndef CENEMYSPAWNER_H
#define CENEMYSPAWNER_H
#include "GameConstants.h"
#include "cPlayerCar.h"
#include "cEnemyCar.h"

class cEnemySpawner
{
private:
	cPlayerCar* thePlayerCar;
	cTexture textureEnemy;
	cTexture* playerTexture;
	vector<cEnemyCar*> cars;
	float spawnTimer = 0;
	float difficultyTimer = 0;
	int spawnBoundries[2];
	int speedY = 100;
	int speedBoundryY = 300;
	float difficultyTimeTier;
	float speedIncrease;
	int previousPosition;
	int maxSpawnRange;
	float minSpawnTime;

public:
	cEnemySpawner(cPlayerCar* playerCar, int boundries[2], int speedYValue, int speedBoundryYValue, cTexture* playerTex); //constructor
	void update(double deltaTime); // update function
	void spawnEnemy(); // spawns a new enemy car and places them in a randomised position along the x-axis
};
#endif