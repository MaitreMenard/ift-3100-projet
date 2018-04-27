#pragma once
#include "ofMain.h"
#include "selector.h"
#include "light.h"
#include "gameobject_visitor.h"

class LightModeSelector : public Selector<int>, public GameObjectVisitor
{
public:
    void setup(enum LightMode defaultLightMode);

    void visit(GameObject* gameObject);
    void visit(Curve* curve);
    void visit(BezierCurve* bezierCurve);
    void visit(ControlPoint* controlPoint);
    void visit(Model3D* model3D);
    void visit(Light* light);

private:
    const std::string headerText = "Light Mode";
    const std::string lightModeLabels[4] = {   //FIXME: this should go in light.h
        "PointLight",
        "SpotLight",
        "AmbientLight",
        "DirectionalLight"
    };
};
