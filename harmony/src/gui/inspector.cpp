#include "inspector.h"

void Inspector::setup()
{
    setupPanel();

    positionFields.setup(positionText, ofVec3f(0), ofVec3f(POSITION_MIN_VALUE), ofVec3f(POSITION_MAX_VALUE));
    rotation.setup(rotationText, ofVec3f(0), ofVec3f(ROTATION_MIN_VALUE), ofVec3f(ROTATION_MAX_VALUE));
    scaleFields.setup(scaleText, ofVec3f(1), ofVec3f(SCALE_MIN_VALUE), ofVec3f(SCALE_MAX_VALUE));
    colorPicker.setup(ofColor());
    parentField.setup(0, 0);
}

void Inspector::setupPanel()
{
    panel.setup();
    panel.setName(headerText);
    panel.setHeaderBackgroundColor(headerColor);
    panel.setPosition(ofGetWidth() - panel.getWidth() - 2, 2);
}

void Inspector::update(Scene& scene)
{
    panel.clear();
    setupPanel();

    panel.add(&positionFields);
    panel.add(&rotation);
    panel.add(&scaleFields);
    panel.add(&colorPicker);
    panel.add(&parentField);

    positionFields = scene.getPositionSelectedGameObject();
    rotation = scene.getEulerRotationSelectedGameObject();
    scaleFields = scene.getScaleSelectedGameObject();
    colorPicker.setColor(scene.getColorSelectedGameObject());
    parentField.update(scene.getSelectedGameObjectParentID(), scene.getNumberOfGameObjects());
}

void Inspector::draw()
{
    panel.draw();
}
