#pragma once
#include "ofMain.h"
#include "selector.h"
#include "light.h"

class LightModeSelector : public Selector<enum LightMode>
{
private:
    const std::string headerText = "Light Mode";
    const std::string lightModeLabels[] = {   //FIXME: this should go in light.h
        "PointLight",
        "SpotLight",
        "AmbientLight",
        "DirectionalLight"
    };

public:
    void setup(LightMode defaultLightMode);
};
