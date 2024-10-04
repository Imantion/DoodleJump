#pragma once
#include "Scene.h"

class Button;

class GameOverScene :
    public Scene
{
	using Scene::Scene;
public:

	virtual ~GameOverScene();

	bool Init() override;
	void update(float deltaTime) override;
	void draw() override;

	void onKeyboardEvent(FRKey k, bool isReleased) override;
	void onMouseEvent(FRMouseButton button, bool isReleased) override;
	void setMousePosition(float x, float y) override;

private:

	Button* playAgainButton;
};

