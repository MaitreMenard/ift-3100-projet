#include "light.h"
#include "gameobject_visitor.h"

Light::Light(string name, LightMode lightMode) : GameObject(name, nullptr)
{
    pointLight.setPointLight();
    spotLight.setSpotlight();
    spotLight.setSpotlightCutOff(spotLightCutOff);
    directionnalLight.setDirectional();

    defaultGlobalAmbientColor = ofGetGlobalAmbientColor();
    ofLog() << defaultGlobalAmbientColor;

    diffuseColor = ofColor(255);
    specularColor = ofColor(255);
    if (lightMode == LIGHTMODE_AMBIENT)
    {
        ambientColor = defaultGlobalAmbientColor;
    }
    else
    {
        ambientColor = ofColor(0);
    }

    boundingBox.set(boxSize);
    setNewLightMode(lightMode);
}

void Light::setNewLightMode(LightMode lightMode)
{
    this->lightMode = lightMode;

    if (lightMode == LIGHTMODE_POINT)
    {
        selectedLight = &pointLight;
    }
    else if (lightMode == LIGHTMODE_SPOT)
    {
        selectedLight = &spotLight;
    }
    else if (lightMode == LIGHTMODE_AMBIENT)
    {
        selectedLight = nullptr;
        ofSetGlobalAmbientColor(ambientColor);
    }
    else if (lightMode == LIGHTMODE_DIRECTIONAL)
    {
        selectedLight = &directionnalLight;
    }

    if (lightMode != LIGHTMODE_AMBIENT)
    {
        selectedLight->setDiffuseColor(diffuseColor);
        selectedLight->setSpecularColor(specularColor);
        selectedLight->setAmbientColor(ambientColor);
    }
}

LightMode Light::getLightMode()
{
    return lightMode;
}

void Light::setLightMode(LightMode lightMode)
{
    if (this->lightMode != lightMode)
    {
        disable();
        resetLightTransform();
        setNewLightMode(lightMode);
    }
}

void Light::resetLightTransform()
{
    if (this->lightMode != LIGHTMODE_AMBIENT)
    {
        selectedLight->setPosition(ofVec3f(0));
        selectedLight->setOrientation(ofVec3f(0));
    }
    GameObject::setPosition(ofVec3f(0));
    GameObject::setRotation(0, 0, 0);
}

ofColor Light::getDiffuseColor()
{
    return diffuseColor;
}

void Light::setDiffuseColor(ofColor diffuseColor)
{
    this->diffuseColor = diffuseColor;
    if (lightMode != LIGHTMODE_AMBIENT)
    {
        selectedLight->setDiffuseColor(diffuseColor);
    }
}

ofColor Light::getSpecularColor()
{
    return specularColor;
}

void Light::setSpecularColor(ofColor specularColor)
{
    this->specularColor = specularColor;
    if (lightMode != LIGHTMODE_AMBIENT)
    {
        selectedLight->setSpecularColor(specularColor);
    }
}

ofColor Light::getAmbientColor()
{
    return ambientColor;
}

void Light::setAmbientColor(ofColor ambientColor)
{
    this->ambientColor = ambientColor;
    if (lightMode == LIGHTMODE_AMBIENT)
    {
        ofLog() << ambientColor;
        ofSetGlobalAmbientColor(ambientColor);
    }
    else
    {
        selectedLight->setAmbientColor(ambientColor);
    }
    ofLog() << ofGetGlobalAmbientColor();
}

ofVec3f Light::getPosition()
{
    if (lightMode == LIGHTMODE_AMBIENT)
    {
        return ofVec3f();
    }

    return selectedLight->getPosition();
}

void Light::setPosition(ofVec3f position)
{
    if (lightMode != LIGHTMODE_AMBIENT)
    {
        GameObject::setPosition(position);
        selectedLight->setPosition(position);
    }
}

ofVec3f Light::getRotation()
{
    if (lightMode == LIGHTMODE_AMBIENT)
    {
        return ofVec3f();
    }

    return selectedLight->getOrientationEuler();
}

void Light::setRotation(float x, float y, float z)
{
    if (lightMode != LIGHTMODE_AMBIENT)
    {
        GameObject::setRotation(x, y, z);
        selectedLight->setOrientation(ofVec3f(x, y, z));
    }
}

void Light::disable()
{
    pointLight.disable();
    spotLight.disable();
    directionnalLight.disable();
    ofSetGlobalAmbientColor(defaultGlobalAmbientColor);
}

void Light::enable()
{
    if (lightMode != LIGHTMODE_AMBIENT)
    {
        selectedLight->enable();
    }
    else
    {
        ofSetGlobalAmbientColor(ambientColor);
    }
}

void Light::accept(GameObjectVisitor & visitor)
{
    visitor.visit(this);
}

void Light::draw()
{
    ofPushMatrix();
    transform.applyToModelViewMatrix();

    drawChildren();

    if (isSelected)
    {
        drawBoundingBox();
    }

    ofPopMatrix();
}

ofColor Light::getColor()
{
    return ofColor(255);
}

void Light::setColor(ofColor color) {}
