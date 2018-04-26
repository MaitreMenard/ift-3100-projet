#pragma once
#include "ofMain.h"
#include "gameobject.h"

class Light : public GameObject
{
private:
    ofLight* light;

public:
    Light(string name);
    ~Light();

    ofColor getColor();
    void setColor(ofColor color);

    void setLightMode(size_t lightMode);
    ofColor getDiffuseColor();
    void setDiffuseColor(ofColor diffuseColor);
    ofColor getSpecularColor();
    void setSpecularColor(ofColor specularColor);
    ofColor getAmbientColor();
    void setAmbientColor(ofColor ambientColor);

    void draw();

    ofVec3f getPosition();
    void setPosition(ofVec3f position);

    void disable();
    void enable();

    void accept(GameObjectVisitor& visitor);
};

enum LightMode
{
    LIGHTMODE_POINT,
    LIGHTMODE_SPOT,
    LIGHTMODE_AMBIENT,
    LIGHTMODE_DIRECTIONAL
};
