#include "grid_plane.h"

GridPlane::GridPlane()
{
    
}

void GridPlane::setup()
{
    ofLoadImage(texture, "grid.png");
    texture.setTextureWrap(GL_REPEAT, GL_REPEAT);

    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    mesh.addVertex(ofVec3f(-10, 0, 10));
    mesh.addTexCoord(texture.getCoordFromPercent(0, 0));
    mesh.addVertex(ofVec3f(-10, 0, -10));
    mesh.addTexCoord(texture.getCoordFromPercent(0, 5));
    mesh.addVertex(ofVec3f(10, 0, 10));
    mesh.addTexCoord(texture.getCoordFromPercent(5, 0));
    mesh.addVertex(ofVec3f(10, 0, -10));
    mesh.addTexCoord(texture.getCoordFromPercent(5, 5));
}

void GridPlane::draw()
{
    texture.bind();
    mesh.draw();
    texture.unbind();
}
