#pragma once
#include "ofMain.h"
#include "curve.h"

class HermiteCurve : public Curve
{
public:
    HermiteCurve(std::string name);

private:
    ofVec3f interpolate(float t);
    void drawOutline();
};
