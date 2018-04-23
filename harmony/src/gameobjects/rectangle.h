#pragma once
#include "gameobject.h"
#include "texture.h"

class Rektangle : public GameObject
{
public:
    Rektangle(std::string name, Texture* texture);
};
