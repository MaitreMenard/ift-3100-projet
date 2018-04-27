#pragma once
#include "ofMain.h"

class fboRenderer
{
private:
	int fboIter;
	ofFbo fboFirstPass, fboSecondPass;
	ofShader shaderBlurX, shaderBlurY, shaderBlackWhite, shaderSepia, shader8bits, shaderEdge, shaderEdgeLayer, shaderGray, shaderMult;

	// Blur parameters
	bool blurIsSet_;
	float blurValue_;
	int blurIterations_;

	// Black and White
	bool blackWhiteIsSet_;

	// Sepia
	bool sepiaIsSet_;

	// 8bits
	bool toonIsSet_;

public:
	fboRenderer();
	~fboRenderer();

	void setup();
	void apply(ofFbo * pFbo);
	void setBlurParam(float pBlurValue, int pBlurIteration);
	void enableBlur();
	void disableBlur();
	bool isBlurSet();
	void enableBW();
	void disableBW();
	bool isBlackWhiteSet();
	void enableSepia();
	void disableSepia();
	bool isSepiaSet();
	void enableToon();
	void disableToon();
	bool is8bitsSet();
	void resize();
	void next();
};
