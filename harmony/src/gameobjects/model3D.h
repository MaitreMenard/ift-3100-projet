#pragma once
#include "ofxAssimpModelLoader.h"
#include "gameobject.h"

class Model3D : public GameObject
{
private:
    ofxAssimpModelLoader objModel;

public:
    Model3D(string fileName);
    Model3D(string fileName, ofVec3f positionOffset, float rotationOffsetAngle, ofVec3f rotationOffsetAxis, ofVec3f scaleFactor);

    void draw();

    void setColor(ofColor color);
};