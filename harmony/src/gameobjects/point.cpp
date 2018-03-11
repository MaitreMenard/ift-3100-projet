#include "point.h"


Point::Point()
{
    texture.allocate(1, 1, GL_RGB);

    nbVertex = 1;

    model.addVertex(ofVec3f(-1.f, -0, 0.f));
    model.addTexCoord(texture.getCoordFromPercent(0, 0));
}