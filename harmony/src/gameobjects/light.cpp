#include "light.h"
#include "gameobject_visitor.h"

Light::Light(string name) : GameObject(name, nullptr)
{
    light = new ofLight();
    boundingBox.set(0.2);
    setLightMode(LIGHTMODE_SPOT);
}

void Light::setLightMode(size_t lightMode)
{
    //TODO: Don't set if the same as current light mode
    if (light != nullptr)
    {
        delete light;
    }
    light = new ofLight();
    if (lightMode == LIGHTMODE_POINT)
    {
        ofLog() << "Point light";
        light->setPointLight();
        //light->setDiffuseColor(ofColor(255, 0, 0));
        setPosition(ofVec3f(-5, 0, 0));
    }
    else if (lightMode == LIGHTMODE_SPOT)
    {
        ofLog() << "Spot light";
        light->setSpotlight();
        //light->setDiffuseColor(ofColor(255, 100, 100));
        setPosition(ofVec3f(0, 3, 0));
        light->lookAt(ofVec3f(0, 0, 0));
        light->setSpotlightCutOff(15);
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
    else
    {
        ofLog() << "Invalid light mode";
    }
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