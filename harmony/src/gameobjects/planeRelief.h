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

	ofLight pointLight;
	ofLight spotLight;
	ofLight directionalLight;

	ofMaterial material;

	ofParameterGroup materialParameters;
	ofParameter<ofFloatColor> diffuse;
	ofParameter<ofFloatColor> ambient;
	ofParameter<ofFloatColor> specular;
	ofParameter<ofFloatColor> emissive;
	ofParameter<float> shininess;
public:
    planeRelief();
	void setTexture(size_t textureID, ofPixels * pixels);
	void draw();
	void setColor(ofColor color);
};