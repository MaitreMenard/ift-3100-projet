#pragma once
#include "ofxGui.h"
#include "scene.h"
#include "gameobject_visitor.h"
#include "gameobjects/bezier_curve.h"
#include "gameobjects/model3D.h"
#include "gameobjects/light.h"
#include "gui/colorpicker.h"
#include "gui/parentIntField.h"
#include "gui/rotation_slider.h"
#include "gui/vec3f_textfield.h"

class Inspector : public GameObjectVisitor
{
public:
    Vec3fTextField positionFields;
    RotationSlider rotation;
    Vec3fTextField scaleFields;
    ColorPicker colorPicker;
    ColorPicker diffuseColorpicker;
    ColorPicker specularColorPicker;
    ColorPicker ambientColorPicker;
    ParentIntField parentField;
    ofxButton addControlPointButton;

    void setup();
    void update(Scene& scene);
    void draw();

    void visit(GameObject* gameObject);
    void visit(BezierCurve* bezierCurve);
    void visit(ControlPoint* controlPoint);
    void visit(Model3D* model3D);
    void visit(Light* light);

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
    const string colorPickerText = "Color:";
    const string diffuseColorPickerText = "Diffuse Color:";
    const string specularColorPickerText = "Specular Color:";
    const string ambientColorPickerText = "Ambient Color:";
    const string addControlPointButtonText = "Add Control Point";
    const ofColor headerColor = ofColor(24, 120, 24);
    const ofColor addControlPointButtonColor = ofColor(48, 48, 72);

    ofxPanel panel;

    void setupPanel();
};
