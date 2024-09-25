#include "DoodlerController.h"
#include "Doodler.h"
#include "Ability.h"
#include "Platform.h"
#include "Enemy.h"
#include "Framework.h"

DoodlerController::DoodlerController(Doodler* doodler_, float doodlerSpeed_, float doodlerJumpSpeed_)
{
	doodler = doodler_;
	doodlerSpeed = doodlerSpeed_;
	doodlerJumpSpeed = doodlerJumpSpeed_;
	doodlerLives = 5;
	direction = Direction::STAYING;
	state = State::ALIVE;
	abilityState = AbilityState::INVINCIBILITY;
}

DoodlerController::~DoodlerController()
{
	delete doodler;
}

void DoodlerController::update(float dt)
{
	doodler->update(dt);
	handleAbilityTimer(dt);
}

void DoodlerController::draw()
{
	doodler->draw();
}

void DoodlerController::onKeyReleased(FRKey k)
{
	if(state != State::ALIVE)
		return;

	if (k == FRKey::RIGHT && direction == Direction::RIGHT)
	{
		direction = Direction::STAYING;
		doodler->setVelocityX(0);
	}
	else if (k == FRKey::LEFT && direction == Direction::LEFT)
	{
		direction = Direction::STAYING;
		doodler->setVelocityX(0);
	}
}

void DoodlerController::onKeyPressed(FRKey k)
{
	if (state != State::ALIVE)
		return;

	if (k == FRKey::RIGHT)
	{
		direction = Direction::RIGHT;
		doodler->setVelocityX(doodlerSpeed);
	}
	else if (k == FRKey::LEFT)
	{
		direction = Direction::LEFT;
		doodler->setVelocityX(-doodlerSpeed);
	}

}

Projectile* DoodlerController::onMouseEvent(FRMouseButton b, float x, float y)
{
	if (state != State::ALIVE)
		return nullptr;

	if (b == FRMouseButton::LEFT)
	{
		return doodler->shoot(x, y);
	}

	return nullptr;
}

void DoodlerController::isOutOfSideBoundaries(float x)
{
	if (doodler->getSpriteX() + doodler->getCollisionX() + doodler->getSpriteWidth() < 0)
	{
		doodler->setPosition(x - doodler->getCollisionX() - 5, doodler->getSpriteY());
	}
	else if (doodler->getSpriteX() + doodler->getCollisionX() + 5 > x)
	{
		doodler->setPosition(5 - doodler->getSpriteWidth(), doodler->getSpriteY());
	}
}

bool DoodlerController::isOutOfBotomBoundary(float y)
{
	bool fall = doodler->getSpriteY() > y;
	if (fall)
	{
		--doodlerLives;
		state = doodlerLives <= 0 ? State::DEAD : State::HIT;

		abilityState = AbilityState::NONE;
	}
	
	return fall;
}

bool DoodlerController::hitFromAbove(GameObject* collided)
{
	float yCheck = doodler->getSpriteY() + doodler->getCollisionY() + doodler->getCollisionHeight() - collided->getSpriteY() - collided->getCollisionY();
	if (doodler->getVelocityY() >= 0 && yCheck <= 20 && yCheck >= 0)
	{
		return true;
	}
	return false;
}

void DoodlerController::spawnOnPlatform(Platform* platform)
{
	doodler->jump(0); // reseting velocity

	doodler->setPosition(platform->getSpriteX() + platform->getCollisionX() + platform->getCollisionWidth() / 2,
		platform->getSpriteY() + platform->getCollisionY() - doodler->getCollisionY() - doodler->getCollisionHeight() - platform->getCollisionHeight() * 0.1);

	state = State::ALIVE;
	direction = Direction::STAYING;
	doodler->setVelocityX(0);
}

float DoodlerController::getDoodlerJumpHeight() 
{
	return doodlerJumpSpeed * doodlerJumpSpeed / (2 * doodler->getfallSpeed()); // The height of an object in physics is determined by its gravitational potential energy and its kinetic energy.
}

bool DoodlerController::onCollision(GameObject* collided)
{
	if (state != State::ALIVE)
		return false;

	switch (collided->getCollisionType())
	{
	case GameObject::CollisionType::platform:
		if (hitFromAbove(collided))
		{
			doodler->jump(doodlerJumpSpeed);
			return true;
		}
		break;
	case GameObject::CollisionType::enemy:
		{
			Enemy* enemy = static_cast<Enemy*>(collided); // don't use dynamic_cast because it's slower than static. And there is for sure enemy
			if (enemy->getState() == Enemy::State::ALIVE)
			{
				if (hitFromAbove(collided))
				{
					doodler->jump(doodlerJumpSpeed);
					enemy->onCollision(doodler);
					return true;
				}
				else if (abilityState != DoodlerController::AbilityState::INVINCIBILITY)
				{
					--doodlerLives;
					state = doodlerLives <= 0 ? State::DEAD : State::HIT;

					abilityState = AbilityState::NONE;
				}
			}
		}
	case GameObject::CollisionType::ability:
		{
			Ability* ability = static_cast<Ability*>(collided); // Same as above
			handleAbility(ability);
		}
		break;
	default:
		break;
	}

	return false;
}

const Doodler* DoodlerController::getDoodler() const
{
	return doodler;
}

int DoodlerController::getDoodlerLives() const
{
	return doodlerLives;
}


DoodlerController::State DoodlerController::getDoolerState() const
{
	return state;
}

void DoodlerController::translateY(float y)
{
	doodler->translateY(y);
}


void DoodlerController::ScaleObjectProperties(float x, float y)
{
	doodler->ScaleObjectProperties(x, y);
	doodlerSpeed *= x;
	doodlerJumpSpeed *= y;
}

void DoodlerController::handleAbilityTimer(float deltaTime)
{
	if(abilityTimer >= abilityDuration)
		abilityState = AbilityState::NONE;

	if(abilityState != AbilityState::NONE)
		abilityTimer += deltaTime;
}

void DoodlerController::handleAbility(Ability* ability)
{
	switch (ability->getAbilityType())
	{
		case Ability::AbilityType::INVINCIBILITY:
			abilityState = AbilityState::INVINCIBILITY;
			abilityDuration = ability->getDuration();
			abilityTimer = 0;
			break;
	default:
		break;
	}
}
