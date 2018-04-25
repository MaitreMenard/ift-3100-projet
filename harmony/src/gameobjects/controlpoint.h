#pragma once
#include "ofMain.h"
#include "gameobject.h"
#include "texture.h"

class ControlPoint : public GameObject
{
public:
    ControlPoint(std::string name, Texture* texture, ofVec3f position, ofColor color);
    void draw();
};
