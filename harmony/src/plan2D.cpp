#include "plan2D.h"


plan2D::plan2D()
{
    texture.allocate(1, 1, GL_RGB);

    nbVertex = 4;
    model.setMode(OF_PRIMITIVE_TRIANGLES);
    model.addVertex(ofVec3f(0.f, 0.f, 0.f));
    model.addTexCoord(texture.getCoordFromPercent(0, 0));
    model.addVertex(ofVec3f(0.f, 1.f, 0.f));
    model.addTexCoord(texture.getCoordFromPercent(0, 1));
    model.addVertex(ofVec3f(1.f, 1.f, 0.f));
    model.addTexCoord(texture.getCoordFromPercent(1, 1));
    model.addVertex(ofVec3f(1.f, 0.f, 0.f));
    model.addTexCoord(texture.getCoordFromPercent(0, 1));

    model.addIndex(0);
    model.addIndex(1);
    model.addIndex(2);

    model.addIndex(3);
    model.addIndex(0);
    model.addIndex(2);
}

void plan2D::draw()
{
    texture.bind();
    model.draw();
    texture.unbind();
}