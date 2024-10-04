#pragma once

#include <vector>
class GameObject;
class Sprite;
enum class FRKey;
enum class FRMouseButton;

class Scene
{
public:
	Scene(int window_width, int window_height);
	virtual ~Scene();

	virtual bool Init() = 0;
	virtual void onKeyboardEvent(FRKey k, bool isReleased) = 0;
	virtual void onMouseEvent(FRMouseButton button, bool isReleased) = 0;
	virtual void setMousePosition(float x, float y) = 0;

	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;



	enum class State
	{
		MAIN_MENU,
		START_GAME,
		PLAYING,
		GAME_OVER
	};


	State getSceneState() const;

protected:
	Sprite* background;
	State state;

	float mousePosX, mousePosY;
	int wWidth, wHeight; // window width and height
	float wRatio, hRatio; // window ratio. Used for scaling sprites and their speed
};

