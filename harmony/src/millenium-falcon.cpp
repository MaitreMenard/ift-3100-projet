#include "millenium-falcon.h"

MilleniumFalcon::MilleniumFalcon()
{
    objModel = ofxAssimpModelLoader();
    objModel.loadModel("/models/millenium-falcon/millenium-falcon.obj");

    fixModel();

    model = objModel.getMesh(0);
    nbVertex = model.getVertices().size();
}

void MilleniumFalcon::fixModel()
{
    objModel.setPosition(POSITION_OFFSET.x, POSITION_OFFSET.y, POSITION_OFFSET.z);
    objModel.setScale(SCALE_FACTOR.x, SCALE_FACTOR.y, SCALE_FACTOR.z);
    objModel.setRotation(0, ROTATION_ANGLE, ROTATION_AXIS.x, ROTATION_AXIS.y, ROTATION_AXIS.z);
}

void MilleniumFalcon::draw()
{
    ofPushMatrix();

    ofTranslate(transform.getPosition());

    float angle, x, y, z;
    transform.getRotate(angle, x, y, z);
    ofRotate(angle, x, y, z);

    objModel.draw(OF_MESH_FILL);
    for (GameObject* child : children)
    {
        child->draw();
    }

    ofPopMatrix();
}

void MilleniumFalcon::setColor(ofColor color)
{}
