#include "mirror.h"


Mirror::Mirror(std::string name, Texture* texture) : GameObject(name, texture)
{
    mirrorTexture = new Texture(*texture);

    nbVertex = 4;
    model.setMode(OF_PRIMITIVE_TRIANGLES);
    model.addVertex(ofVec3f(-0.5f, -0.5f, 0.f));
    model.addVertex(ofVec3f(0.5f, -0.5f, 0.f));
    model.addVertex(ofVec3f(-0.5f, 0.5f, 0.f));
    model.addVertex(ofVec3f(0.5f, 0.5f, 0.f));
    addTexCoords();

    model.addIndex(0);
    model.addIndex(1);
    model.addIndex(2);

    model.addIndex(3);
    model.addIndex(2);
    model.addIndex(1);

    boundingBox.set(1, 1, 0.01f);
}

void Mirror::addTexCoords()
{
    model.addTexCoord(mirrorTexture->getCoordFromPercent(0, 1));
    model.addTexCoord(mirrorTexture->getCoordFromPercent(1, 1));
    model.addTexCoord(mirrorTexture->getCoordFromPercent(0, 0));
    model.addTexCoord(mirrorTexture->getCoordFromPercent(1, 0));

}

void Mirror::setTexturePixels(ofPixels pix)
{
    mirrorTexture->allocate(pix);
    model.clearTexCoords();
    addTexCoords();
}

void Mirror::drawTextureAndMaterial()
{
    mirrorTexture->bind();
    model.draw();
    mirrorTexture->unbind();
}

Mirror::~Mirror()
{
    delete mirrorTexture;
}