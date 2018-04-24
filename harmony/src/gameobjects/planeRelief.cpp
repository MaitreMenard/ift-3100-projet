#include "planeRelief.h"

planeRelief::planeRelief()
{
	/*
	ofEnableDepthTest();
	ofSetVerticalSync(false);
	ofSetFrameRate(500);
	*/
	shader.load("shaders/texture");
	//shader.load("shaders/displacePhong");

	if (!colorMap.load("img/6133-diffuse.jpg"))
		cout << "color map failed" << endl;

	if (!bumpMap.load("img/6133-bump.jpg"))
		cout << "bump map failed" << endl;

	int planeWidth = bumpMap.getWidth();
	int planeHeight = bumpMap.getHeight();
	int planeGridSize = 1;
	int planeColumns = planeWidth / planeGridSize;
	int planeRows = planeHeight / planeGridSize;

	plane.set(1.0, 1.0, planeColumns, planeRows, OF_PRIMITIVE_TRIANGLES);
	plane.mapTexCoords(0, 0, 1.0, 1.0);

	gameObjectIs2D = false;

	pointLight.setDiffuseColor(ofColor(0.f, 255.f, 0.f));
	pointLight.setSpecularColor(ofColor(255.f, 255.f, 0.f));
	pointLight.setPointLight();

	spotLight.setDiffuseColor(ofColor(255.f, 0.f, 0.f));
	spotLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
	spotLight.setSpotlight();

	spotLight.setSpotlightCutOff(50);
	spotLight.setSpotConcentration(45);

	directionalLight.setDiffuseColor(ofColor(0.f, 0.f, 255.f));
	directionalLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
	directionalLight.setDirectional();

	directionalLight.setOrientation(ofVec3f(0, 90, 0));

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
	shader.setUniform1f("maxHeight", 0.2);
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