#include "cube.h"

Cube::Cube()
{
    model.setMode(OF_PRIMITIVE_TRIANGLES);

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
    //TODO: modify vertices in the reScale method
    model.clearVertices();
    model.addVertex(ofPoint(-transform.getScale().x / 2, transform.getScale().y / -2, transform.getScale().z / 2));
    model.addVertex(ofPoint(transform.getScale().x / 2, -transform.getScale().y / 2, transform.getScale().z / 2));
    model.addVertex(ofPoint(-transform.getScale().x / 2, transform.getScale().y / 2, transform.getScale().z / 2));
    model.addVertex(ofPoint(transform.getScale().x / 2, transform.getScale().y / 2, transform.getScale().z / 2));
    model.addVertex(ofPoint(-transform.getScale().x / 2, -transform.getScale().y / 2, -transform.getScale().z / 2));
    model.addVertex(ofPoint(transform.getScale().x / 2, -transform.getScale().y / 2, -transform.getScale().z / 2));
    model.addVertex(ofPoint(-transform.getScale().x / 2, transform.getScale().y / 2, -transform.getScale().z / 2));
    model.addVertex(ofPoint(transform.getScale().x / 2, transform.getScale().y / 2, -transform.getScale().z / 2));

    ofPushMatrix();

    ofTranslate(transform.getPosition());
    model.draw();

    ofPopMatrix();
}
