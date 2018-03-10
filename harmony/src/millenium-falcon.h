#pragma once
#include "ofxAssimpModelLoader.h"
#include "gameobject.h"

class MilleniumFalcon : public GameObject
{
private:
    ofxAssimpModelLoader objModel;

    const ofVec3f POSITION_OFFSET = ofVec3f(-0.59, 0.17, 19.0);
    const float ROTATION_ANGLE = 180;
    const ofVec3f ROTATION_AXIS = ofVec3f(0, 0, 1);
    const ofVec3f SCALE_FACTOR = ofVec3f(0.01, 0.01, 0.01);

    void fixModel();

public:
    MilleniumFalcon();

    void draw();

    void setColor(ofColor color);
};
