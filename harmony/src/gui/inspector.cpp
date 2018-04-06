#include "inspector.h"

void Inspector::setup(Scene & scene)
{
    panel.setup();
    panel.setName(headerText);
    panel.setHeaderBackgroundColor(headerColor);

    panel.add(positionFields.setup(positionText, scene.getPositionSelectedGameObject(),
        ofVec3f(POSITION_MIN_VALUE), ofVec3f(POSITION_MAX_VALUE)));
    panel.add(rotation.setup(rotationText, scene.getEulerRotationSelectedGameObject(),
        ofVec3f(ROTATION_MIN_VALUE), ofVec3f(ROTATION_MAX_VALUE)));
    panel.add(scaleFields.setup(scaleText, scene.getScaleSelectedGameObject(),
        ofVec3f(SCALE_MIN_VALUE), ofVec3f(SCALE_MAX_VALUE)));
    panel.add(colorPicker.setup(scene.getColorSelectedGameObject()));
    panel.add(parentField.setup(scene.getSelectedGameObjectParentID(), scene.getNumberOfGameObjects()));

    panel.setPosition(ofGetWidth() - panel.getWidth() - 2, 2);
}

void Inspector::update(Scene& scene)
{
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
