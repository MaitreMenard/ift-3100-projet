#include "planeRelief.h"

planeRelief::planeRelief()
{
	/*
	ofEnableDepthTest();
	ofSetVerticalSync(false);
	ofSetFrameRate(500);
	*/
	shader.load("shaders/texture");

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

	gameObjectIs2D = false;

}

void planeRelief::setTexture(size_t textureID, ofPixels * pixels) {
	this->textureID = textureID;
	texture.clear();
	texture.allocate(*pixels);
	texture.setTextureWrap(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
}

void planeRelief::draw()
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


void planeRelief::setColor(ofColor color) {

}