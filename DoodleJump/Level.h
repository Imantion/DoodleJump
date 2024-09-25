#pragma once
#include <vector>
#include <list>

class Platform;
class Enemy;

class Level
{
public:
	Level(int windowWidth, int windowHeight, float playerJumpHeight, int platformsAmount);

	int generateLevel(std::vector<Platform*>& platforms, std::list<Enemy*>& enemies, bool isFirstLevelGeneration); // isFirstLevelGeneration is used to prevent spawning platform on enemy
																												  // returns spawned platforms amount

private:
	bool enemyPreviouslySpawned = false; // used to prevent spawning platform on enemy
	bool changePlatformDirection = false; // used to fix platforms height when 2 movable platforms are spawned in a row
	std::vector<Platform*>::iterator highestPlatform;

	int wWidth, wHeight;
	float wRatio, hRatio;

	float playerJumpHeight;
	int platfromsAmount;
};

