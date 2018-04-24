#pragma once
#include "ofMain.h"
#include "texture.h"

/*
    Ressource: http://lodev.org/cgtutor/randomnoise.html
*/
class TextureFactory
{
public:
    TextureFactory();
    ~TextureFactory();

    std::vector<Texture*> getAllTextures();
    Texture* getEmptyTexture();

private:
    std::vector<Texture*> textures;

    ofPixels initPixels();

    void setNoise(ofPixels& image);
    void setZoom(ofPixels& image, float zoom);
    void setTurbulence(ofPixels& image, float size);
    void setCloud(ofPixels& image, float size);
    void setMarble(ofPixels& image, float xPeriod, float yPeriod, float TurbPower, float TurbSize);
    void setWood(ofPixels& image, float numberRings, float TurbPower, float TurbSize);

    ofColor convertHslToHsb(int h, int s, int l);
    float linearInterpolation(const ofPixels & image, float x, float y);
    float turbulence(const ofPixels & image, float x, float y, float size);
};
