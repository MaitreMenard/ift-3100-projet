
#include "fboRenderer.h"

fboRenderer::fboRenderer(){}
fboRenderer::~fboRenderer(){}

void fboRenderer::setup() {
	// setup blur param / shaders
	blurValue_ = 2;
	blurIterations_ = 2;
	blurIsSet_ = false;

#ifdef TARGET_OPENGLES
	shaderBlurX.load("shadersES2/shaderBlurX");
	shaderBlurY.load("shadersES2/shaderBlurY");
#else
	if (ofIsGLProgrammableRenderer()) {
		shaderBlurX.load("shadersGL3/shaderBlurX");
		shaderBlurY.load("shadersGL3/shaderBlurY");
	}
	else {
		shaderBlurX.load("shadersGL2/shaderBlurX");
		shaderBlurY.load("shadersGL2/shaderBlurY");
	}
#endif

	// setup black and white shaders
	blackWhiteIsSet_ = false;
	shaderBlackWhite.load("shaders/blackwhite");

	// setup sepia shaders
	sepiaIsSet_ = false;
	shaderSepia.load("shaders/sepia");

	// setup edge detection shaders
	edgeDetectionIsSet_ = false;
	shaderEdgeDetect.load("shaders/edgedetection");
	shaderGray.load("shaders/gray");

	// setup fbo allocation
	fboFirstPass.allocate(ofGetWidth(), ofGetHeight());
	fboSecondPass.allocate(ofGetWidth(), ofGetHeight());
}

void fboRenderer::apply(ofFbo * pFbo) {
	if (edgeDetectionIsSet_) {
		fboFirstPass.begin();
		ofClear(0, 0, 0);
		shaderGray.begin();
		pFbo->draw(0, 0, ofGetWidth(), ofGetHeight());
		shaderGray.end();
		fboFirstPass.end();

		pFbo->begin();
		shaderEdgeDetect.begin();
		ofClear(0, 0, 0);
		fboFirstPass.draw(0, 0, ofGetWidth(), ofGetHeight());
		shaderEdgeDetect.end();
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

void fboRenderer::enableEdgeDetection() {
	edgeDetectionIsSet_ = true;
}
void fboRenderer::disableEdgeDetection() {
	edgeDetectionIsSet_ = false;
}
bool fboRenderer::isEdgeDetectionSet() {
	return edgeDetectionIsSet_;
}

void fboRenderer::resize() {
	fboFirstPass.allocate(ofGetWidth(), ofGetHeight());
}