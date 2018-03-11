#pragma once
#include "ofMain.h"

class SkyBox
{
private:
    ofVec3f position;
    ofMesh cube;
    GLuint textureID;
    ofShader shader;

public:
    void setup(string fileNames[6]);
    void draw();
    void translate(float dx, float dy, float dz);
};
