
#include "fboRenderer.h"

fboRenderer::fboRenderer() {}
fboRenderer::~fboRenderer() {}

void fboRenderer::setup() {
	// setup blur param / shaders
	fboIter = 0;
	blurValue_ = 2;
	blurIterations_ = 2;
	blurIsSet_ = false;
	shaderBlurX.load("shadersGL3/shaderBlurX");
	shaderBlurY.load("shadersGL3/shaderBlurY");


	// setup black and white shaders
	blackWhiteIsSet_ = false;
	shaderBlackWhite.load("shaders/blackwhite");

	// setup sepia shaders
	sepiaIsSet_ = false;
	shaderSepia.load("shaders/sepia");

	// setup 8bits shaders
	bitsIsSet_ = false;
	shader8bits.load("shaders/colorbits");
	shaderEdge.load("shaders/edgesobel");
	shaderGray.load("shaders/gray");
	shaderMult.load("shaders/multiple");
	shaderEdgeLayer.load("shaders/edgewidth");

	// setup fbo allocation
	fboFirstPass.allocate(ofGetWidth(), ofGetHeight());
	fboSecondPass.allocate(ofGetWidth(), ofGetHeight());
}

void fboRenderer::apply(ofFbo * pFbo) {
	if (bitsIsSet_) {
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
	}

	if (blurIsSet_) {
		for (int i = 0; i < blurIterations_; i++) {
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
	}

	if (blackWhiteIsSet_) {
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
	}

	if (sepiaIsSet_) {
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
	}
}

void fboRenderer::setBlurParam(float pBlurValue, int pBlurIteration) {
	blurValue_ = pBlurValue;
	blurIterations_ = pBlurIteration;
}

void fboRenderer::enableBlur() {
	blurIsSet_ = true;
}

void fboRenderer::disableBlur() {
	blurIsSet_ = false;
}

bool fboRenderer::isBlurSet() {
	return blurIsSet_;
}

void fboRenderer::enableBW() {
	blackWhiteIsSet_ = true;
}

void fboRenderer::disableBW() {
	blackWhiteIsSet_ = false;
}

bool fboRenderer::isBlackWhiteSet() {
	return blackWhiteIsSet_;
}

void fboRenderer::enableSepia() {
	sepiaIsSet_ = true;
}
void fboRenderer::disableSepia() {
	sepiaIsSet_ = false;
}
bool fboRenderer::isSepiaSet() {
	return sepiaIsSet_;
}

void fboRenderer::enable8bits() {
	bitsIsSet_ = true;
}

void fboRenderer::disable8bits() {
	bitsIsSet_ = false;
}

bool fboRenderer::is8bitsSet() {
	return bitsIsSet_;
}

void fboRenderer::resize() {
	fboFirstPass.allocate(ofGetWidth(), ofGetHeight());
}

void fboRenderer::next() {
	switch (++fboIter % 5)
	{
	case 0:
		disableBlur();
		disableBW();
		disableSepia();
		disable8bits();
		break;
	case 1:
		enableBlur();
		disableBW();
		disableSepia();
		disable8bits();
		break;
	case 2:
		disableBlur();
		enableBW();
		disableSepia();
		disable8bits();
		break;
	case 3:
		disableBlur();
		disableBW();
		enableSepia();
		disable8bits();
		break;
	case 4:
		disableBlur();
		disableBW();
		disableSepia();
		enable8bits();
		break;
	default:
		break;
	}
}