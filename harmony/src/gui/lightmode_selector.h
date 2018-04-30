#pragma once
#include "ofMain.h"
#include "selector.h"
#include "gameobject_visitor.h"
#include "gameobject.h"
#include "gameobjects/light.h"

class LightModeSelector : public Selector<int>, public GameObjectVisitor
{
public:
    void setup(enum LightMode defaultLightMode);

    void visit(GameObject* gameObject);
    void visit(Light* light);

    void onWindowResized();

private:
    const std::string headerText = "Light Mode";
    const std::string lightModeLabels[4] = {   //FIXME: this should go in light.h
        "PointLight",
        "SpotLight",
        "AmbientLight",
        "DirectionalLight"
    };
};
