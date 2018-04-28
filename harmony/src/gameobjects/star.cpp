#include "star.h"

Star::Star(std::string name, Texture* texture) : GameObject(name, texture)
{
    nbVertex = 10;
    model.setMode(OF_PRIMITIVE_TRIANGLES);

    model.addVertex(ofVec3f(0.f, 0.5f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(0.5f, 0.f));
    model.addVertex(ofVec3f(-0.125f, 0.125f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(0.375f, 0.375f));
    model.addVertex(ofVec3f(0.125f, 0.125f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(0.625f, 0.375f));

    model.addVertex(ofVec3f(0.2f, -0.13f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(0.7f, 0.63f));
    model.addVertex(ofVec3f(0.5f, 0.125f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(1, 0.375f));

    model.addVertex(ofVec3f(0.f, -0.29f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(0.5f, 0.79f));
    model.addVertex(ofVec3f(0.3f, -0.5f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(0.8f, 1));

    model.addVertex(ofVec3f(-0.2f, -0.13f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(0.3f, 0.63f));
    model.addVertex(ofVec3f(-0.3f, -0.5f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(0.2f, 1));

    model.addVertex(ofVec3f(-0.5f, 0.125f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(0.f, 0.375f));

    model.addIndex(0);
    model.addIndex(1);
    model.addIndex(2);

    model.addIndex(2);
    model.addIndex(3);
    model.addIndex(4);

    model.addIndex(3);
    model.addIndex(5);
    model.addIndex(6);

    model.addIndex(5);
    model.addIndex(7);
    model.addIndex(8);

    model.addIndex(7);
    model.addIndex(1);
    model.addIndex(9);

    model.addIndex(1);
    model.addIndex(7);
    model.addIndex(5);

    model.addIndex(1);
    model.addIndex(5);
    model.addIndex(2);

    model.addIndex(2);
    model.addIndex(5);
    model.addIndex(3);

    gameObjectIs2D = true;
	hasMaterial = true;
    boundingBox.set(1, 1, 0.01f);
}
