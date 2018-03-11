#include "skybox.h"

void SkyBox::setup(string fileName)
{}

void SkyBox::draw()
{
    ofPushMatrix();
    ofTranslate(position);

    //texture.bind();
    cube.draw();
    //texture.unbind();

    ofPopMatrix();
}

void SkyBox::translate(float dx, float dy, float dz)
{
    position += ofVec3f(dx, dy, dz);
}
