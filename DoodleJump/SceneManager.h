#pragma once
#include "Scene.h"

class SceneManager
{
public:
	SceneManager(int window_width,int window_height);
	~SceneManager();

	void Init();

	bool sceneChangeHandler(); // returns true if scene has changed
	Scene* getCurrentScene();

	int getWindowWidth() const { return wWidth; }
	int getWindowHeight() const { return wHeight; }


private:
	Scene* currentScene;
	int wWidth, wHeight;

	Scene::State previousState;
};

