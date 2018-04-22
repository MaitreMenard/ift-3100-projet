#include "curve.h"

Curve::Curve()
{
    texture.allocate(1, 1, GL_RGB);
    nbVertex = 0;
    gameObjectIs2D = false;

    curveColor = ofColor(255, 0, 0);

    for (int i = 0; i <= resolution; i++)
    {
        curvePoints.addVertex(ofVec3f());
    }

    controlPoints.push_back(ofVec3f(-0.5, 0, 0));
    controlPoints.push_back(ofVec3f(-0.3, 0.3, 0));
    controlPoints.push_back(ofVec3f(0.3, 0.3, 0));
    controlPoints.push_back(ofVec3f(0.5, 0, 0));
}

void Curve::updateCurvePoints()
{
    for (int i = 0; i <= resolution; i++)
    {
        float t = i / (float)resolution;
        ofVec3f point = interpolate(t);
        curvePoints[i] = point;
    }
}

void Curve::draw()
{
    ofPushMatrix();
    transform.applyToModelViewMatrix();

    drawCurve();

    drawChildren();

    if (isSelected)
    {
        drawOutline();
        drawControlPoints();
    }

    ofPopMatrix();
}

void Curve::drawCurve()
{
    ofPushStyle();

    ofSetColor(curveColor);
    ofSetLineWidth(curveWidth); //TODO: take scale into consideration
    curvePoints.draw();

    ofPopStyle();
}

void Curve::drawControlPoints()
{
    ofPushStyle();

    ofSetColor(controlPointsColor);
    for (ofVec3f controlPoint : controlPoints)
    {
        ofDrawSphere(controlPoint, controlPointsRadius);
    }

    ofPopStyle();
}

ofColor Curve::getColor()
{
    return curveColor;
}

void Curve::setColor(ofColor color)
{
    curveColor = color;
}

Curve::~Curve()
{
    curvePoints.clear();
}
