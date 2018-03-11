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
	Transform(const Transform &transf);
    ofVec3f getPosition() const;
    ofQuaternion getRotation() const;
    void getRotate(float& angle, float& x, float& y, float& z);
    ofVec3f getScale() const;

    void translate(float dx, float dy, float dz);
	void rotate(float degrees, float x, float y, float z);
    void setPosition(float x, float y, float z);
    void setRotation(float x, float y, float z);

    void setScale(float x, float y, float z);
    void reScale(float x, float y, float z);

    void applyToModelViewMatrix();

    void setRelativeTo(Transform other);
	bool operator==(const Transform &obj);
	bool operator!=(const Transform &obj);
};
