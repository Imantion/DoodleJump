#include "Scene.h"
#include "GameObject.h"
#include "Consts.h"
#include "Framework.h"


Scene::Scene(int window_width, int window_height)
{
	wWidth = window_width;
	wHeight = window_height;
	wRatio = (float)wWidth / (float)Consts::WIN_WIDTH;
	hRatio = (float)wHeight / (float)Consts::WIN_HEIGHT;
}

Scene::~Scene()
{
	destroySprite(background);
}


Scene::State Scene::getSceneState() const
{
	return state;
}
