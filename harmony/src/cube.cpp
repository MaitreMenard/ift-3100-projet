#include "cube.h"

Cube::Cube()
{
    model.setMode(OF_PRIMITIVE_TRIANGLES);
    model.addVertex(ofPoint(-50, -50, 50));
    model.addVertex(ofPoint(50, -50, 50));
    model.addVertex(ofPoint(-50, 50, 50));
    model.addVertex(ofPoint(50, 50, 50));
    model.addVertex(ofPoint(-50, -50, -50));
    model.addVertex(ofPoint(50, -50, -50));
    model.addVertex(ofPoint(-50, 50, -50));
    model.addVertex(ofPoint(50, 50, -50));

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

    model.addColor(ofColor(0, 0, 0));
    model.addColor(ofColor(255, 0, 0));
    model.addColor(ofColor(0, 255, 0));
    model.addColor(ofColor(255, 255, 0));
    model.addColor(ofColor(0, 0, 255));
    model.addColor(ofColor(255, 0, 255));
    model.addColor(ofColor(0, 255, 255));
    model.addColor(ofColor(255, 255, 255));
}

void Cube::draw()
{
    model.draw();
}
