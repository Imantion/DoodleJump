#include "Ability.h"

Ability::Ability(Rectangle spriteRect, float duration_, const char* spritePath)
	: GameObject(spriteRect, spritePath), duration(duration_)
{
}

Platform* Ability::getBindedPlatform() const
{
	return platform;
}

float Ability::getDuration() const
{
	return duration;
}

Ability::AbilityType Ability::getAbilityType() const
{
	return effect;
}

GameObject::CollisionType Ability::getCollisionType() const
{
	return collisionType;
}

GameObject::CollisionType Ability::collisionType = GameObject::CollisionType::ability;