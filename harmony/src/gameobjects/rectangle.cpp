#include "rectangle.h"


Rektangle::Rektangle(std::string name, Texture* texture) : GameObject(name, texture)
{
    nbVertex = 4;
    model.setMode(OF_PRIMITIVE_TRIANGLES);
    model.addVertex(ofVec3f(-0.5f, -0.5f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(0, 0));
    model.addVertex(ofVec3f(0.5f, -0.5f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(0, 1));
    model.addVertex(ofVec3f(-0.5f, 0.5f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(1, 0));
    model.addVertex(ofVec3f(0.5f, 0.5f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(1, 1));

    model.addIndex(0);
    model.addIndex(1);
    model.addIndex(2);

    model.addIndex(3);
    model.addIndex(2);
    model.addIndex(1);

    gameObjectIs2D = true;

    boundingBox.set(1, 1, 0.01f);
}