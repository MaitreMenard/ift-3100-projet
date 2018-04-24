#pragma once

class GameObject;
class Curve;

class GameObjectVisitor
{
public:
    virtual void visit(GameObject* gameObject) = 0;
    virtual void visit(Curve* curve) = 0;
};
