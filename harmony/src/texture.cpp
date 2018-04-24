#include "texture.h"

Texture::Texture(std::string name, ofPixels pixels)
{
    this->name = name;
    this->pix = pixels;
    allocate(pix);
    setTextureWrap(GL_REPEAT, GL_REPEAT);
}

Texture::Texture(const Texture& texture)
{
    this->name = texture.name;
    this->pix = texture.pix;
    allocate(pix);
    setTextureWrap(GL_REPEAT, GL_REPEAT);
}

std::string Texture::getName()
{
    return name;
}
