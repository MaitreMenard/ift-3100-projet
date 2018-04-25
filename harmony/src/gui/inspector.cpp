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

    GameObject* selectedGameObject = scene.getSelectedGameObject();
    selectedGameObject->accept(*this);

    parentField.update(scene.getSelectedGameObjectParentID(), scene.getNumberOfGameObjects());
}

void Inspector::draw()
{
    panel.draw();
}

void Inspector::visit(GameObject * gameObject)
{
    panel.add(&positionFields);
    panel.add(&rotation);
    panel.add(&scaleFields);
    panel.add(&colorPicker);
    panel.add(&parentField);

    positionFields = gameObject->getPosition();
    rotation = gameObject->getEulerAngles();
    scaleFields = gameObject->getScale();
    colorPicker.setColor(gameObject->getColor());
}

void Inspector::visit(Curve * curve)
{
    visit((GameObject*)curve);
}

void Inspector::visit(ControlPoint * controlPoint)
{
    panel.add(&positionFields);
    positionFields = controlPoint->getPosition();
}

void Inspector::visit(Model3D * model3D)
{
    panel.add(&positionFields);
    panel.add(&rotation);
    panel.add(&scaleFields);
    panel.add(&parentField);

    positionFields = model3D->getPosition();
    rotation = model3D->getEulerAngles();
    scaleFields = model3D->getScale();
}
