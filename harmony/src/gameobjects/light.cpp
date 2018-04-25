#include "light.h"

Light::Light(string name) : GameObject(name, nullptr)
{
    light = new ofLight();
    setLightMode(Spot);
}

void Light::setLightMode(size_t lightMode)
{
    if (light != nullptr)
    {
        delete light;
    }
    light = new ofLight();
    if (lightMode == Point)
    {
        light->setPointLight();
        //light->setDiffuseColor(ofColor(255, 0, 0));
        setPosition(ofVec3f(-5, 0, 0));
    }
    else if (lightMode == Spot)
    {
        light->setSpotlight();
        //light->setDiffuseColor(ofColor(255, 100, 100));
        setPosition(ofVec3f(0, 3, 0));
        light->lookAt(ofVec3f(0, 0, 0));
        light->setSpotlightCutOff(15);
    }
    else if (lightMode == Ambient)
    {
        light->setAmbientColor(ofColor(255, 255, 255));
    }
    else
    {
        light->setDirectional();
        setPosition(ofVec3f(0, 0, 0));
        light->lookAt(ofVec3f(1, 1, 0));
    }
}

ofVec3f Light::getPosition()
{
    return light->getPosition();
}

void Light::setPosition(ofVec3f position)
{
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

void Light::draw() {}

ofColor Light::getColor()
{
    return ofColor(255);
}

void Light::setColor(ofColor color) {}

Light::~Light()
{
    delete light;
}