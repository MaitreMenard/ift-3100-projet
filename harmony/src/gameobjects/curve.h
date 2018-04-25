#pragma once
#include "ofMain.h"
#include "gameobject.h"
#include "texture.h"
#include "controlpoint.h"

class Curve : public GameObject
{
public:
    Curve(std::string name);

    void updateCurvePoints();
    void draw();
    ofColor getColor();
    void setColor(ofColor color);
    virtual void accept(GameObjectVisitor& visitor);
    std::vector<ControlPoint*> getControlPoints();

    ~Curve();

protected:
    const int outlineWidth = 2;
    const ofColor outlineColor = ofColor(0, 255, 0);
    std::vector<ControlPoint*> controlPoints;

    virtual ofVec3f interpolate(float t) = 0;
    virtual void drawOutline() = 0;
    ControlPoint* createControlPoint(ofVec3f position);

private:
    const int curveWidth = 3;
    const int resolution = 100;
    const std::string baseControlPointName = "Ctrl Pt ";

    ofPolyline curvePoints;
    ofColor curveColor;

    void drawCurve();
    void drawControlPoints();
};
