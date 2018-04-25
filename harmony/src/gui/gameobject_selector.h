#pragma once
#include "selector.h"
#include "gameobject.h"
#include "gameobject_visitor.h"
#include "gameobjects/curve.h"
#include "gameobjects/controlpoint.h"

class GameObjectSelector : public Selector<GameObject*>, public GameObjectVisitor
{
public:
    void setup();
    void visit(GameObject* gameObject);
    void visit(Curve* curve);
    void addControlPoint(Curve* curve, ControlPoint* controlPoint);

private:
    const std::string headerText = "Scene";
    const int xOffset = 2;
    const int yOffset = 2;
};
