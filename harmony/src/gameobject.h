#pragma once
#include "ofMain.h"
#include "transform.h"

class GameObject
{
protected:
    Transform transform;

public:
    virtual void setup();
    virtual void update();
    virtual void draw();

    void translate(float dx, float dy, float dz);
    void reScale(float x, float y, float z);
    void rotate(float degrees, float x, float y, float z);
    void setRotation(float thetaX, float thetaY, float thetaZ);

    virtual ~GameObject();
};