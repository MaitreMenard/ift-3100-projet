#pragma once
#include "ofMain.h"
#include "gameobject.h"

class planeBump : public GameObject
{
private:
	ofImage colorMap;
	ofImage bumpMap;
	ofShader shader;
	ofPlanePrimitive plane;

public:
    planeBump(string pName);
	void draw();
	void setColor(ofColor color);
};
