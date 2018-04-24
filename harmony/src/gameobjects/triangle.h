#pragma once
#include "gameobject.h"
#include "texture.h"

class Triangle : public GameObject
{
public:
    Triangle(std::string name, Texture* texture);
};
