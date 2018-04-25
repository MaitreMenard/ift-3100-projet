#include "controlpoint.h"
#include "curve.h"

ControlPoint::ControlPoint(std::string name, ofVec3f position, Curve* curve) : GameObject(name, nullptr)
{
    transform.setPosition(position);
    boundingBox.set(2 * radius);
    gameObjectIs2D = false;
    nbVertex = 0;
    this->curve = curve;
}

void ControlPoint::draw()
{
    ofPushMatrix();
    transform.applyToModelViewMatrix();

    ofPushStyle();
    ofSetColor(color);
    ofDrawSphere(radius);
    ofPopStyle();

    if (isSelected)
    {
        drawBoundingBox();
    }

    ofPopMatrix();
}

Curve * ControlPoint::getCurve()
{
    return curve;
}

void ControlPoint::setPosition(ofVec3f position)
{
    GameObject::setPosition(position);
    curve->updateCurvePoints();
}

void ControlPoint::setSelected(bool isSelected)
{
    GameObject::setSelected(isSelected);

    curve->setSelected(isSelected);
}
