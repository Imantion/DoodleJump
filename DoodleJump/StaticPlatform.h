#pragma once
#include "Platform.h"
class StaticPlatform :
    public Platform
{
    using Platform::Platform;
public:
    void update(float deltaTime) override {}
    void draw() override;
};

