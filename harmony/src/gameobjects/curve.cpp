#include "curve.h"
#include "gameobject_visitor.h"

Curve::Curve(std::string name) : GameObject(name, nullptr)
{
    nbVertex = 0;
    gameObjectIs2D = false;

    curveColor = ofColor(255, 0, 0);

    for (int i = 0; i <= resolution; i++)
    {
        curvePoints.addVertex(ofVec3f());
    }

    controlPoints.push_back(createControlPoint(ofVec3f(-0.5, 0, 0)));
    controlPoints.push_back(createControlPoint(ofVec3f(-0.3, 0.3, 0)));
    controlPoints.push_back(createControlPoint(ofVec3f(0.3, 0.3, 0)));
    controlPoints.push_back(createControlPoint(ofVec3f(0.5, 0, 0)));
}

ControlPoint * Curve::createControlPoint(ofVec3f position)
{
    std::string name = baseControlPointName + std::to_string(controlPoints.size());
    return new ControlPoint(name, position, this);
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
    for (ControlPoint* controlPoint : controlPoints)
    {
        controlPoint->draw();
    }
}

ofColor Curve::getColor()
{
    return curveColor;
}

void Curve::setColor(ofColor color)
{
    curveColor = color;
}

void Curve::accept(GameObjectVisitor & visitor)
{
    visitor.visit(this);
}

std::vector<ControlPoint*> Curve::getControlPoints()
{
    return controlPoints;
}

Curve::~Curve()
{
    for (ControlPoint* controlPoint : controlPoints)
    {
        delete controlPoint;
    }
    curvePoints.clear();
}
