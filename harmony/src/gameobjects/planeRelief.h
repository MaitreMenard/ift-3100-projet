#pragma once
#include "ofMain.h"
#include "gameobject.h"

//TODO: use a copy of ofMaterial that use the normal map texture
class PlaneRelief : public GameObject
{
private:
    ofImage colorMap;
    ofImage bumpMap;
    ofImage normalMap;
    ofShader shader;
    ofPlanePrimitive plane;

public:
    PlaneRelief(string pName);
    void draw();
    void setColor(ofColor color);
    bool isWithNormalMap();
};
