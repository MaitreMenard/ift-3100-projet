#include "arrow.h"

Arrow::Arrow(std::string name, Texture* texture) : GameObject(name, texture)
{
    nbVertex = 7;
    model.setMode(OF_PRIMITIVE_TRIANGLES);

    model.addVertex(ofVec3f(0.f, 0.5f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(0.5f, 0.f));
    model.addVertex(ofVec3f(-0.5f, 0.15f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(0.f, 0.35f));
    model.addVertex(ofVec3f(0.5f, 0.15f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(1, 0.35f));

    model.addVertex(ofVec3f(-0.2f, 0.15f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(0.3f, 0.35f));
    model.addVertex(ofVec3f(-0.2f, -0.5f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(0.3f, 1));
    model.addVertex(ofVec3f(0.2f, -0.5f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(0.7f, 1));

    model.addVertex(ofVec3f(0.2f, 0.15f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(0.7f, 0.35f));

    model.addIndex(0);
    model.addIndex(1);
    model.addIndex(2);

    model.addIndex(3);
    model.addIndex(4);
    model.addIndex(5);

    model.addIndex(3);
    model.addIndex(5);
    model.addIndex(6);

    gameObjectIs2D = true;
    boundingBox.set(1, 1, 0.01f);
}
