#pragma once
#include "ofxAssimpModelLoader.h"
#include "gameobject.h"
#include "texture.h"

class Model3D : public GameObject
{
public:
    Model3D(std::string name, Texture* texture, std::string fileName, ofVec3f positionOffset,
        float rotationOffsetAngle, ofVec3f rotationOffsetAxis, ofVec3f scaleFactor);

    void draw();

    void setColor(ofColor color);

private:
    ofxAssimpModelLoader objModel;
};