#pragma once

class GameObject;
class Doodler;
class Projectile;
class Platform;
class Ability;

enum class FRKey;
enum class FRMouseButton;

class DoodlerController
{
public:
	DoodlerController(Doodler* doodler, float doodlerSpeed, float doodlerJumpSpeed);
    virtual ~DoodlerController();

    enum class Direction
    {
        STAYING,
        LEFT,
        RIGHT 
    };

    enum class AbilityState
    {
        INVINCIBILITY,
        NONE,
    };

    enum class State
    {
        ALIVE,
        HIT,
        DEAD,
    };

    void update(float deltaTime);
    void draw();

    void onKeyPressed(FRKey k);
    void onKeyReleased(FRKey k);
    Projectile* onMouseEvent(FRMouseButton b, float x, float y);

    void isOutOfSideBoundaries(float x);
    bool isOutOfBotomBoundary(float y);

    void spawnOnPlatform(Platform* platform);
    bool onCollision(GameObject* collided); // Returns true if player jumped on collided object
   
    bool hitFromAbove(GameObject* collided);
    void translateY(float y);

    float getDoodlerJumpHeight();
    const Doodler* getDoodler() const;
    State getDoolerState() const;
    int getDoodlerLives() const;

    void ScaleObjectProperties(float x, float y);

private:

    void handleAbilityTimer(float deltaTime);
    void handleAbility(Ability* ability);

	Doodler* doodler;
    Direction direction;
    float doodlerSpeed;
    float doodlerJumpSpeed;
    int doodlerLives;
    float abilityTimer;
    float abilityDuration;

    State state;
    AbilityState abilityState;
};

