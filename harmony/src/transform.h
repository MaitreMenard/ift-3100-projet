#pragma once
#include "ofMain.h"

class Transform
{
private:
    ofVec3f position;
    ofQuaternion rotation;
    ofVec3f scale;

public:
    Transform();
    ofVec3f getPosition();
    ofVec3f getScale();

    void translate(float dx, float dy, float dz);
    void reScale(float x, float y, float z);
};
