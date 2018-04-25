#include "model3D.h"
#include "gameobject_visitor.h"

Model3D::Model3D(std::string name, std::string fileName, ofVec3f positionOffset=ofVec3f(0, 0, 0), float rotationOffsetAngle=0,
    ofVec3f rotationOffsetAxis=ofVec3f(0, 0, 0), ofVec3f scaleFactor=ofVec3f(1, 1, 1)) : GameObject(name, nullptr)
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
    drawChildren();

    ofPopMatrix();
}

void Model3D::setColor(ofColor color)
{}

void Model3D::accept(GameObjectVisitor & visitor)
{
    visitor.visit(this);
}
