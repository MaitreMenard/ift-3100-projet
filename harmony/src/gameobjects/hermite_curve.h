#pragma once
#include "ofMain.h"
#include "curve.h"

class HermiteCurve : public Curve
{
public:
    HermiteCurve();

private:
    ofVec3f interpolate(float t);
    void drawOutline();
};
