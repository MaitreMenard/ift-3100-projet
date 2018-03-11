#pragma once
#include "ofMain.h"

class Transform
{
private:
    ofVec3f globalPosition;
    ofQuaternion globalRotation;
    ofVec3f globalScale;

    ofVec3f localPosition;
    ofQuaternion localRotation;
    ofVec3f localScale;

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

    void setRelativeTo(Transform other);
    void setGlobal();
};
