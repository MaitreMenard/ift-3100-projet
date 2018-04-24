#include "gameobject_selector.h"

void GameObjectSelector::setup()
{
    Selector::setup(headerText);

    panel.setPosition(xOffset, yOffset);
}

void GameObjectSelector::visit(GameObject * gameObject)
{
    //todo
}

void GameObjectSelector::visit(Curve * curve)
{
    //todo
}
