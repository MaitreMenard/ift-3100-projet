#include "planeBump.h"

planeBump::planeBump(string pName) : GameObject(pName, nullptr)
{
	gameObjectIs2D = false;
	shader.load("shaders/bumpMap");

	//if (!colorMap.load("img/6133-diffuse.jpg"))
	if (!colorMap.load("img/6903-diffuse.jpg"))
		cout << "color map failed" << endl;

	//if (!bumpMap.load("img/6133-bump.jpg"))
	if (!bumpMap.load("img/6903-bump.jpg"))
		cout << "bump map failed" << endl;

	int planeWidth = bumpMap.getWidth();
	int planeHeight = bumpMap.getHeight();
	int planeGridSize = 1;
	int planeColumns = planeWidth / planeGridSize;
	int planeRows = planeHeight / planeGridSize;

	plane.set(1.0, 1.0, planeColumns, planeRows, OF_PRIMITIVE_TRIANGLES);
	plane.mapTexCoords(0, 0, 1.0, 1.0);
}

void planeBump::draw()
{
	ofPushMatrix();
	transform.applyToModelViewMatrix();

	shader.begin();
	shader.setUniformTexture("texColor", colorMap.getTextureReference(), 0);
	shader.setUniformTexture("texBumpMap", bumpMap.getTextureReference(), 1);
	shader.setUniform1f("maxHeight", 0.05);
	plane.draw();
	shader.end();

    if (isSelected)
    {
        drawBoundingBox();
    }

	ofPopMatrix();
}

void planeBump::setColor(ofColor color) {

}