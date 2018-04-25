#include "controlpoint.h"

ControlPoint::ControlPoint(std::string name, ofVec3f position) : GameObject(name, nullptr)
{
    setPosition(position);
    boundingBox.set(2 * radius);
    gameObjectIs2D = false;
    nbVertex = 0;
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
