#pragma once
#include "ofMain.h"
#include "gameobject.h"
#include "texture.h"

class Arrow : public GameObject
{
public:
    Arrow(std::string name, Texture* texture);
};
