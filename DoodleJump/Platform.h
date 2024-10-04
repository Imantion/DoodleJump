#pragma once
#include "GameObject.h"

class Platform :
    public GameObject
{    
public:
    using GameObject::GameObject;

    CollisionType getCollisionType() const override;

   virtual float getMaximalY() const; // maximum Y which platform can be located on;
   virtual float getMimimalY() const; // minimum Y which platform can be located on;

   virtual bool checkForOverlap(const Platform* other) const;

protected:
    static CollisionType collisionType;
};