#pragma once
#include "GameObject.h"

class Projectile;

class Doodler : // Probably it should be controlled by DoodlerController but not by Game class
    public GameObject
{
public:
    Doodler(const Rectangle& coll, const Rectangle& spriteRect, float fallSpeed, const char* leftSpritePath, const char* rightSpritePath);
    Doodler(const Rectangle& spriteRect, float fallSpeed, const char* leftSpritePath, const char* rightSpritePath);
 

   
    void update(float deltatime) override;
    void draw() override;
    CollisionType getCollisionType() const override;

    bool isDead() const;
    void jump(float jumpVelocity);
    Projectile* shoot(float shootPointX, float shootPointY);

    void hitFromAbove(GameObject* collided);

    void setVelocityX(float vx);
    void setPosition(float x, float y);
    float getVelocityY();
    float getfallSpeed();

    void ScaleObjectProperties(float x, float y) override;

    virtual ~Doodler();

private:
    static CollisionType collisionType;

    int lifesAmount;
    float vx;
    float vy;
    float fallSpeed;

    Sprite* leftSprite; // Sprite for left direction
    Sprite* rightSprite; // Sprite for right direction
};

