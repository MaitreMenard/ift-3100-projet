#pragma once
#include "ofMain.h"
#include "selector.h"
#include "texture.h"
#include "textureFactory.h"

class TextureSelector : public Selector<Texture*>
{
private:
    const std::string headerText = "Texture";

public:
    void setup(TextureFactory& textureFactory);
    void onWindowResized();
};
