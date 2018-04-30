#pragma once
#include "ofMain.h"

enum class effectType { none, blur, gray, black_white, sepia, toon };

class FboRenderer
{
private:
    bool isActive;
    string effectName;
    effectType fboEffect;
    ofFbo fboFirstPass, fboSecondPass;
    ofShader shaderBlurX, shaderBlurY, shaderBlackWhite, shaderSepia, shader8bits, shaderEdge, shaderEdgeLayer, shaderGray, shaderMult;

    // Blur parameters
    float blurValue_;
	int blurIterations_;

public:
    FboRenderer();
    ~FboRenderer();

    bool isActiveEffect() { return isActive; };;
    string getEffectName() { return effectName; };
    void setup();
    void apply(ofFbo * pFbo);
    void setBlurParam(float pBlurValue, int pBlurIteration);
    void resize();
    void next();

    void onWindowResized();
};
