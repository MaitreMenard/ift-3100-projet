#include "point.h"


Point::Point()
{
    texture.allocate(1, 1, GL_RGB);

    nbVertex = 0;

    gameObjectIs2D = true;
    color = ofColor(255);
    radius = 0.5f;
    boundingBox.set(0.01f, 0.01f, 0.01f);
}

void Point::draw()
{
    ofPushMatrix();
    transform.applyToModelViewMatrix();

    texture.bind();
    ofPushStyle();
    ofFill();
    ofSetColor(color);
    ofDrawCircle(ofVec3f(0, 0, 0), radius);
    ofPopStyle();
    texture.unbind();

    for (GameObject* child : children)
    {
        child->draw();
    }

    if (isSelected)
    {
        drawBoundingBox();
    }

    ofPopMatrix();
}

ofColor Point::getColor()
{
    return color;
}

void Point::setColor(ofColor color)
{
    this->color = color;
}
