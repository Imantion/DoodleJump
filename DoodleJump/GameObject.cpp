#include "GameObject.h"
#include "Framework.h"
#include <stdexcept>


GameObject::GameObject(const Rectangle& coll, const Rectangle& spriteRect, const char* spritePath) :
	collision(coll), spriteRectangle(spriteRect)
{
	if (collision.width <= 0 || collision.height <= 0 || spriteRectangle.width <= 0 || spriteRectangle.height <= 0)
	{
		throw std::invalid_argument("Width and height must be positive numbers");
	}

	sprite = createSprite(spritePath);
	setSpriteSize(sprite, spriteRectangle.width, spriteRectangle.height);

}



GameObject::GameObject(const Rectangle & spriteRect, const char* spritePath) : 
	GameObject(Rectangle(0,0, spriteRect.width, spriteRect.height), spriteRect, spritePath)
{
}


GameObject::CollisionType GameObject::getCollisionType() const
{
	return CollisionType::none;
}

void GameObject::setPosition(float x, float y)
{
	spriteRectangle.x = x;
	spriteRectangle.y = y;
}

float GameObject::getSpriteX() const
{
	return spriteRectangle.x;
}

float GameObject::getSpriteY() const
{
	return spriteRectangle.y;
}

int GameObject::getSpriteWidth() const
{
	return spriteRectangle.width;
}

int GameObject::getSpriteHeight() const
{
	return spriteRectangle.height;
}

float GameObject::getCollisionX() const
{
	return collision.x;
}

float GameObject::getCollisionY() const
{
	return collision.y;
}

int GameObject::getCollisionWidth() const
{
	return collision.width;
}

int GameObject::getCollisionHeight() const
{
	return collision.height;
}

void GameObject::translateY(float y)
{
	spriteRectangle.y += y;
}

void GameObject::ScaleObjectProperties(float x, float y)
{
	spriteRectangle.width *= x;
	spriteRectangle.height *= y;

	collision.x *= x;
	collision.y *= y;
	collision.width *= x;
	collision.height *= y;

	setSpriteSize(sprite, spriteRectangle.width, spriteRectangle.height);
}


GameObject::~GameObject()
{
	destroySprite(sprite);
}
