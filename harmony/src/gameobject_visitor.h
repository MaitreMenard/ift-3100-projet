#pragma once
#include "gameobject.h"
#include "gameobjects/curve.h"

class GameObjectVisitor
{
public:
    virtual void visit(GameObject* gameObject) = 0;
    virtual void visit(Curve* curve) = 0;
};
