#include "line.h"


Line::Line()
{
    texture.allocate(1, 1, GL_RGB);

    nbVertex = 2;
    model.addVertex(ofVec3f(-1.f, -0, 0.f));
    model.addTexCoord(texture.getCoordFromPercent(0, 0));
    model.addVertex(ofVec3f(1.f, 0, 0.f));
    model.addTexCoord(texture.getCoordFromPercent(1, 1));

    model.addIndex(0);
    model.addIndex(1);

    gameObjectIs2D = true;
}

void Line::draw()
{
    ofPushMatrix();
    transform.applyToModelViewMatrix();

    texture.bind();
    model.draw();
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