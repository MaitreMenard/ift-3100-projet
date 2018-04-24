#pragma once
#include "ofMain.h"

class Texture : public ofTexture
{
public:
    Texture(std::string name, ofPixels pixels);
    std::string getName();

private:
    std::string name;
};
