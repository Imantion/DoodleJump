#include "GameOverScene.h"
#include "Framework.h"
#include "Button.h"
#include "Consts.h"

GameOverScene::~GameOverScene()
{
	delete playAgainButton;
}

bool GameOverScene::Init()
{
	playAgainButton = new Button(Rectangle((wWidth - Consts::Button_WIDTH * wRatio) / 2, (wHeight - Consts::Button_HEIGHT * hRatio) / 2, Consts::Button_WIDTH, Consts::Button_HEIGHT),
		Consts::PLAY_AGAIN_BUTTON_SPRITE_PATH);
	playAgainButton->ScaleObjectProperties(wRatio, hRatio);

	background = createSprite(Consts::BACKGROUND_SPRITE_PATH);
	setSpriteSize(background, wWidth, wHeight);

	return true;
}

void GameOverScene::update(float deltaTime)
{
}

void GameOverScene::draw()
{
	drawSprite(background, 0, 0);
	playAgainButton->draw();
}

void GameOverScene::onKeyboardEvent(FRKey k, bool isReleased)
{
}

void GameOverScene::onMouseEvent(FRMouseButton button, bool isReleased)
{
	if (!isReleased)
	{
		if (playAgainButton->isPressed(mousePosX, mousePosY, button))
		{
			state = State::START_GAME;
		}
	}

}

void GameOverScene::setMousePosition(float x, float y)
{
	mousePosX = x;
	mousePosY = y;
}