#pragma once
#include "gameobject.h"
#include "texture.h"

class Mirror : public GameObject
{
private:
    Texture* mirrorTexture;
    void addTexCoords();
public:
    Mirror(std::string name, Texture* texture);
    ~Mirror();

    void drawTextureAndMaterial();
    void setTexturePixels(ofPixels pix);
};
