#include "Doodler.h"
#include "Projectile.h"
#include "Consts.h"
#include "Framework.h"


GameObject::CollisionType Doodler::collisionType = GameObject::CollisionType::doodler; // Static variable initialization

Doodler::Doodler(const Rectangle& coll, const Rectangle& spriteRect, float fallSpeed, const char* leftSpritePath, const char* rightSpritePath) :
	GameObject(coll, spriteRect, leftSpritePath)
{

	this->leftSprite = sprite; // By default sprite is left sprite, that's why leftSprite is pointing to sprite address
	this->rightSprite = createSprite(rightSpritePath);
	setSpriteSize(rightSprite, spriteRect.width, spriteRect.height); // In base constuctor sprite variable size is set to spriteWidth and spriteHeight
																	 // So, we need to set size of rightSprite to the same values
	this->lifesAmount = 5;
	this->fallSpeed = fallSpeed;
	this->vx = this->vy = 0;
}

Doodler::Doodler(const Rectangle& spriteRect, float fallSpeed, const char* leftSpritePath, const char* rightSpritePath) :
	Doodler(Rectangle(0, 0, spriteRect.width, spriteRect.height), spriteRect, fallSpeed, leftSpritePath, rightSpritePath)
{
}



void Doodler::setVelocityX(float vx)
{
	this->vx = vx;
}

void Doodler::setPosition(float x, float y)
{
	spriteRectangle.x = x;
	spriteRectangle.y = y;
}

float Doodler::getVelocityY()
{
	return vy;
}

float Doodler::getfallSpeed()
{
	return fallSpeed;
}

void Doodler::ScaleObjectProperties(float x, float y)
{
	GameObject::ScaleObjectProperties(x, y);

	fallSpeed *= y;
	setSpriteSize(rightSprite, spriteRectangle.width, spriteRectangle.height);
}

void Doodler::update(float deltatime)
{
	vy += fallSpeed * deltatime; // Gravity is added to velocity
	spriteRectangle.y += vy * deltatime; // Velocity is added to position
    
	spriteRectangle.x += vx * deltatime;

}

void Doodler::draw()
{
	if (vx < 0) // Depending on player direction, different sprite will be drawn
	{
		sprite = leftSprite;
	}
	else if (vx > 0)
	{
		sprite = rightSprite;
	}
	
	drawSprite(sprite, spriteRectangle.x, spriteRectangle.y);
}

GameObject::CollisionType Doodler::getCollisionType() const
{
	return collisionType;
}


bool Doodler::isDead() const
{
    return lifesAmount <= 0;
}


void Doodler::jump(float jumpVelocity)
{
	vy = -jumpVelocity;
}


void Doodler::hitFromAbove(GameObject* collided)
{
	if (vy >= 0 && spriteRectangle.y + collision.y + collision.height - collided->getSpriteY() - collided->getCollisionY() <= 20)
	{
		/*jump();*/
	}
}

Projectile* Doodler::shoot(float shootPointX, float shootPointY)
{
	// I wanted to implement shoot animation. Considiring that doodler had is semi-sphere shape
	// and knowing angle of shoot, I could calculate the point on the doodler's head, where nose should be spawned

	float doodlerCenter = spriteRectangle.x + spriteRectangle.width * 0.5;
	float velocityX = shootPointX - doodlerCenter;
	float velocityY = shootPointY - spriteRectangle.y;

	if (velocityY >= 0) // that means that shoot point is under doodler
	{
		return nullptr;
	}

	Projectile* projectile = new Projectile(Rectangle(doodlerCenter, spriteRectangle.y, Consts::PROJECTILE_WIDTH, Consts::PROJECTILE_HEIGHT),Consts::PROJECTILE_SPEED,
		Consts::PROJECTILE_LIFETIME, Consts::PROJECTILE_SPRITE_PATH);

	projectile->setVelocity(velocityX, velocityY);

	return projectile;
}

Doodler::~Doodler()
{
	destroySprite(rightSprite); // Destroying only rightSprite, because leftSprite is destroyed in base class destructor
	sprite = leftSprite; // Setting sprite to leftSprite, because it's used in base class destructor
}
