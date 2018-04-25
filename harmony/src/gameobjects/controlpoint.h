#pragma once
#include "ofMain.h"
#include "gameobject.h"

class Curve;

class ControlPoint : public GameObject
{
public:
    ControlPoint(std::string name, ofVec3f position, Curve* curve);
    void draw();
    Curve* getCurve();
    void setPosition(ofVec3f position);
    void setSelected(bool isSelected);

private:
    const ofColor color = ofColor(0, 160, 0);
    const float radius = 0.05;

    Curve* curve;
};
