#pragma once
#include "gameobject.h"
#include "texture.h"

class Polygone : public GameObject
{
public:
    Polygone(std::string name, Texture* texture, size_t nbVertex);

private:
    void createPoint(size_t index);
};
