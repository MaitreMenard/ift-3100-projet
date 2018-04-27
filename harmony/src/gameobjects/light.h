#pragma once
#include "ofMain.h"
#include "gameobject.h"

enum LightMode
{
    LIGHTMODE_POINT,
    LIGHTMODE_SPOT,
    LIGHTMODE_AMBIENT,
    LIGHTMODE_DIRECTIONAL
};

class Light : public GameObject
{
public:
    Light(string name, LightMode lightMode);
    ~Light();

    ofColor getColor();
    void setColor(ofColor color);

    void setLightMode(LightMode lightMode);
    ofColor getDiffuseColor();
    void setDiffuseColor(ofColor diffuseColor);
    ofColor getSpecularColor();
    void setSpecularColor(ofColor specularColor);
    ofColor getAmbientColor();
    void setAmbientColor(ofColor ambientColor);

    void draw();

    ofVec3f getPosition();
    void setPosition(ofVec3f position);

    ofVec3f getRotation();
    void setRotation(float x, float y, float z);

    void disable();
    void enable();

    void accept(GameObjectVisitor& visitor);

private:
    const float boxSize = 0.2;
    const float spotLightCutOff = 15;

    ofLight* light;
    LightMode lightMode;

    void setNewLightMode(LightMode lightMode);
    void resetLight(LightMode lightMode);
};
