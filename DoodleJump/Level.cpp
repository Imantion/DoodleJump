#include "Level.h"
#include "Platform.h"
#include "StaticPlatform.h"
#include "DynamicPlatform.h"
#include "Framework.h"
#include "Consts.h"
#include "Enemy.h"
#include "MovablePlatform.h"
#include "MemoryPool.h"

Level::Level(int windowWidth, int windowHeight, float playerJumpHeight_, int platformsAmount_)
{
	wWidth = windowWidth;
	wHeight = windowHeight;
	wRatio = (float)wWidth / (float)Consts::WIN_WIDTH;
	hRatio = (float)wHeight / (float)Consts::WIN_HEIGHT;

	playerJumpHeight = playerJumpHeight_;
	platfromsAmount = platformsAmount_;

}

int Level::generateLevel(std::vector<Platform*>& platforms, std::list<Enemy*>& enemies, MemoryPool* enemyMemoryPool, bool isFirstLevelGeneration)
{

	int spawnedPlatforms = 0;
	if (isFirstLevelGeneration)
	{
		platforms.reserve(platfromsAmount);
		platforms.push_back(new DynamicPlatform(
			Rectangle(rand() % (wWidth - Consts::PLATFORM_WIDTH), wHeight - wHeight * 0.01,
				Consts::PLATFORM_WIDTH, Consts::PLATFORM_HEIGHT),
			Consts::MOVABLE_PLATFORM_MOVE_DISTANCE,
			Consts::MOVABLE_PLATFORM_MOVE_SPEED,
			Consts::PLATFORM_SPRITE_PATH));

		platforms[0]->ScaleObjectProperties(wRatio, hRatio);


		for (size_t i = 1; i < platfromsAmount; i++)
		{
			platforms.push_back(new DynamicPlatform(
				Rectangle(0, wHeight + Consts::ENEMY_HEIGHT + 10,
					Consts::PLATFORM_WIDTH, Consts::PLATFORM_HEIGHT),
				Consts::MOVABLE_PLATFORM_MOVE_DISTANCE,
				Consts::MOVABLE_PLATFORM_MOVE_SPEED,
				Consts::PLATFORM_SPRITE_PATH));

			platforms[i]->ScaleObjectProperties(wRatio, hRatio);
		}

		highestPlatform = platforms.begin();

	}

	for (size_t i = 0; i < platforms.size(); i++) // Using vector cause it's easier and faster to iterate through
	{
		if (platforms[i] == nullptr || platforms[i]->getMaximalY() > wHeight)
		{
			spawnedPlatforms++;
			bool isMovable = false;
			bool enemySpawned = false;
			if (rand() % 1000 <= 100) // Probability to spawn movable platform
			{
				isMovable = true;

				DynamicPlatform* platform = static_cast<DynamicPlatform*>(platforms[i]);
				platform->setMove(true);

				if (changePlatformDirection)
				{
					platform->setDirection(DynamicPlatform::Direction::DOWN);
					changePlatformDirection = false;
				}
				else
				{
					platform->setDirection(DynamicPlatform::Direction::UP);
					changePlatformDirection = true;
				}
			}
			else
			{
				DynamicPlatform* platform = static_cast<DynamicPlatform*>(platforms[i]);
				platform->setMove(false);
			}

			int enemyHeight = 0; // Need to calculate enemy height so it will not overlap with neiborgh platform
			if (rand() % 1000 <= 150 && !isFirstLevelGeneration) // Spawning enemy when game was initialized. So there won't be situation when enemy is spawned near the first platform
			{
				enemySpawned = true;
				Enemy* enemy = static_cast<Enemy*>(enemyMemoryPool->allocate()); // Using static cast because it's faster and there is always or Enemy or nullptr. So it's safe
				if (enemy)
				{
					enemies.push_back(enemy);
				}
			}

			if (enemyPreviouslySpawned)
				enemyHeight = enemies.back()->getSpriteHeight(); // using this varibale so spawned platform won't overlap with enemy

			int firstCacl = getTickCount();
			float x = rand() % (wWidth - platforms[i]->getCollisionWidth());
			float y = ((*highestPlatform)->getMaximalY() - playerJumpHeight + platforms[i]->getCollisionHeight() + 20); // calculating maximum y coordinat so player can reach it
			y += (rand() % (int)((*highestPlatform)->getMaximalY() - y - platforms[i]->getSpriteHeight() - 10 - enemyHeight)); // randomizing y coordinate in range of maximum and minimum y coordinate 
			int secondCacl = getTickCount();

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

			if (enemySpawned) // This will work because for every platfor there can be enemy. That's why if there is no platform enemy
			{
				enemies.back()->reset(); // Reseting enemy state
				enemies.back()->bindToPlatform(platforms[i]);// Binding enemy to platform
			}

			highestPlatform = platforms.begin() + i;
			enemyPreviouslySpawned = enemySpawned;
		}
	}

	return spawnedPlatforms;
}
