#pragma once
#include "gameobject.h"
#include "texelFactory.h"

class Polygone : public GameObject
{
public:
    Polygone(std::string name, size_t nbVertex);

private:
    void createPoint(size_t index);
};
