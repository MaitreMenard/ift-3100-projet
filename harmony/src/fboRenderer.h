#pragma once
#include "ofMain.h"

class fboRenderer
{
private:
	ofFbo fboFirstPass, fboSecondPass;
	ofShader shaderBlurX, shaderBlurY, shaderBlackWhite, shaderSepia, shaderEdgeDetect, shaderGray;
	
	// Blur parameters
	bool blurIsSet_;
	float blurValue_;
	int blurIterations_;

	// Black and White
	bool blackWhiteIsSet_;

	// Sepia
	bool sepiaIsSet_;

	// EdgeDetection
	bool edgeDetectionIsSet_;

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
	void enableEdgeDetection();
	void disableEdgeDetection();
	bool isEdgeDetectionSet();
	void resize();
};
