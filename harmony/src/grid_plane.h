#pragma once
#include "ofMain.h"

class GridPlane
{
public:
    GridPlane();
    void setup();
    void draw();

private:
    ofTexture texture;
    ofMesh mesh;
};
