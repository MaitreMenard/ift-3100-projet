#pragma once
#include "ofMain.h"

class Texture : public ofTexture
{
public:
    Texture(std::string name, ofPixels pixels);
    Texture(const Texture& texture);
    std::string getName();

private:
    std::string name;
    ofPixels pix;
};
