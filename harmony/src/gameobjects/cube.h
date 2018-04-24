#pragma once
#include "ofMain.h"
#include "gameobject.h"
#include "texture.h"

class Cube : public GameObject
{
public:
    Cube(std::string name, Texture* texture);
    void setColor(ofColor color);
};
