#pragma once
#include "ofMain.h"
#include "gameobject.h"
#include "ReliefMaterial.h"

//TODO: use a copy of ofMaterial that use the normal map texture
class PlaneRelief : public GameObject
{
private:
	ofImage colorMap;
    ofPlanePrimitive plane;
	ReliefMaterial RMaterial;


public:
    PlaneRelief(string pName);
    void draw();
    void setColor(ofColor color);
    bool isWithNormalMap();
};
