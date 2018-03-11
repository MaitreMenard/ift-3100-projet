#include "skybox.h"


void SkyBox::setup(string fileNames[6])
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for (unsigned int i = 0; i < 6; i++)
    {
        ofImage image;
        image.load(fileNames[i]);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, image.getWidth(), image.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.getPixels().getData());
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void SkyBox::draw()
{
    ofPushMatrix();
    ofDisableDepthTest();
    shader.begin();

    //ofTranslate(position);

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    //texture.bind();
    cube.draw();
    //texture.unbind();

    shader.end();
    ofEnableDepthTest();
    ofPopMatrix();
}

void SkyBox::translate(float dx, float dy, float dz)
{
    position += ofVec3f(dx, dy, dz);
}
