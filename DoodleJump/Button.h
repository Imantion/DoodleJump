#pragma once
#include "GameObject.h"

enum class FRMouseButton;

class Button :
    public GameObject
{
    using GameObject::GameObject;
public:
    bool isPressed(int x, int y,FRMouseButton) const;

    void update(float deltaTime) override;
    void draw() override;
    
};

