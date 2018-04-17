#pragma once
#include "gameobject.h"

class Polygone : public GameObject
{
private:
    void createPoint(size_t index);
public:
    Polygone(size_t nbVertex);
};
