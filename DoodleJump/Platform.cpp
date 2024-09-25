#include "Platform.h"

GameObject::CollisionType Platform::collisionType = GameObject::CollisionType::platform;

GameObject::CollisionType Platform::getCollisionType() const
{
	return collisionType;
}

float Platform::getMaximalY() const
{
	return spriteRectangle.y;
}

float Platform::getMimimalY() const
{
	return spriteRectangle.y;
}

bool Platform::checkForOverlap(const Platform* other) const
{
	return false;
}

