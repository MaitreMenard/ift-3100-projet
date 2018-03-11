#pragma once
#include "gameobject.h"
#include "texelFactory.h"

class Line : public GameObject
{
private:
    ofColor color;
    float lineWidth;

public:
    Line();
    void draw();
    ofColor getColor();
    void setColor(ofColor color);
};
