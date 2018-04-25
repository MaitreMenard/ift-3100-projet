#pragma once
#include "ofMain.h"
#include "curve.h"
#include "texture.h"

class BezierCurve : public Curve
{
public:
    BezierCurve(std::string name, Texture* texture);

private:
    ofVec3f interpolate(float t);
    int combinations(int n, int k);
    void drawOutline();
};