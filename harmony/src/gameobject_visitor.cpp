#include "gameobject_visitor.h"

void GameObjectVisitor::visit(Curve * curve)
{
    visit((GameObject*)curve);
}

void GameObjectVisitor::visit(BezierCurve * bezierCurve)
{
    visit((GameObject*)bezierCurve);
}

void GameObjectVisitor::visit(ControlPoint * controlPoint)
{
    visit((GameObject*)controlPoint);
}

void GameObjectVisitor::visit(Model3D * model3D)
{
    visit((GameObject*)model3D);
}

void GameObjectVisitor::visit(Light * light)
{
    visit((GameObject*)light);
}
