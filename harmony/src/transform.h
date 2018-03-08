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
    void getRotate(float& angle, float& x, float& y, float& z);
    ofVec3f getScale();

    void translate(float dx, float dy, float dz);
    void reScale(float x, float y, float z);
    void rotate(float degrees, float x, float y, float z);
	void setPosition(float x, float y, float z);
    void setRotation(float thetaX, float thetaY, float thetaZ);
	void setScale(float x, float y, float z);
};
