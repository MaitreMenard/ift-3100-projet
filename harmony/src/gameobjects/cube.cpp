#include "cube.h"

Cube::Cube(std::string name, Texture* texture) : GameObject(name, texture)
{
    //TODO: add texture coordinates
    nbVertex = 8;

    model.setMode(OF_PRIMITIVE_TRIANGLES);
    model.addVertex(ofPoint(-0.5f, -0.5f, 0.5f));
    model.addVertex(ofPoint(0.5f, -0.5f, 0.5f));
    model.addVertex(ofPoint(-0.5f, 0.5f, 0.5f));
    model.addVertex(ofPoint(0.5f, 0.5f, 0.5f));
    model.addVertex(ofPoint(-0.5f, -0.5f, -0.5f));
    model.addVertex(ofPoint(0.5f, -0.5f, -0.5f));
    model.addVertex(ofPoint(-0.5f, 0.5f, -0.5f));
    model.addVertex(ofPoint(0.5f, 0.5f, -0.5f));

    model.addIndex(0);
    model.addIndex(1);
    model.addIndex(2);

    model.addIndex(1);
    model.addIndex(2);
    model.addIndex(3);

    model.addIndex(4);
    model.addIndex(5);
    model.addIndex(6);

    model.addIndex(5);
    model.addIndex(6);
    model.addIndex(7);

    model.addIndex(0);
    model.addIndex(2);
    model.addIndex(4);

    model.addIndex(2);
    model.addIndex(4);
    model.addIndex(6);

    model.addIndex(2);
    model.addIndex(3);
    model.addIndex(6);

    model.addIndex(3);
    model.addIndex(6);
    model.addIndex(7);

    model.addIndex(1);
    model.addIndex(3);
    model.addIndex(5);

    model.addIndex(3);
    model.addIndex(5);
    model.addIndex(7);

    model.addIndex(0);
    model.addIndex(1);
    model.addIndex(4);

    model.addIndex(1);
    model.addIndex(4);
    model.addIndex(5);

    gameObjectIs2D = false;
}

void Cube::setColor(ofColor color)
{
    model.clearColors();
    for (int i = 0; i < nbVertex; i++)
    {
        model.addColor(color);
    }
}
