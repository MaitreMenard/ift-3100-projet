#pragma once
#include "ofMain.h"
#include "gameobject.h"
#include "texture.h"

class ControlPoint : public GameObject
{
public:
    ControlPoint(std::string name, ofVec3f position);
    void draw();

private:
    const ofColor color = ofColor(0, 160, 0);
    const float radius = 0.05;
};
