#include "line.h"


Line::Line()
{
    texture.allocate(1, 1, GL_RGB);

    nbVertex = 0;

    gameObjectIs2D = true;
    color = ofColor(255);
    lineWidth = 5;
    boundingBox.set(1, 0.01f, 0.01f);
}

void Line::draw()
{
    ofPushMatrix();
    transform.applyToModelViewMatrix();

    texture.bind();
    ofPushStyle();
    ofSetLineWidth(lineWidth);
    ofFill();
    ofSetColor(color);
    ofDrawLine(ofVec3f(-0.5f, 0.f, 0.f), ofVec3f(0.5f, 0.f, 0.f));
    ofPopStyle();
    texture.unbind();

    drawChildren();

    if (isSelected)
    {
        drawBoundingBox();
    }

    ofPopMatrix();
}

ofColor Line::getColor()
{
    return color;
}

void Line::setColor(ofColor color)
{
    this->color = color;
}
