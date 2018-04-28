#include "polygone.h"

Polygone::Polygone(std::string name, Texture* texture, size_t nbVertex) : GameObject(name, texture)
{
    this->nbVertex = nbVertex;
    model.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    for (size_t i = 0; i < nbVertex; i++)
    {
        createPoint(i);
    }

    gameObjectIs2D = true;
	hasMaterial = true;

    boundingBox.set(1, 1, 0.01f);
}

void Polygone::createPoint(size_t index)
{
    float x = cosf(((index * 2.f * PI) / nbVertex) + (PI / 2.f)) / 2.f;
    float y = sinf(((index * 2.f * PI) / nbVertex) + (PI / 2.f)) / 2.f;

    model.addVertex(ofVec3f(x, y));
    model.addTexCoord(texture->getCoordFromPercent(0.5f + x, 0.5f - y));
}
