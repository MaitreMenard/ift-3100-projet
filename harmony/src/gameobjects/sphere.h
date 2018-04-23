#pragma once
#include "gameobject.h"


class Sphere : public GameObject
{
public:
    Sphere(std::string name);

private:
    const float defaultRadius = 0.5;
};
