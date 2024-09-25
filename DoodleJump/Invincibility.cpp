#include "Invincibility.h"
#include "DoodlerController.h"
#include "Platform.h"
#include "Framework.h"


void Invincibility::update(float deltaTime)
{
	if (isBindedToPlatform)
	{
		spriteRectangle.y = platform->getSpriteY() - spriteRectangle.height;
		spriteRectangle.x = platform->getSpriteX() + platform->getSpriteWidth() / 2 - spriteRectangle.width / 2;
	}
}

void Invincibility::draw()
{
	drawSprite(sprite, spriteRectangle.x, spriteRectangle.y);
}

bool Invincibility::isOutOfBotomBoundary(int bottomBoundary)
{
	if (spriteRectangle.y > bottomBoundary)
	{
		return true;
	}
	if (spriteRectangle.y + spriteRectangle.height > bottomBoundary)
	{
		isBindedToPlatform = false;
		platform = nullptr;
	}
	return false;
}

void Invincibility::bindToPlatform(Platform* platform_)
{
	platform = platform_;
	isBindedToPlatform = true;
}


