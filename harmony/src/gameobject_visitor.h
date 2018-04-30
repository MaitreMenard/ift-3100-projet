#pragma once

class GameObject;
class Curve;
class BezierCurve;
class ControlPoint;
class Model3D;
class Light;

class GameObjectVisitor
{
public:
    virtual void visit(GameObject* gameObject) = 0;
    virtual void visit(Curve* curve);
    virtual void visit(BezierCurve* bezierCurve);
    virtual void visit(ControlPoint* controlPoint);
    virtual void visit(Model3D* model3D);
    virtual void visit(Light* light);
};
