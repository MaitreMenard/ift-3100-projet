#include "polygon.h"


Polygone::Polygone()
{
    texture.allocate(1, 1, GL_RGB);

    nbVertex = 5;

    ofSetCircleResolution(nbVertex);
}

void Polygone::draw()
{
    texture.bind();
    ofDrawCircle(transform.getPosition(), 1);
    texture.unbind();
}