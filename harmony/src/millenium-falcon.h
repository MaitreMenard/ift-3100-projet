#pragma once
#include "ofxAssimpModelLoader.h"
#include "gameobject.h"

class MilleniumFalcon : public GameObject
{
private:
    ofxAssimpModelLoader objModel;

    const float X_OFFSET = -5.9;
    const float Y_OFFSET = -1.8;
    const float Z_OFFSET = 190;
    const float SCALE_FACTOR = 0.1;

public:
    MilleniumFalcon();

    void draw();

    void setColor(ofColor color);
};
