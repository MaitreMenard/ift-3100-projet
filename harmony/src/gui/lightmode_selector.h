#pragma once
#include "ofMain.h"
#include "selector.h"
#include "light.h"

class LightModeSelector : public Selector<int>
{
public:
    void setup(enum LightMode defaultLightMode);

private:
    const std::string headerText = "Light Mode";
    const std::string lightModeLabels[4] = {   //FIXME: this should go in light.h
        "PointLight",
        "SpotLight",
        "AmbientLight",
        "DirectionalLight"
    };
};
