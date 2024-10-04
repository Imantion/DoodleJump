#pragma once
#include "Rectangle.h"

class Sprite;



class GameObject
{
public:
	GameObject(const Rectangle& coll,const Rectangle& spriteRect, const char* spritePath);
	GameObject(const Rectangle& spriteRect, const char* spritePath);
	virtual ~GameObject();

	enum class CollisionType
	{
		doodler,
		platform,
		enemy,
		projectile,
		ability,
		none
	};

	virtual void update(float deltatime) = 0;	
	virtual void draw() = 0;
	virtual CollisionType getCollisionType() const;

	virtual void setPosition(float x, float y);

	virtual float getSpriteX() const;
	virtual float getSpriteY() const;
	int getSpriteWidth() const;
	int getSpriteHeight() const;

	float getCollisionX() const; // Positon are relative to the sprite
	float getCollisionY() const; // Positon are relative to the sprite
	int getCollisionWidth() const;
	int getCollisionHeight() const;

	virtual void translateY(float y);

	virtual void ScaleObjectProperties(float x, float y);
	

protected:

	Rectangle spriteRectangle; // rectangle that is used to draw the sprite.
	Rectangle collision; // rectangle that is used for collision detection. X and Y are the coordinates relative to the sprite

	Sprite* sprite;

};

