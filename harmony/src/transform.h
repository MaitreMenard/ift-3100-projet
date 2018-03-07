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
	ofQuaternion getRotation();
    ofVec3f getScale();

    void translate(float dx, float dy, float dz);
    void reScale(float x, float y, float z);
	void rotate(float dx, float dy, float dz);
};
