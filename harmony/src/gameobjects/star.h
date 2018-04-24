#pragma once
#include "ofMain.h"
#include "gameobject.h"
#include "texture.h"

class Star : public GameObject
{
public:
    Star(std::string name, Texture* texture);
};
