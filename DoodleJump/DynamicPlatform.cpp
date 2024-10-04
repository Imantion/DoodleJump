#include "DynamicPlatform.h"
#include "Framework.h"

DynamicPlatform::DynamicPlatform(const Rectangle& coll, const Rectangle& spriteRect, float moveDistance, float moveSpeed, const char* spritePath):
	Platform(coll, spriteRect, spritePath)
{
	this->moveDistance = moveDistance;
	this->moveSpeed = moveSpeed;
	this->startY = spriteRectangle.y;
}

DynamicPlatform::DynamicPlatform(const Rectangle& spriteRect, float moveDistance, float moveSpeed, const char* spritePath):
	Platform(spriteRect, spritePath)
{
	this->moveDistance = moveDistance;
	this->moveSpeed = moveSpeed;
	this->startY = spriteRectangle.y;
}


void DynamicPlatform::update(float deltaTime)
{
	if (shouldMove)
	{
		if (spriteRectangle.y >= startY + moveDistance + 1)
		{
			direction = Direction::UP;
			spriteRectangle.y = startY + moveDistance;
		}
		else if (spriteRectangle.y <= this->startY - moveDistance - 1)
		{
			direction = Direction::DOWN;
			spriteRectangle.y = startY - moveDistance;
		}

		spriteRectangle.y += moveSpeed * (int)direction * deltaTime;
	}
}

void DynamicPlatform::draw()
{
	drawSprite(sprite, spriteRectangle.x, spriteRectangle.y);
}

void DynamicPlatform::translateY(float y)
{
	spriteRectangle.y += y;
	startY += y;
}

void DynamicPlatform::setPosition(float x, float y)
{
	spriteRectangle.x = x;
	spriteRectangle.y = y;
	startY = y;
}

void DynamicPlatform::setDirection(Direction direction_)
{
	direction = direction_;
}

void DynamicPlatform::setMove(bool move)
{
	shouldMove = move;
}

float DynamicPlatform::getMaximalY() const
{
	if(shouldMove)
		return startY - moveDistance;

	return startY;
}

float DynamicPlatform::getMimimalY() const
{
	if(shouldMove)
		return startY + moveDistance;
	return startY;
}

float DynamicPlatform::getMoveDistance() const
{
	return moveDistance;
}

bool DynamicPlatform::checkForOverlap(const Platform* b) const
{
	if (this->getSpriteX() + this->getCollisionX() > b->getSpriteX() + b->getCollisionX() + b->getCollisionWidth() ||
		b->getSpriteX() + b->getCollisionX() > this->getSpriteX() + this->getCollisionX() + this->getCollisionWidth()) // Checkign if platforms are overlaping on x axis
		return false;

	if (this->getSpriteY() + this->moveDistance >= b->getMaximalY()) // checking if platforms are overlaping on y axis
		return true;

	return false;
}

void DynamicPlatform::ScaleObjectProperties(float x, float y)
{
	Platform::ScaleObjectProperties(x, y);

	moveDistance *= y;
	moveSpeed *= y;
}

