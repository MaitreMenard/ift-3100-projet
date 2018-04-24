#pragma once
#include "selector.h"
#include "gameobject.h"
#include "gameobject_visitor.h"

class GameObjectSelector : public Selector<GameObject*>, public GameObjectVisitor
{
public:
    void setup();
    void visit(GameObject* gameObject);
    void visit(Curve* curve);

private:
    const std::string headerText = "Scene";
    const int xOffset = 2;
    const int yOffset = 2;
};
