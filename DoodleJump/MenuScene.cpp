#include "MenuScene.h"
#include "Consts.h"
#include "Framework.h"
#include "Doodler.h"
#include "Button.h"
#include <iostream>

MenuScene::~MenuScene()
{
	delete playButton;
	delete doodler;
}

bool MenuScene::Init()
{
	playButton = new Button(Rectangle((wWidth * 0.9  - Consts::Button_WIDTH * wRatio), (wHeight - Consts::Button_HEIGHT * hRatio) / 1.28, Consts::Button_WIDTH, Consts::Button_HEIGHT),
							Consts::PLAY_BUTTON_SPRITE_PATH);
	playButton->ScaleObjectProperties(wRatio, hRatio);

	 doodler = new Doodler(Rectangle(wWidth / 9.14 , wHeight / 1.28 - 62 * hRatio, 62, 60), Consts::GRAVITY, // 9.14 and 1.28 are magic numbers. They are used to calculate the position of the platform
		Consts::DOODLER_SPRITE_LEFT_PATH, Consts::DOODLER_SPRITE_LEFT_PATH);

	 doodler->ScaleObjectProperties(wRatio, hRatio);

	background = createSprite(Consts::MENU_BACKGROUND_SPRITE_PATH);
	setSpriteSize(background, wWidth, wHeight);

	return true;
}

void MenuScene::update(float deltaTime)
{
	if (doodler->getSpriteY() + doodler->getSpriteHeight() > wHeight / 1.28)
	{
		doodler->jump(Consts::JUMP_VELOCITY * hRatio);
	}

	doodler->update(deltaTime);
}

void MenuScene::draw()
{
	drawSprite(background, 0, 0);
	playButton->draw();
	doodler->draw();
}

void MenuScene::onKeyboardEvent(FRKey k, bool isReleased)
{
}

void MenuScene::onMouseEvent(FRMouseButton button, bool isReleased)
{
	if (!isReleased)
	{
		if (playButton->isPressed(mousePosX, mousePosY, button))
		{
			state = State::START_GAME;
		}
	}
	
}

void MenuScene::setMousePosition(float x, float y)
{
	mousePosX = x;
	mousePosY = y;
}
