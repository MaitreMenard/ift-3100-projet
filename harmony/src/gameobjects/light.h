#pragma once
#include "ofMain.h"
#include "gameobject.h"

class Light : public GameObject
{
private:
    ofLight* light;
public:
    Light(string name, Texture* texture);
    ~Light();

    ofColor getColor();
    void setColor(ofColor color);

    void setLightMode(size_t lightMode);

    void draw();

    ofVec3f getPosition();
    void setPosition(ofVec3f position);

    void disable();
    void enable();
};

enum LightMode {
    Point,
    Spot,
    Ambient, 
    Directional
};
