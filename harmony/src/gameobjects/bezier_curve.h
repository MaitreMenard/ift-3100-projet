#pragma once
#include "ofMain.h"
#include "curve.h"

class BezierCurve : public Curve
{
public:
    BezierCurve(std::string name);
    void accept(GameObjectVisitor& visitor);
    ControlPoint* addControlPoint();

private:
    ofVec3f interpolate(float t);
    int combinations(int n, int k);
    void drawOutline();
};
