#pragma once
#include "ofMain.h"
#include "curve.h"

class BezierCurve : public Curve
{
public:
    BezierCurve();

private:
    ofVec3f interpolate(float t);
    int combinations(int n, int k);
    void drawOutline();
};
