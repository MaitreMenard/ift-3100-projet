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

    virtual ~GameObject();
};