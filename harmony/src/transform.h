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
    void setPosition(float x, float y, float z);
    void translate(float dx, float dy, float dz);

    ofQuaternion getRotation();
    void getRotate(float& angle, float& x, float& y, float& z);
    void setRotation(float x, float y, float z);
    void rotate(float degrees, float x, float y, float z);

    ofVec3f getScale();
    void setScale(float x, float y, float z);
    void reScale(float x, float y, float z);

    void applyToModelViewMatrix();
};
