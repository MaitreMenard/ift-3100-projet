#pragma once
#include "ofMain.h"

class CubeMap
{
private:
    ofVec3f position;
    ofMesh cube;
    ofTexture texture;

public:
    void setup(string fileName);
    void draw();
    void translate(float dx, float dy, float dz);
};
