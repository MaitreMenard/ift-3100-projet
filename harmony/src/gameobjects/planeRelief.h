#pragma once
#include "ofMain.h"
#include "gameobject.h"

class planeRelief : public GameObject
{
private:
	ofImage colorMap;
	ofImage bumpMap;
	ofShader shader;
	ofPlanePrimitive plane;

public:
    planeRelief();
	void setTexture(size_t textureID, ofPixels * pixels);
	void draw();
	void setColor(ofColor color);
};
