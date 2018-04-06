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
    Transform(const Transform &transf);
    ofVec3f getPosition() const;
    ofQuaternion getRotation() const;
    void getRotate(float& angle, float& x, float& y, float& z);
    ofVec3f getScale() const;

    void translate(float dx, float dy, float dz);
    void rotate(float degrees, float x, float y, float z);
    void setPosition(ofVec3f position);
    void setRotation(float x, float y, float z);

    void setScale(ofVec3f scale);
    void reScale(float x, float y, float z);

    void applyToModelViewMatrix();

    bool operator==(const Transform &obj);
    bool operator!=(const Transform &obj);
};
