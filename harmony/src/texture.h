#pragma once
#include "ofMain.h"

class Texture : public ofTexture
{
public:
    std::string name;

    Texture(std::string name, ofPixels* pixels);
    std::string getName();
};
