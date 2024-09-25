#include "Projectile.h"
#include "Framework.h"
#include "Consts.h"
#include <cmath>

GameObject::CollisionType Projectile::collisionType = GameObject::CollisionType::projectile;

Projectile::Projectile(const Rectangle& coll, float speed, float lifeTime, const char* spritePath) : 
	GameObject(coll, spritePath)
{
	this->speed = speed;
	this->lifeTime = lifeTime;

	this->lifeTimer = 0;
}

Projectile::Projectile(const Rectangle& coll, const Rectangle& spriteRect, float speed, float lifeTime, const char* spritePath) :
	GameObject(coll, spriteRect, spritePath)
{
	this->speed = speed;
	this->lifeTime = lifeTime;

	this->lifeTimer = 0;
}


void Projectile::isOutOfSidesScreen(int wWith)
{
	if (spriteRectangle.x + collision.x + collision.width < 0)
	{
		spriteRectangle.x = wWith - collision.x;
	}
	else if (spriteRectangle.x + 5 > wWith)
	{
		spriteRectangle.x = 5 - collision.width;
	}
}

void Projectile::update(float deltaTime)
{
	lifeTimer += deltaTime;

	spriteRectangle.x += velocity.x * deltaTime;
	spriteRectangle.y += velocity.y * deltaTime;

}

void Projectile::draw()
{
	drawSprite(sprite, spriteRectangle.x, spriteRectangle.y);
}

GameObject::CollisionType Projectile::getCollisionType() const
{
	return collisionType;
}

void Projectile::setVelocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
	velocity.normalize();
	velocity.x *= speed;
	velocity.y *= speed;
}

bool Projectile::isLifeTimeOver()
{
	return lifeTimer > lifeTime;
}

void Projectile::ScaleObjectProperties(float x, float y)
{
	GameObject::ScaleObjectProperties(x, y);

	speed *= x;

	float average = (x + y) / 2;
	velocity.x *= average;
	velocity.y *= average;
}

void Projectile::Vector2::normalize() {
	float length = std::sqrt(x * x + y * y);
	x /= length;
	y /= length;
}
