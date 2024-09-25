#include "Level.h"
#include "Platform.h"
#include "StaticPlatform.h"
#include "Consts.h"
#include "Enemy.h"
#include "MovablePlatform.h"


Level::Level(int windowWidth, int windowHeight, float playerJumpHeight_, int platformsAmount_)
{
	wWidth = windowWidth;
	wHeight = windowHeight;
	wRatio = (float)wWidth / (float)Consts::WIN_WIDTH;
	hRatio = (float)wHeight / (float)Consts::WIN_HEIGHT;

	playerJumpHeight = playerJumpHeight_;
	platfromsAmount = platformsAmount_;
	
}

int Level::generateLevel(std::vector<Platform*>& platforms, std::list<Enemy*>& enemies, bool isFirstLevelGeneration)
{
	int spawnedPlatforms = 0;
	if (isFirstLevelGeneration)
	{
		platforms.reserve(platfromsAmount);
		platforms.push_back(new StaticPlatform(Rectangle(rand() % (wWidth - Consts::PLATFORM_WIDTH), wHeight - wHeight * 0.01,
			Consts::PLATFORM_WIDTH, Consts::PLATFORM_HEIGHT), Consts::PLATFORM_SPRITE_PATH));

		platforms[0]->ScaleObjectProperties(wRatio, hRatio);
		for (size_t i = 1; i < platfromsAmount; i++)
		{
			platforms.push_back(nullptr);
		}

		highestPlatform = platforms.begin();
	}

	for (size_t i = 0; i < platforms.size(); i++) // Using vector cause it's easier and faster to iterate through
	{
		if (platforms[i] == nullptr || platforms[i]->getMaximalY() > wHeight + 5)
		{
			spawnedPlatforms++;
			bool isMovable = false;
			bool enemySpawned = false;
			if (rand() % 1000 <= 100) // Probability to spawn movable platform
			{
				isMovable = true;
					
				Platform* temp = platforms[i];
				MovablePlatform* platform = new MovablePlatform(
					Rectangle(0, 0, Consts::PLATFORM_WIDTH, Consts::PLATFORM_HEIGHT),
					Consts::MOVABLE_PLATFORM_MOVE_DISTANCE,
					Consts::MOVABLE_PLATFORM_MOVE_SPEED,
					Consts::PLATFORM_SPRITE_PATH);

				platform->ScaleObjectProperties(wRatio, hRatio);

				if (changePlatformDirection)
				{
					platform->setDirection(MovablePlatform::Direction::DOWN);
					changePlatformDirection = false;
				}
				else
				{
					platform->setDirection(MovablePlatform::Direction::UP);
					changePlatformDirection = true;
				}

				platforms[i] = platform;

				if (temp)
					delete temp;
			}
			else
			{
				Platform* temp = platforms[i];
				                                 // -10 and -10 just to spawn platform out of screen. Actual values will be set after
				platforms[i] = new StaticPlatform(Rectangle(-10, -10, Consts::PLATFORM_WIDTH, Consts::PLATFORM_HEIGHT), Consts::PLATFORM_SPRITE_PATH);
				platforms[i]->ScaleObjectProperties(wRatio, hRatio);

				if (temp)
					delete temp;
			}

			int enemyHeight = 0; // Need to calculate enemy height so it will not overlap with neiborgh platform
			if (rand() % 1000 <= 200 && !isFirstLevelGeneration) // Spawning enemy when game was initialized. So there won't be situation when enemy is spawned near the first platform
			{
				Enemy* enemy = new Enemy(Rectangle(-10, -10, Consts::ENEMY_WIDTH, Consts::ENEMY_HEIGHT), Consts::ENEMY_SPRITE_PATH);
				enemy->bindToPlatform(platforms[i]);
				enemy->ScaleObjectProperties(wRatio, hRatio);
				enemyHeight = enemy->getCollisionHeight() + enemy->getCollisionY();
				enemies.push_back(enemy);
				enemySpawned = true;
			}

			if (enemyPreviouslySpawned)
				enemyHeight = enemies.back()->getSpriteHeight(); // using this varibale so spawned platform won't overlap with enemy

			float x = rand() % (wWidth - platforms[i]->getCollisionWidth());
			float y = ((*highestPlatform)->getMaximalY() - playerJumpHeight + platforms[i]->getCollisionHeight() + 20); // calculating maximum y coordinat so player can reach it
			y += (rand() % (int)((*highestPlatform)->getMaximalY() - y - platforms[i]->getSpriteHeight() - 10 - enemyHeight)); // randomizing y coordinate in range of maximum and minimum y coordinate 


			platforms[i]->setPosition(x, y);

			if (isMovable) // Checking if movable platform is overlaping with other platforms
			{
				for (size_t j = 0; j < platforms.size(); j++)
				{
					if (i != j && platforms[j] != nullptr && platforms[i]->checkForOverlap(platforms[j]))
					{
						// if it does. Transaleting on distance where platforms are not overlaping
						platforms[i]->translateY(platforms[i]->getMaximalY() + platforms[i]->getCollisionY() + platforms[i]->getCollisionHeight() - platforms[j]->getSpriteY() - 5);
					}

				}
			}

			highestPlatform = platforms.begin() + i;
			enemyPreviouslySpawned = enemySpawned;
		}
	}

	return spawnedPlatforms;
}
