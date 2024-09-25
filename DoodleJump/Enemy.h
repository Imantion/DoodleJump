#pragma once
#include "GameObject.h"

class Platform;

class Enemy :
    public GameObject
{
public:
    using GameObject::GameObject;
    enum class State
    {
        ALIVE,
        DEAD,
        VANISHED
    };

    void update(float deltaTime) override;
	void draw() override;

    void bindToPlatform(const Platform* platform);

	void SetState(State state) { this->state = state; }
	State getState() const { return state; }

    void onCollision(const GameObject* other);
    void isOutOfBotomBoundary(int bottomBoundary);
    CollisionType getCollisionType() const override;

	private:
    static CollisionType collisionType;
    State state = State::ALIVE;

    float dieTimer = 0;

    bool isBindedToPlatform = false;
    const Platform* bindedPlatform = nullptr;
   
};

