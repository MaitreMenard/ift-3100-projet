#include "millenium-falcon.h"

MilleniumFalcon::MilleniumFalcon()
{
    objModel = ofxAssimpModelLoader();
    objModel.loadModel("/models/millenium-falcon/millenium-falcon.obj");
    model = objModel.getMesh(0);
    nbVertex = model.getVertices().size();
}

void MilleniumFalcon::draw()
{
    ofPushMatrix();

    ofTranslate(X_OFFSET, Y_OFFSET, Z_OFFSET);
    ofTranslate(transform.getPosition());

    ofScale(SCALE_FACTOR * transform.getScale().x, SCALE_FACTOR * transform.getScale().y, SCALE_FACTOR * transform.getScale().z);

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
