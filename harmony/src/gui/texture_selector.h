#pragma once
#include "ofMain.h"
#include "selector.h"

class TextureSelector : public Selector
{
private:
    const std::string headerText = "Texture";
    const std::vector<string> textureTexts = { "None" , "Cloud" , "Marble" , "Noise" , "Turbulence" , "Zoom" };

public:
    void setup();   //FIXME: use the TextureFactory to setup the object instead of using hardcoded strings
};
