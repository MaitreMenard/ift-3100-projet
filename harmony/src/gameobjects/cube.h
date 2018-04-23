#pragma once
#include "ofMain.h"
#include "gameobject.h"

class Cube : public GameObject
{
public:
    Cube(std::string name);
    void setColor(ofColor color);
};
