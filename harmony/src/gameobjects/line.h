#pragma once
#include "gameobject.h"
#include "texture.h"

class Line : public GameObject
{
public:
    Line(std::string name, Texture* texture);
    void draw();
    ofColor getColor();
    void setColor(ofColor color);

private:
    ofColor color;
    float lineWidth;
};
