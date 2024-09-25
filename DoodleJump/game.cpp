#include "Framework.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "Consts.h"
#include "SceneManager.h"



class Game : public Framework {

public:

	Game(int wWidth, int wHeight):
		sceneManager(wWidth, wHeight)
	{
	}

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = sceneManager.getWindowWidth();
		height = sceneManager.getWindowHeight();
		fullscreen = false;
	}

	virtual bool Init() {

		sceneManager.Init();
		showCursor(true);
		return true;
	}

	virtual void Close() {

	}

	virtual bool Tick() {

		sceneManager.sceneChangeHandler();
		
		deltaTime = (turn + 1) > 2 ? 16 : 17;
		lag += currTime - prevTime;
		prevTime = currTime;

		if (lag > deltaTime * MAX_LAG_UPDATE) lag = deltaTime * MAX_LAG_UPDATE;

		while (lag >= deltaTime) {
			lag -= deltaTime;
			deltaTime = (++turn) > 2 ? (turn = 0, 16) : 17;
			
			sceneManager.getCurrentScene()->update(deltaTime);
		}

		
		sceneManager.getCurrentScene()->draw();
		

		
		currTime = getTickCount();
		// delay time for 60fps: (17/17/16 ms delay) - (time passed for game update)
		int delayTime = deltaTime - (currTime - prevTime);
		if (delayTime < 0) delayTime = 0;
		currTime += delayTime;
		timer += deltaTime;

		std::this_thread::sleep_for(std::chrono::milliseconds(delayTime));
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		sceneManager.getCurrentScene()->setMousePosition(x, y);
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		sceneManager.getCurrentScene()->onMouseEvent(button, isReleased);
	}

	virtual void onKeyPressed(FRKey k) {
		sceneManager.getCurrentScene()->onKeyboardEvent(k, false);
	}

	virtual void onKeyReleased(FRKey k) {
		sceneManager.getCurrentScene()->onKeyboardEvent(k, true);
	}
	
	virtual const char* GetTitle() override
	{
		return "Doodle Jump";
	}

private:
	SceneManager sceneManager;

	// Variables below used for setting FPS limit to 60
	int timer = 0;
	unsigned turn = 0;
	unsigned lag = 0;
	const int MAX_LAG_UPDATE = 1000;
	unsigned prevTime = 0;
	unsigned currTime = 0;
	unsigned deltaTime = 0;
};

int main(int argc, char *argv[])
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));


	int windowWidth = Consts::WIN_WIDTH;
	int windowHeight = Consts::WIN_HEIGHT;
	
	if (argc > 1) 
	{
		for (int i = 1; i < argc; ++i) {
			if (std::string(argv[i]) == "-window" && i + 1 < argc) 
			{
				if (sscanf_s(argv[2], "%ds%d", &windowWidth, &windowHeight) != 2)
				{
					std::cerr << "Invalid window size format. Use default values" << std::endl;
					int windowWidth = Consts::WIN_WIDTH;
					int windowHeight = Consts::WIN_HEIGHT;
				}
			}
		}
	}

	return run(new Game(windowWidth, windowHeight));
}
