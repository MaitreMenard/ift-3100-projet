#include "sphere.h"

Sphere::Sphere()
{
    ofSpherePrimitive spherePrimitive = ofSpherePrimitive();
    spherePrimitive.setRadius(defaultRadius);

	ofPixels * pix = new ofPixels();
	pix->allocate(1, 1, OF_PIXELS_RGB);
	pix->setColor(0, 0, ofColor(255, 255, 255));
	texture.allocate(*pix);

    model = spherePrimitive.getMesh();
    nbVertex = model.getVertices().size();

    gameObjectIs2D = false;
}
