#pragma once
#include "ofMain.h"
#include "gameobject.h"

class Curve : public GameObject
{
public:
    Curve();

    void draw();
    ofColor getColor();
    void setColor(ofColor color);

    ~Curve();

protected:
    const int outlineWidth = 2;
    const ofColor outlineColor = ofColor(0, 255, 0);
    std::vector<ofVec3f> controlPoints;

    void updateCurvePoints();
    virtual ofVec3f interpolate(float t) = 0;
    virtual void drawOutline() = 0;

private:
    const int curveWidth = 3;
    const ofColor controlPointsColor = ofColor(0, 160, 0);
    const float controlPointsRadius = 0.05;
    const int resolution = 100;

    ofPolyline curvePoints;
    ofColor curveColor;

    void drawCurve();
    void drawControlPoints();
};