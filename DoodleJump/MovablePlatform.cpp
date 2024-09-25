#include "MovablePlatform.h"
#include "Framework.h"


MovablePlatform::MovablePlatform(const Rectangle& coll, const Rectangle& spriteRect, float moveDistance, float moveSpeed, const char* spritePath) :
	Platform(coll, spriteRect, spritePath)
{
	this->moveDistance = moveDistance;
	this->moveSpeed = moveSpeed;
	this->startY = spriteRectangle.y;
}

MovablePlatform::MovablePlatform(const Rectangle& spriteRect, float moveDistance, float moveSpeed, const char* spritePath) :
	Platform(spriteRect, spritePath)
{
	this->moveDistance = moveDistance;
	this->moveSpeed = moveSpeed;
	this->startY = spriteRectangle.y;
}



void MovablePlatform::update(float deltaTime)
{
	if (spriteRectangle.y >= startY + moveDistance + 1)
	{
		direction = Direction::UP;
		spriteRectangle.y = startY + moveDistance;
	}
	else if (spriteRectangle.y  <= this->startY - moveDistance - 1) 
	{
		direction = Direction::DOWN;
		spriteRectangle.y = startY - moveDistance;
	}

	spriteRectangle.y += moveSpeed * (int)direction * deltaTime;
}

void MovablePlatform::draw()
{
	drawSprite(sprite, spriteRectangle.x, spriteRectangle.y);
}

void MovablePlatform::translateY(float y)
{
	spriteRectangle.y += y;
	startY += y;
}

void MovablePlatform::setPosition(float x, float y)
{
	spriteRectangle.x = x;
	spriteRectangle.y = y;
	startY = y;
}

void MovablePlatform::setDirection(Direction direction_)
{
	direction = direction_;
}

float MovablePlatform::getMaximalY() const
{
	return startY - moveDistance;
}

float MovablePlatform::getMimimalY() const
{
	return startY + moveDistance;
}

float MovablePlatform::getMoveDistance() const
{
	return moveDistance;
}

bool MovablePlatform::checkForOverlap(const Platform* b) const
{
	if (this->getSpriteX() + this->getCollisionX() > b->getSpriteX() + b->getCollisionX() + b->getCollisionWidth() ||
		b->getSpriteX() + b->getCollisionX() > this->getSpriteX() + this->getCollisionX() + this->getCollisionWidth()) // Checkign if platforms are overlaping on x axis
		return false;

	if (this->getSpriteY() + this->moveDistance >= b->getMaximalY()) // checking if platforms are overlaping on y axis
		return true;

	return false;
}

void MovablePlatform::ScaleObjectProperties(float x, float y)
{
	Platform::ScaleObjectProperties(x, y);

	moveDistance *= y;
	moveSpeed *= y;
	startY *= y;
}

