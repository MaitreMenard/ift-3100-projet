#pragma once
#include "ofMain.h"
#include "gameobject.h"

class BezierCurve : public GameObject
{
public:
    BezierCurve();

    void draw();
    ofColor getColor();
    void setColor(ofColor color);

    ~BezierCurve();

private:
    const int curveWidth = 3;
    const ofColor controlPointsColor = ofColor(255, 0, 0);
    const float controlPointsRadius = 0.05;
    const int resolution = 100;

    std::vector<ofVec3f> controlPoints;
    ofPolyline curvePoints;
    ofColor curveColor;

    void updateCurvePoints();
    void drawCurve();
    void drawControlPoints();
    int combinations(int n, int k);
};
