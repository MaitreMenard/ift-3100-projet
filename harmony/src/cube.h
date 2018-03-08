#pragma once
#include "ofMain.h"
#include "gameobject.h"

class Cube: public GameObject
{
private:

public:
    Cube();

    void setColor(ofColor color);
    void draw();
};
