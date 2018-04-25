#pragma once
#include "ofMain.h"
#include "curve.h"

class BezierCurve : public Curve
{
public:
    BezierCurve(std::string name);

private:
    ofVec3f interpolate(float t);
    int combinations(int n, int k);
    void drawOutline();
};
