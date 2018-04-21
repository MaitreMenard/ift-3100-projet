#pragma once
#include "ofMain.h"

class fboRenderer
{
private:
	ofFbo fboBlur;
	ofShader shaderBlurX, shaderBlurY;
	
	// Blur parameters
	bool blurIsSet_;
	float blurValue_;
	int blurIterations_;

public:
	fboRenderer();
	~fboRenderer();

	void setup();
	void apply(ofFbo * pFbo);
	void setBlurParam(float pBlurValue, int pBlurIteration);
	void enableBlur();
	void disableBlur();
	bool isBlurSet();
	void resize();
};
