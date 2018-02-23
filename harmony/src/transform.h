#pragma once
#include "ofMain.h"

class Transform
{
private:
    ofVec3f position;
    ofQuaternion rotation;
    ofVec3f scale;

public:
    ofVec3f getPosition();

    void translate(float dx, float dy, float dz);
};
