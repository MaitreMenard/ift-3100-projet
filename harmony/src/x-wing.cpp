#include "x-wing.h"

XWing::XWing()
{
    objModel = ofxAssimpModelLoader();
    objModel.loadModel("/models/xwing/x-wing.obj");

    fixModel();

    model = objModel.getMesh(0);
    nbVertex = model.getVertices().size();
}

void XWing::fixModel()
{
    objModel.setPosition(POSITION_OFFSET.x, POSITION_OFFSET.y, POSITION_OFFSET.z);
    objModel.setScale(SCALE_FACTOR.x, SCALE_FACTOR.y, SCALE_FACTOR.z);
    objModel.setRotation(0, ROTATION_ANGLE, ROTATION_AXIS.x, ROTATION_AXIS.y, ROTATION_AXIS.z);
}

void XWing::draw()
{
    ofPushMatrix();

    transform.applyToModelViewMatrix();

    objModel.draw(OF_MESH_FILL);
    for (GameObject* child : children)
    {
        child->draw();
    }

    ofPopMatrix();
}

void XWing::setColor(ofColor color)
{}
