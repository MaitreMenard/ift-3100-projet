#include "light.h"
#include "gameobject_visitor.h"

Light::Light(string name, LightMode lightMode) : GameObject(name, nullptr)
{
    light = new ofLight();
    boundingBox.set(boxSize);
    setNewLightMode(lightMode);
}

void Light::setNewLightMode(LightMode lightMode)
{
    if (lightMode == LIGHTMODE_POINT)
    {
        ofLog() << "Point light";
        light->setPointLight();
    }
    else if (lightMode == LIGHTMODE_SPOT)
    {
        ofLog() << "Spot light";
        light->setSpotlight();
        light->setSpotlightCutOff(spotLightCutOff);
    }
    else if (lightMode == LIGHTMODE_AMBIENT)
    {
        ofLog() << "Ambient light";
        light->setAmbientColor(ofColor(255, 255, 255));
    }
    else if (lightMode == LIGHTMODE_DIRECTIONAL)
    {
        ofLog() << "Directional light";
        light->setDirectional();
        setPosition(ofVec3f(0, 0, 0));
        light->lookAt(ofVec3f(1, 1, 0));
    }
    this->lightMode = lightMode;
}

void Light::setLightMode(LightMode lightMode)
{
    if (this->lightMode != lightMode)
    {
        GameObject::setPosition(ofVec3f(0));
        GameObject::setRotation(0, 0, 0);

        resetLight(lightMode);

        setNewLightMode(lightMode);
    }
}

void Light::resetLight(LightMode lightMode)
{
    ofColor oldDiffuseColor = light->getDiffuseColor();
    ofColor oldSpecularColor = light->getSpecularColor();
    ofColor oldAmbientColor = light->getAmbientColor();

    delete light;
    light = new ofLight();

    light->setDiffuseColor(oldDiffuseColor);
    light->setSpecularColor(oldSpecularColor);
    light->setAmbientColor(oldAmbientColor);
}

ofColor Light::getDiffuseColor()
{
    return light->getDiffuseColor();
}

void Light::setDiffuseColor(ofColor diffuseColor)
{
    light->setDiffuseColor(diffuseColor);
}

ofColor Light::getSpecularColor()
{
    return light->getSpecularColor();
}

void Light::setSpecularColor(ofColor specularColor)
{
    light->setSpecularColor(specularColor);
}

ofColor Light::getAmbientColor()
{
    return light->getAmbientColor();
}

void Light::setAmbientColor(ofColor ambientColor)
{
    light->setAmbientColor(ambientColor);
}

ofVec3f Light::getPosition()
{
    return light->getPosition();
}

void Light::setPosition(ofVec3f position)
{
    GameObject::setPosition(position);
    light->setPosition(position);
}

ofVec3f Light::getRotation()
{
    return light->getOrientationEuler();
}

void Light::setRotation(float x, float y, float z)
{
    GameObject::setRotation(x, y, z);
    light->setOrientation(ofVec3f(x, y, z));
}

void Light::disable()
{
    light->disable();
}
void Light::enable()
{
    light->enable();
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

Light::~Light()
{
    delete light;
}