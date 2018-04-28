#include "planeRelief.h"

PlaneRelief::PlaneRelief(string pName) : GameObject(pName, nullptr)
{
    gameObjectIs2D = false;

    if (!colorMap.load("img/6903-diffuse.jpg"))
        cout << "color map failed" << endl;

    int planeWidth = colorMap.getWidth();
    int planeHeight = colorMap.getHeight();
    int planeGridSize = 1;
    int planeColumns = planeWidth / planeGridSize;
    int planeRows = planeHeight / planeGridSize;

    plane.set(1.0, 1.0, planeColumns, planeRows, OF_PRIMITIVE_TRIANGLES);
    plane.mapTexCoords(0, 0, 1.0, 1.0);

    boundingBox.set(1, 1, 0.1f);
	_hasMaterial = true;
}

void PlaneRelief::draw()
{
    ofPushMatrix();
    transform.applyToModelViewMatrix();

	if (_hasMaterial)
		RMaterial.begin();
    plane.draw();
	if (_hasMaterial)
		RMaterial.end();

    if (isSelected)
    {
        drawBoundingBox();
    }

    ofPopMatrix();
}

void PlaneRelief::setColor(ofColor color)
{

}

bool PlaneRelief::isWithNormalMap()
{
    return true;
}
