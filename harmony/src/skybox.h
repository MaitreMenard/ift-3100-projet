#pragma once
#include "ofMain.h"

class SkyBox
{
private:
    ofVec3f position;
    ofMesh cube;
    ofTexture texture[6];

public:
    void setup(string fileName);
    void draw();
    void translate(float dx, float dy, float dz);
};
