#include "model3D.h"

Model3D::Model3D(string fileName)
{
    Model3D(fileName, ofVec3f(0, 0, 0), 0, ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));
}

Model3D::Model3D(string fileName, ofVec3f positionOffset, float rotationOffsetAngle, ofVec3f rotationOffsetAxis, ofVec3f scaleFactor)
{
    objModel = ofxAssimpModelLoader();
    objModel.loadModel(fileName);

    objModel.setPosition(positionOffset.x, positionOffset.y, positionOffset.z);
    objModel.setScale(scaleFactor.x, scaleFactor.y, scaleFactor.z);
    objModel.setRotation(0, rotationOffsetAngle, rotationOffsetAxis.x, rotationOffsetAxis.y, rotationOffsetAxis.z);

    model = objModel.getMesh(0);
    nbVertex = model.getVertices().size();
}

void Model3D::draw()
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

void Model3D::setColor(ofColor color)
{}
