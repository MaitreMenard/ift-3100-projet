#include "polygon.h"


Polygone::Polygone()
{
	ofPixels * pix = new ofPixels();
	pix->allocate(1, 1, OF_PIXELS_RGB);
	pix->setColor(0, 0, ofColor(255, 255, 255));
	texture.allocate(*pix);

    nbVertex = 5;

    ofSetCircleResolution(nbVertex);
}

void Polygone::draw()
{
    texture.bind();
    ofDrawCircle(transform.getPosition(), 1);
    texture.unbind();
}