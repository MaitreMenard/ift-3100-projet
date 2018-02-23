#pragma once
#include "ofMain.h"
#include "gameobject.h"

class Cube: public GameObject
{
private:
    ofMesh model;

public:
    Cube();

    void draw();
};
