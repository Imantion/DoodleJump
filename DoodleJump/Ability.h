#pragma once
#include "GameObject.h"

class DoodlerController;
class Platform;

class Ability :
    public GameObject
{
public:


    enum class AbilityType
    {
        INVINCIBILITY,
        NONE
    };

    Ability(Rectangle spriteRect, float duration, const char* spritePath);

    virtual bool isOutOfBotomBoundary(int bottomBoundary) = 0;
    virtual void bindToPlatform(Platform* platform_) = 0;

    Platform* getBindedPlatform() const;
    float getDuration() const;
    AbilityType getAbilityType() const;
    GameObject::CollisionType getCollisionType() const override;

protected:
    static GameObject::CollisionType collisionType;
    Platform* platform; // Because ability can spawn on moving platform. It is needed to bind ability to platform
    bool isBindedToPlatform = false;
    float duration;
    AbilityType effect;
};

