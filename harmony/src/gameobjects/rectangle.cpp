#include "rectangle.h"


Rektangle::Rektangle()
{
    ofPixels * pix = new ofPixels();
    pix->allocate(1, 1, OF_PIXELS_RGB);
    pix->setColor(0, 0, ofColor(255, 255, 255));
    texture.allocate(*pix);

    nbVertex = 4;
    model.setMode(OF_PRIMITIVE_TRIANGLES);
    model.addVertex(ofVec3f(-0.5f, -0.5f, 0.f));
    model.addTexCoord(texture.getCoordFromPercent(0, 0));
    model.addVertex(ofVec3f(0.5f, -0.5f, 0.f));
    model.addTexCoord(texture.getCoordFromPercent(0, 1));
    model.addVertex(ofVec3f(-0.5f, 0.5f, 0.f));
    model.addTexCoord(texture.getCoordFromPercent(1, 0));
    model.addVertex(ofVec3f(0.5f, 0.5f, 0.f));
    model.addTexCoord(texture.getCoordFromPercent(1, 1));

    model.addIndex(0);
    model.addIndex(1);
    model.addIndex(2);

    model.addIndex(3);
    model.addIndex(2);
    model.addIndex(1);
}

void Rektangle::setColor(ofColor color)
{
    model.clearColors();
    for (int i = 0; i < nbVertex; i++)
    {
        model.addColor(color);
    }
}