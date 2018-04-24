#include "texture.h"

Texture::Texture(std::string name, ofPixels pixels)
{
    this->name = name;
    allocate(pixels);
    setTextureWrap(GL_REPEAT, GL_REPEAT);
}

std::string Texture::getName()
{
    return name;
}
