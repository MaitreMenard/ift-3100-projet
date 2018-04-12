#pragma once
#include "ofMain.h"

/*
    Ressource: http://lodev.org/cgtutor/randomnoise.html
*/
class texelFactory
{
private:
    ofColor texelFactory::convertHslToHsb(int h, int s, int l);
    float linearInterpolation(const ofPixels & image, float x, float y);
    float turbulence(const ofPixels & image, float x, float y, float size);
	ofPixels * noise(ofPixels * image);

	ofPixels * textureNoise_;
	ofPixels * textureZoom_;
	ofPixels * textureTurbulence_;
	ofPixels * textureCloud_;
	ofPixels * textureMarble_;
	ofPixels * textureWood_;
public:
    texelFactory();
    ~texelFactory();

    ofPixels * setNoise(ofPixels * image);
    ofPixels * setZoom(ofPixels * image, float zoom);
    ofPixels * setTurbulenceImage(ofPixels * image, float size);
    ofPixels * setCloudImage(ofPixels * image, float size);
    ofPixels * setMarbleTexture(ofPixels * image, float xPeriod, float yPeriod, float TurbPower, float TurbSize);
    ofPixels * setWoodTexture(ofPixels * image, float numberRings, float TurbPower, float TurbSize);
};
