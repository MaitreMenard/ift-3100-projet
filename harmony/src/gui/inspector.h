#pragma once
#include "ofxGui.h"
#include "gameobject.h"
#include "gui/colorpicker.h"
#include "gui/rotation_slider.h"
#include "gui/vec3f_textfield.h"

class Inspector
{
private:
    const string headerText = "Inspector";
    const ofColor headerColor = ofColor(24, 120, 24);

    ofxPanel panel;
    Vec3fTextField positionFields;
    RotationSlider rotation;
    Vec3fTextField scaleFields;
    ColorPicker colorPicker;
    ofxIntField parent;

public:
    Inspector();
    void update(GameObject* gameObject);

    void draw();
};
