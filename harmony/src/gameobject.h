#pragma once
#include "ofMain.h"
#include "transform.h"

class GameObject
{
private:
    Transform transform;

public:
    virtual void setup();
    virtual void update();
    virtual void draw();

    virtual ~GameObject();
};