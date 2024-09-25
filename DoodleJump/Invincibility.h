#pragma once
#include "Ability.h"


class Platform;

class Invincibility:
	public Ability
{
public:
	using Ability::Ability;

	void update(float deltaTime) override;
	void draw() override;

	bool isOutOfBotomBoundary(int bottomBoundary) override;

	void bindToPlatform(Platform* platform_) override;

};

