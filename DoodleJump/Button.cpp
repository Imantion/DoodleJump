#include "Button.h"
#include "Framework.h"

bool Button::isPressed(int x, int y, FRMouseButton) const
{
    if (x >= spriteRectangle.x && x <= spriteRectangle.x + spriteRectangle.width &&
        y >= spriteRectangle.y && y <= spriteRectangle.y + spriteRectangle.height)
    {
		return true;
	}

    return false;
}

void Button::update(float deltaTime)
{
}

void Button::draw()
{
	drawSprite(sprite, spriteRectangle.x, spriteRectangle.y);
}
