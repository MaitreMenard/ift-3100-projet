#pragma once
#include "ofMain.h"
#include "gameobject.h"

class Cube : public GameObject
{
public:
    Cube();
    void setColor(ofColor color);
};
