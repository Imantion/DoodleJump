#include "Enemy.h"
#include "Platform.h"
#include "Framework.h"


GameObject::CollisionType  Enemy::collisionType = GameObject::CollisionType::enemy;

void Enemy::update(float deltaTime)
{
	if (state == State::ALIVE && isBindedToPlatform /*&& bindedPlatform != nullptr*/)
	{
		spriteRectangle.y = bindedPlatform->getSpriteY() - spriteRectangle.height;
		spriteRectangle.x = bindedPlatform->getSpriteX() + bindedPlatform->getSpriteWidth() * 0.08;
	}
	else if (state == State::DEAD)
	{
		spriteRectangle.y += deltaTime * 0.4;
		dieTimer += deltaTime;
		if (dieTimer > 2000)
			state = State::VANISHED;
	}
}

void Enemy::draw()
{
	if (state != State::VANISHED)
	{
		drawSprite(sprite, spriteRectangle.x, spriteRectangle.y);
	}
}

void Enemy::bindToPlatform(const Platform* platform)
{
	isBindedToPlatform = true;
	bindedPlatform = platform;

	spriteRectangle.y = bindedPlatform->getSpriteY() - spriteRectangle.height;
	spriteRectangle.x = bindedPlatform->getSpriteX() + bindedPlatform->getSpriteWidth() * 0.08;
}

void Enemy::onCollision(const GameObject* other)
{
	
	if (other->getCollisionType() == GameObject::CollisionType::projectile ||
		other->getCollisionType() == GameObject::CollisionType::doodler)
	{
		state = State::DEAD;
		isBindedToPlatform = false;
	}
}

void Enemy::isOutOfBotomBoundary(int bottomBoundary)
{
	if (spriteRectangle.y > bottomBoundary)
	{
		state = State::VANISHED;
	}
	if (spriteRectangle.y + spriteRectangle.height > bottomBoundary)
	{
		isBindedToPlatform = false;
		bindedPlatform = nullptr;
	}
}

GameObject::CollisionType Enemy::getCollisionType() const
{
	return collisionType;
}
