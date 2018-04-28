#include "fboRenderer.h"

FboRenderer::FboRenderer() {}
FboRenderer::~FboRenderer() {}

void FboRenderer::setup()
{
    // setup blur param / shaders
    effectName = "No effect";
    fboEffect = effectType::none;
    isActive = false;
    blurValue_ = 2;
    blurIterations_ = 2;
    shaderBlurX.load("shadersGL3/shaderBlurX");
    shaderBlurY.load("shadersGL3/shaderBlurY");


    // setup black and white shaders
    shaderBlackWhite.load("shaders/blackwhite");

    // setup sepia shaders
    shaderSepia.load("shaders/sepia");

    // setup toon shaders
    shader8bits.load("shaders/colorbits");
    shaderEdge.load("shaders/edgesobel");
    shaderGray.load("shaders/gray");
    shaderMult.load("shaders/multiple");

    // setup fbo allocation
    fboFirstPass.allocate(ofGetWidth(), ofGetHeight());
    fboSecondPass.allocate(ofGetWidth(), ofGetHeight());
}

void FboRenderer::apply(ofFbo * pFbo)
{
	switch (fboEffect)
	{
	case effectType::none:
		effectName = "No effect";
		break;
	case effectType::blur:
		effectName = "Gaussian Blur";
		for (int i = 0; i < blurIterations_; i++)
		{
			fboFirstPass.begin();
			ofClear(0, 0, 0);
			shaderBlurX.begin();
			shaderBlurX.setUniform1f("blurAmnt", blurValue_);
			pFbo->draw(0, 0, ofGetWidth(), ofGetHeight());
			shaderBlurX.end();
			fboFirstPass.end();

			pFbo->begin();
			ofClear(0);
			shaderBlurY.begin();
			shaderBlurY.setUniform1f("blurAmnt", blurValue_);
			fboFirstPass.draw(0, 0, ofGetWidth(), ofGetHeight());
			shaderBlurY.end();
			pFbo->end();
		}
		isActive = true;
		break;
	case effectType::gray:
		effectName = "Gray";
		fboFirstPass.begin();
		ofClear(0);
		shaderGray.begin();
		pFbo->draw(0, 0, ofGetWidth(), ofGetHeight());
		shaderGray.end();
		fboFirstPass.end();

		pFbo->begin();
		ofClear(0);
		fboFirstPass.draw(0, 0, ofGetWidth(), ofGetHeight());
		pFbo->end();
		isActive = true;
		break;
	case effectType::black_white:
		effectName = "Black and White";
		fboSecondPass.begin();
		ofClear(0, 0, 0);
		shaderBlackWhite.begin();
		pFbo->draw(0, 0, ofGetWidth(), ofGetHeight());
		shaderBlackWhite.end();
		fboSecondPass.end();

		pFbo->begin();
		ofClear(0, 0, 0);
		fboSecondPass.draw(0, 0, ofGetWidth(), ofGetHeight());
		pFbo->end();
		isActive = true;
		break;
	case effectType::sepia:
		effectName = "Sepia";
		fboSecondPass.begin();
		ofClear(0, 0, 0);
		shaderSepia.begin();
		pFbo->draw(0, 0, ofGetWidth(), ofGetHeight());
		shaderSepia.end();
		fboSecondPass.end();

		pFbo->begin();
		ofClear(0, 0, 0);
		fboSecondPass.draw(0, 0, ofGetWidth(), ofGetHeight());
		pFbo->end();
		isActive = true;
		break;
	case effectType::toon:
		effectName = "Toon";

		// make edge detection mask
		fboFirstPass.begin();
		ofClear(0, 0, 0);
		shaderGray.begin();
		pFbo->draw(0, 0, ofGetWidth(), ofGetHeight());
		shaderGray.end();
		fboFirstPass.end();

		fboSecondPass.begin();
		ofClear(0, 0, 0);
		shaderBlackWhite.begin();
		fboFirstPass.draw(0, 0, ofGetWidth(), ofGetHeight());
		shaderBlackWhite.end();
		fboSecondPass.end();

		fboFirstPass.begin();
		ofClear(0, 0, 0);
		shaderEdge.begin();
		fboSecondPass.draw(0, 0, ofGetWidth(), ofGetHeight());
		shaderEdge.end();
		fboFirstPass.end();

		// make edge detection mask
		fboSecondPass.begin();
		ofClear(0, 0, 0);
		shader8bits.begin();
		pFbo->draw(0, 0, ofGetWidth(), ofGetHeight());
		shader8bits.end();
		fboSecondPass.end();

		pFbo->begin();
		ofClear(0, 0, 0);
		shaderMult.begin();
		shaderMult.setUniformTexture("texEdge", fboFirstPass.getTextureReference(), 1);
		fboSecondPass.draw(0, 0, ofGetWidth(), ofGetHeight());
		shaderMult.end();
		pFbo->end();
		isActive = true;
		break;
	default:
		break;
	}
}

void FboRenderer::setBlurParam(float pBlurValue, int pBlurIteration)
{
    blurValue_ = pBlurValue;
    blurIterations_ = pBlurIteration;
}

void FboRenderer::resize()
{
    //fboFirstPass.allocate(ofGetWidth(), ofGetHeight());
	//fboSecondPass.allocate(ofGetWidth(), ofGetHeight());
}

void FboRenderer::next()
{
    fboEffect = (effectType)(((int)fboEffect + 1) % 6);
}

void FboRenderer::onWindowResized()
{
    //fboFirstPass.allocate(ofGetWidth(), ofGetHeight());
    //fboSecondPass.allocate(ofGetWidth(), ofGetHeight());
}
