#include "SceneManager.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "GameOverScene.h"

SceneManager::SceneManager(int window_width, int window_height)
{
	wWidth = window_width;
	wHeight = window_height;
}

SceneManager::~SceneManager()
{
    delete currentScene;
}

void SceneManager::Init()
{
	currentScene = new MenuScene(wWidth, wHeight);
	currentScene->Init();
	previousState = currentScene->getSceneState();
}

bool SceneManager::sceneChangeHandler()
{
		Scene::State currentState = currentScene->getSceneState();
		if (previousState != currentState)
		{
			delete currentScene;
			currentScene = nullptr;
		}
		else
			return false;

		switch (currentState)
		{
		case Scene::State::MAIN_MENU:
			currentScene = new MenuScene(wWidth, wHeight);
			break;
		case Scene::State::START_GAME:
			currentScene = new GameScene(wWidth, wHeight);
			break;
		case Scene::State::GAME_OVER:
			currentScene = new GameOverScene(wWidth, wHeight);
			break;
		default:
			break;
		}

		currentScene->Init();
		previousState = currentScene->getSceneState();
		return true;
}

Scene* SceneManager::getCurrentScene()
{
	return currentScene;
}
