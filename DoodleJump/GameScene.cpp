#include "GameScene.h"
#include "Consts.h"
#include "GameObject.h"
#include "Framework.h"
#include "algorithm" 
#include "Doodler.h"
#include "Projectile.h"
#include "Enemy.h"
#include "DoodlerController.h"
#include "Platform.h"
#include "Level.h"
#include "Ability.h"
#include <iostream>
#include "Invincibility.h"


GameScene::GameScene(int windowWidth, int windowHeight):
	Scene(windowWidth, windowHeight)
{
	mousePosX = 0;
	mousePosY = 0;
	movedDistance = 0;
	playerJumpCount = 0;
	platformsPassed = 0;
	platformsAmount = 15;
}



GameScene::~GameScene()
{
	for (size_t i = 0; i < platforms.size(); i++)
	{
		delete platforms[i];
	}

	for (auto enemy : enemies)
	{
		delete enemy;
	}

	for (auto projectile : projectiles)
	{
		delete projectile;
	}

	for (auto ability : abilities)
	{
		delete ability;
	}

	delete doodlerController;

	delete level;
}

bool GameScene::Init()
{
	try
	{
		Doodler* doodler = new Doodler(Rectangle(13, 10, 34, 51), Rectangle(wWidth / 2, wHeight - 51 * hRatio, 62, 60), Consts::GRAVITY, 
									   Consts::DOODLER_SPRITE_LEFT_PATH, Consts::DOODLER_SPRITE_RIGHT_PATH);

		doodlerController = new DoodlerController(doodler, Consts::DOODLER_SPEED, Consts::JUMP_VELOCITY);
		doodlerController->ScaleObjectProperties(wRatio, hRatio);
		doodler->jump(Consts::JUMP_VELOCITY * hRatio);


		level = new Level(wWidth, wHeight, doodlerController->getDoodlerJumpHeight(), platformsAmount);
		level->generateLevel(platforms, enemies, true);

		background = createSprite(Consts::BACKGROUND_SPRITE_PATH);
		setSpriteSize(background, wWidth, wHeight);

		state = Scene::State::PLAYING;

		abilities.reserve(2);

		return true;
	}
	catch (std::exception a)
	{
		return false;
	}
	
}

void GameScene::update(float deltaTime)
{
	

	handleDoodlerState();
	handleEnemyState();
	handleAllCollisions();
	handleAbilityState();

	if(doodlerController->getDoodler()->getSpriteY() < wHeight / 2 - 10 * hRatio)
		moveDown(wHeight / 2 - 10 * hRatio - doodlerController->getDoodler()->getSpriteY());

	
	doodlerController->update(deltaTime);

	for (size_t i = 0; i < platforms.size(); i++)
	{

		platforms[i]->update(deltaTime);
	}

	for(auto projectile : projectiles)
	{
		projectile->update(deltaTime);
	}

	for (auto enemy : enemies)
	{
		enemy->isOutOfBotomBoundary(wHeight);
		enemy->update(deltaTime);
	}

	for (size_t i = 0; i < abilities.size(); i++)
	{
		abilities[i]->update(deltaTime);
	}

	if (!projectiles.empty() && (*projectiles.begin())->isLifeTimeOver())
	{
			Projectile* temp = *projectiles.begin();
			projectiles.erase(projectiles.begin());
			delete temp;
	}

	

	platformsPassed += level->generateLevel(platforms, enemies, false);
}

void GameScene::draw()
{
	drawSprite(background, 0, 0);

	/*system("CLS");*/
	std::cout << "Platforms passed: " << platformsPassed << std::endl;
	std::cout << "Distance: " << movedDistance << std::endl;
	std::cout << "Lives: " << doodlerController->getDoodlerLives() << std::endl;


	for (size_t i = 0; i < platforms.size(); i++)
	{
		if (platforms[i]->getSpriteY() + platforms[i]->getSpriteHeight() < -5 * hRatio) // Optimizing drawing so platform which is out of screen won't be drawn
			continue;
		platforms[i]->draw();
	}

	doodlerController->draw();

	for(auto projectile : projectiles)
	{
		projectile->draw();
	}

	for (auto enemy : enemies)
	{
		if (enemy->getSpriteY() + enemy->getSpriteHeight() < -5 * hRatio) // Optimizing drawing so platform which is out of screen won't be drawn
			continue;
		enemy->draw();
	}

	for (size_t i = 0; i < abilities.size(); i++)
	{
		abilities[i]->draw();
	}
}


void GameScene::onKeyboardEvent(FRKey k, bool isReleased)
{
	if (isReleased)
		doodlerController->onKeyReleased(k);
	else
		doodlerController->onKeyPressed(k);
	
}

void GameScene::onMouseEvent(FRMouseButton button, bool isReleased)
{
	Projectile* project = nullptr;
	if (isReleased == false)
		project = doodlerController->onMouseEvent(button, mousePosX, mousePosY);

	if (project)
	{
		project->ScaleObjectProperties(wRatio, hRatio);
		projectiles.push_back(project);
	}
}

void GameScene::spawnAbility()
{

	if(abilities.size() >= platforms.size())
		return;

	Ability* ability = new Invincibility(Rectangle( -10, -10,
		Consts::ABILITY_WIDTH, Consts::ABILITY_HEIGHT), Consts::ABILITY_DURATION, Consts::ABILITY_SPRITE_PATH);
	
	ability->ScaleObjectProperties(wRatio, hRatio);

	int randomPlatform = rand() % platforms.size();

	for (int i = 0; i < abilities.size(); i++) // checking so platform won't have 2 abilities. But ability can be spawned on platform with enemy
	{
		if (abilities[i]->getBindedPlatform() == platforms[randomPlatform])
		{
            if(randomPlatform == platforms.size() - 1)
				randomPlatform = 0;
			else
				randomPlatform++;

			i = -1; // to start loop from beginning and check if another abillity is binded to platform randomPlatfrom
		}
	}

	ability->bindToPlatform(platforms[randomPlatform]);
	abilities.push_back(std::move(ability));

	abilitySpawned = true;

}

