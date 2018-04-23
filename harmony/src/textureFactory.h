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
    const std::vector<string> textureNames = { "None" , "Cloud" , "Marble" , "Noise" , "Turbulence" , "Zoom" };
    std::vector<Texture*> textures;

    ofPixels initPixels();

    ofPixels& setNoise(ofPixels& image);
    ofPixels& setZoom(ofPixels& image, float zoom);
    ofPixels& setTurbulence(ofPixels& image, float size);
    ofPixels& setCloud(ofPixels& image, float size);
    ofPixels& setMarble(ofPixels& image, float xPeriod, float yPeriod, float TurbPower, float TurbSize);
    ofPixels& setWood(ofPixels& image, float numberRings, float TurbPower, float TurbSize);

    ofColor convertHslToHsb(int h, int s, int l);
    float linearInterpolation(const ofPixels & image, float x, float y);
    float turbulence(const ofPixels & image, float x, float y, float size);
};
