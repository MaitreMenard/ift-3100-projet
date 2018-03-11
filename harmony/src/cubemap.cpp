#include "cubemap.h"

void CubeMap::setup(string fileName)
{}

void CubeMap::draw()
{
    ofPushMatrix();
    ofTranslate(position);

    texture.bind();
    cube.draw();
    texture.unbind();

    ofPopMatrix();
}

void CubeMap::translate(float dx, float dy, float dz)
{
    position += ofVec3f(dx, dy, dz);
}
