#pragma once
#include "gameobject.h"
#include "texelFactory.h"

class Point : public GameObject
{
private:
    ofColor color;
    float radius;

public:
    Point();
    void draw();
    ofColor getColor();
    void setColor(ofColor color);
};
