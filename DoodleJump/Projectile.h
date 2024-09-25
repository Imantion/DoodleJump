#pragma once
#include "GameObject.h"


class Projectile :
    public GameObject
{
public:
	Projectile() = default;

	Projectile(const Rectangle& coll, float speed, float lifeTime, const char* spritePath);
	Projectile(const Rectangle& coll,const Rectangle& spriteRect, float speed, float lifeTime, const char* spritePath);

	void update(float deltaTime) override;
	void draw() override;
	CollisionType getCollisionType() const override;

	void setVelocity(float x, float y);
	void isOutOfSidesScreen(int wWidth);
	bool isLifeTimeOver();

	void ScaleObjectProperties(float x, float y) override;

private:
	static CollisionType collisionType;

	float speed;
	float lifeTime;
	float lifeTimer;

	struct Vector2
	{
		Vector2() = default;
		float x;
		float y;
		void normalize();
	} velocity;
	
};

