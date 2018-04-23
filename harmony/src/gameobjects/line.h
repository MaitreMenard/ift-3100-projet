#pragma once
#include "gameobject.h"
#include "texelFactory.h"

class Line : public GameObject
{
public:
    Line(std::string name);
    void draw();
    ofColor getColor();
    void setColor(ofColor color);

private:
    ofColor color;
    float lineWidth;
};
