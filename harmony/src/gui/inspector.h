#pragma once
#include "ofxGui.h"
#include "scene.h"
#include "gui/colorpicker.h"
#include "gui/parentIntField.h"
#include "gui/rotation_slider.h"
#include "gui/vec3f_textfield.h"

class Inspector
{
public:
    Vec3fTextField positionFields;
    RotationSlider rotation;
    Vec3fTextField scaleFields;
    ColorPicker colorPicker;
    ParentIntField parentField;

    void setup();
    void update(Scene& scene);
    void draw();

private:
    const float POSITION_MIN_VALUE = -1000;
    const float POSITION_MAX_VALUE = 1000;
    const float ROTATION_MIN_VALUE = -180;
    const float ROTATION_MAX_VALUE = 180;
    const float SCALE_MIN_VALUE = -100;
    const float SCALE_MAX_VALUE = 100;

    const string headerText = "Inspector";
    const string positionText = "Position: ";
    const string rotationText = "Rotation: ";
    const string scaleText = "Scale: ";
    const ofColor headerColor = ofColor(24, 120, 24);

    ofxPanel panel;

    void setupPanel();
};
