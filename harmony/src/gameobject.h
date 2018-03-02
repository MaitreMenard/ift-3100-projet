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

    virtual ~GameObject();
};