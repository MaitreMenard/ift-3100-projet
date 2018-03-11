#include "grid_plane.h"

GridPlane::GridPlane()
{
    
}

void GridPlane::setup()
{
    ofLoadImage(texture, "grid2.png");
    texture.setTextureWrap(GL_REPEAT, GL_REPEAT);

    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    mesh.addVertex(ofVec3f(-50, 0, 50));
    mesh.addTexCoord(texture.getCoordFromPercent(0, 0));
    mesh.addVertex(ofVec3f(-50, 0, -50));
    mesh.addTexCoord(texture.getCoordFromPercent(0, 10));
    mesh.addVertex(ofVec3f(50, 0, 50));
    mesh.addTexCoord(texture.getCoordFromPercent(10, 0));
    mesh.addVertex(ofVec3f(50, 0, -50));
    mesh.addTexCoord(texture.getCoordFromPercent(10, 10));
}

void GridPlane::draw()
{
    texture.bind();
    mesh.draw();
    texture.unbind();
}
