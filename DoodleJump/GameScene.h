#pragma once
#include "Scene.h"
#include <list>
#include <vector>

class DoodlerController;
class Platform;
class Enemy;
class GameObejct;
class Projectile;
class Level;
class Sprite;
class Ability;

enum class FRKey;
enum class FRMouseButton;

class GameScene :
	public Scene
{
public:
	GameScene(int windowWidth, int windowHeight);
	~GameScene();

	bool Init() override;

	void update(float deltaTime) override;
	void draw() override;

	void onKeyboardEvent(FRKey k, bool isReleased) override;
	void onMouseEvent(FRMouseButton button, bool isReleased) override;
	void setMousePosition(float x, float y) override;
	
	
	

private:

	void spawnAbility();
	void handleAbilityState();
	void handleDoodlerState();
	void handleEnemyState();
	void handleProjectileState();
	void handleAllCollisions();
	void moveDown(float y);
	bool collided(const GameObject* a, const GameObject* b) const;

	DoodlerController* doodlerController;
	Level* level;

	std::vector<Platform*> platforms;
	std::list<Enemy*> enemies;
	std::list<Projectile*> projectiles;
	std::vector<Ability*> abilities; // Not list because there is only one ability at a time
	bool abilitySpawned;



	int movedDistance;
	int playerJumpCount;
	int platformsPassed;
	int platformsAmount;
};

