#include "gameobject_selector.h"

void GameObjectSelector::setup()
{
    Selector::setup(headerText);

    panel.setPosition(xOffset, yOffset);
}
