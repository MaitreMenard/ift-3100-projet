#pragma once
#include "ofMain.h"

/*
	Ressource: http://lodev.org/cgtutor/randomnoise.html
*/
class texelFactory
{
private:
	ofColor texelFactory::convertHslToHsb(int h, int s, int l);
	float linearInterpolation(const ofImage & image, float x, float y);
	float turbulence(const ofImage & image, float x, float y, float size);
public:
	texelFactory();
	~texelFactory();

	void setNoise(ofImage * p_img);
	void setZoom(ofImage * image, float zoom);
	void setTurbulenceImage(ofImage * image, float size);
	void setCloudImage(ofImage * image, float size);
	void setMarbleTexture(ofImage * image, float xPeriod, float yPeriod, float TurbPower, float TurbSize);
	void setWoodTexture(ofImage * image, float numberRings, float TurbPower, float TurbSize);
};
