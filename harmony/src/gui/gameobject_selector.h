#pragma once
#include "selector.h"

class GameObjectSelector : public Selector
{
private:
    const std::string headerText = "Scene";
    const int xOffset = 2;
    const int yOffset = 2;

public:
    void setup();
};
