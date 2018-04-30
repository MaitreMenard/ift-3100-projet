#include "inspector.h"

void Inspector::setup()
{
    setupPanel();

    positionFields.setup(positionText, ofVec3f(0), ofVec3f(POSITION_MIN_VALUE), ofVec3f(POSITION_MAX_VALUE));
    rotation.setup(rotationText, ofVec3f(0), ofVec3f(ROTATION_MIN_VALUE), ofVec3f(ROTATION_MAX_VALUE));
    scaleFields.setup(scaleText, ofVec3f(1), ofVec3f(SCALE_MIN_VALUE), ofVec3f(SCALE_MAX_VALUE));

    colorPicker.setup(colorPickerText, ofColor());
    diffuseColorpicker.setup(diffuseColorPickerText, ofColor());
    specularColorPicker.setup(specularColorPickerText, ofColor());
    ambientColorPicker.setup(ambientColorPickerText, ofColor());

    parentField.setup(0, 0);

    addControlPointButton.setup(addControlPointButtonText);
    addControlPointButton.setBackgroundColor(labelColor);

    shininessField.setup(shininessFieldText, 0.2, 0, 128);
    shininessField.setBackgroundColor(labelColor);
}

void Inspector::setupPanel()
{
    panel.setup();
    panel.setName(headerText);
    panel.setHeaderBackgroundColor(headerColor);

    onWindowResized();
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
    positionFields = gameObject->getPosition();

    panel.add(&rotation);
    rotation = gameObject->getEulerAngles();

    panel.add(&scaleFields);
    scaleFields = gameObject->getScale();

    if (gameObject->hasMaterial())
    {
        panel.add(&diffuseColorpicker);
        diffuseColorpicker.setColor(gameObject->getDiffuseColor());
        diffuseColorpicker.minimize();

        panel.add(&specularColorPicker);
        specularColorPicker.setColor(gameObject->getSpecularColor());
        specularColorPicker.minimize();

        panel.add(&ambientColorPicker);
        ambientColorPicker.setColor(gameObject->getAmbientColor());
        ambientColorPicker.minimize();

        panel.add(&shininessField);
        shininessField = gameObject->getShininess();
    }
    else
    {
        panel.add(&colorPicker);
        colorPicker.setColor(gameObject->getColor());
        colorPicker.minimize();
    }

    panel.add(&parentField);
}

void Inspector::visit(BezierCurve * bezierCurve)
{
    visit((GameObject*)bezierCurve);
    panel.add(&addControlPointButton);
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

void Inspector::visit(Light * light)
{
    LightMode lightMode = light->getLightMode();
    if (lightMode == LIGHTMODE_POINT || lightMode == LIGHTMODE_SPOT)
    {
        panel.add(&positionFields);
        positionFields = light->getPosition();
    }
    if (lightMode == LIGHTMODE_SPOT || lightMode == LIGHTMODE_DIRECTIONAL)
    {
        panel.add(&rotation);
        rotation = light->getRotation();
    }
    if (lightMode != LIGHTMODE_AMBIENT)
    {
        panel.add(&diffuseColorpicker);
        diffuseColorpicker.setColor(light->getDiffuseColor());
        diffuseColorpicker.minimize();

        panel.add(&specularColorPicker);
        specularColorPicker.setColor(light->getSpecularColor());
        specularColorPicker.minimize();
    }

    panel.add(&ambientColorPicker);
    ambientColorPicker.setColor(light->getAmbientColor());
    ambientColorPicker.minimize();
}

void Inspector::onWindowResized()
{
    panel.setPosition(ofGetWidth() - panel.getWidth() - 2, 2);
}
