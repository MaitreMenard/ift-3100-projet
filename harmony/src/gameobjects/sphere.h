#pragma once
#include "gameobject.h"
#include "texture.h"


class Sphere : public GameObject
{
public:
    Sphere(std::string name, Texture* texture);

private:
    const float defaultRadius = 0.5;
};
