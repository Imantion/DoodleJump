#pragma once
#include "Platform.h"
class MovablePlatform :
    public Platform
{
public:
	enum class Direction
	{
		UP = -1,
		DOWN = 1
	};

	MovablePlatform(const Rectangle& coll, const Rectangle& spriteRect, float moveDistance, float moveSpeed, const char* spritePath);
	MovablePlatform(const Rectangle& spriteRect, float moveDistance, float moveSpeed, const char* spritePath);

	void update(float deltaTime) override;
	void draw() override;

	void translateY(float y) override;
	void setPosition(float x, float y) override;
	void setDirection(Direction direction);

	float getMaximalY() const override;
	float getMimimalY() const override;
	float getMoveDistance() const;

	bool checkForOverlap(const Platform* otherPlatform) const override; // checkin if overlaping platform

	void ScaleObjectProperties(float x, float y) override;
private:
	float moveSpeed;
	float moveDistance; // distance to move up and down
	float startY; // starting y position

    Direction direction = Direction::DOWN;
};

