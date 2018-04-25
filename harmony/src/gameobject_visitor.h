#pragma once

class GameObject;
class Curve;
class ControlPoint;
class Model3D;

class GameObjectVisitor
{
public:
    virtual void visit(GameObject* gameObject) = 0;
    virtual void visit(Curve* curve) = 0;
    virtual void visit(ControlPoint* controlPoint) = 0;
    virtual void visit(Model3D* model3D) = 0;
};
