/*
============
cEnemySpawner.h
- Header file for class definition - SPECIFICATION
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
	vector<cEnemyCar*> cars;
	float timer = 0;
	float overallTimer = 0;
	int spawnBoundries[2];
	int speedY = 100;
	float difficultyTimeTier;
	float speedIncrease;

public:
	cEnemySpawner(cPlayerCar* playerCar, int boundries[2]); //default constructor
	void update(double deltaTime); // update function
	void spawnEnemy(); // spawns a new enemy car and places them in a randomised position along the x-axis

};
#endif