void GameScene::handleAbilityState()
{		
	if (playerJumpCount % 50 == 0 && playerJumpCount != 0 && !abilitySpawned)
	{
		spawnAbility();
	}
	else if (playerJumpCount % 50 != 0)
	{
		abilitySpawned = false;
	}
}

void GameScene::handleDoodlerState()
{
	if (doodlerController->getDoolerState() == DoodlerController::State::HIT && doodlerController->getDoodler()->getSpriteY() > wHeight)
	{
		auto lowestPlatform = std::max_element(platforms.begin(), platforms.end(),[](Platform* a, Platform* b) {return a->getSpriteY() < b->getSpriteY(); });

		if (!enemies.empty())
		{
			auto lowestEnemy = enemies.begin(); // first enemy always lowest because of level generation

			 // Find the lowest platform
			int enemyY = (*lowestEnemy)->getSpriteY() + (*lowestEnemy)->getCollisionHeight();
			int platformY = (*lowestPlatform)->getSpriteY();
			if (enemyY == platformY) // if enemyY == platformY. Means that enemy is on the platform and player will die
			{
				if(*lowestPlatform != platforms.back())
					lowestPlatform++; // next platform always higher than previous
				else
					lowestPlatform = platforms.begin(); // if it's last platform, then next platform is first
			}

			// There could be probability that 2 platforms in row would have enemies there
			// But it won't happen because to pass these platforms player must kill at least one enemy
		}
		

		doodlerController->spawnOnPlatform(*lowestPlatform);
	}
	else if (doodlerController->getDoolerState() == DoodlerController::State::DEAD)
	{
		state = Scene::State::GAME_OVER;
	}
}

void GameScene::handleEnemyState()
{
	for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++)
	{
		if ((*enemy)->getState() == Enemy::State::VANISHED)
		{
			auto temp = *enemy;
			enemies.erase(enemy);

			delete temp;
			break;
		}
	}
}

void GameScene::handleProjectileState()
{
	for (auto i = projectiles.begin(); i != projectiles.end(); i++)
	{
		if ((*i)->isLifeTimeOver())
		{
			Projectile* temp = *i;
			projectiles.erase(i);
			delete temp;
			break;
		}
	}
}

void GameScene::handleAllCollisions()
{
	doodlerController->isOutOfSideBoundaries(wWidth);
	doodlerController->isOutOfBotomBoundary(wHeight);

	for (size_t i = 0; i < platforms.size(); i++)
	{
		if (collided(doodlerController->getDoodler(), platforms[i]))
			if(doodlerController->onCollision(platforms[i]))
				++playerJumpCount;
	}


	for (auto enemy : enemies)
	{
		if (collided(doodlerController->getDoodler(), enemy))
			doodlerController->onCollision(enemy);

	}

	if(!projectiles.empty())
	for (auto enemy : enemies)
	{
		for (auto proj = projectiles.begin(); proj != projectiles.end(); proj++)
		{
			if (collided(enemy, *proj) && enemy->getState() == Enemy::State::ALIVE)
			{
					enemy->onCollision(*proj);

					auto tempProj = *proj;
					projectiles.erase(proj);
					delete tempProj;

					break;
			}
		}
	}

	for (auto proj : projectiles)
	{
		proj->isOutOfSidesScreen(wWidth);
	}

	for (size_t i = 0; i < abilities.size(); i++)
	{
		if (collided(abilities[i], doodlerController->getDoodler()))
		{
			doodlerController->onCollision(abilities[i]);
			abilitySpawned = false;
			delete abilities[i];
			abilities.erase(abilities.begin() + i);
			break;
		}
	}

	for (size_t i = 0; i < abilities.size(); i++)
	{
		if (abilities[i]->isOutOfBotomBoundary(wHeight) == true)
		{
			abilitySpawned = false;
			delete abilities[i];
			abilities.erase(abilities.begin() + i);
		}
	}
		
}

void GameScene::setMousePosition(float x, float y)
{
	mousePosX = x;
	mousePosY = y;
}


void GameScene::moveDown(float y)
{
	for (size_t i = 0; i < platforms.size(); i++)
	{
		platforms[i]->translateY(y);
	}

	for (auto enemy : enemies)
	{
		enemy->translateY(y);
	}

	for (auto projectile : projectiles)
	{
		projectile->translateY(y);
	}

	doodlerController->translateY(y);

	for (int i = 0; i < abilities.size(); i++)
	{
		abilities[i]->translateY(y);
	}

	movedDistance += y / hRatio; // Dividing by height ratio, so distance on every resolution would be the same

}

bool GameScene::collided(const GameObject* a, const GameObject* b) const
{
	if(a->getSpriteX() + a->getCollisionX() > b->getSpriteX() + b->getCollisionX() + b->getCollisionWidth() || 
		b->getSpriteX() + b->getCollisionX() > a->getSpriteX() + a->getCollisionX() + a->getCollisionWidth())
		return false;

	if (a->getSpriteY() + a->getCollisionY() > b->getSpriteY() + b->getCollisionY() + b->getCollisionHeight() ||
		b->getSpriteY() + b->getCollisionY() > a->getSpriteY() + a->getCollisionY() + a->getCollisionHeight())
		return false;

	return true;
}

