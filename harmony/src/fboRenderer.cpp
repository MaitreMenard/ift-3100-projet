
#include "fboRenderer.h"

fboRenderer::fboRenderer(){}
fboRenderer::~fboRenderer(){}

void fboRenderer::setup() {
	// setup blur param
	blurValue_ = 2;
	blurIterations_ = 2;
	blurIsSet_ = false;

	// setup fbo allocation
	fboBlur.allocate(ofGetWidth(), ofGetHeight());

	// setup sharders
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
}

void fboRenderer::apply(ofFbo * pFbo) {
	if(blurIsSet_){
		for (int i = 0; i < blurIterations_; i++) {
			fboBlur.begin();
			ofClear(0);
			shaderBlurX.begin();
			shaderBlurX.setUniform1f("blurAmnt", blurValue_);
			pFbo->draw(0, 0, ofGetWidth(), ofGetHeight());
			shaderBlurX.end();
			fboBlur.end();

			pFbo->begin();
			ofClear(0);
			shaderBlurY.begin();
			shaderBlurY.setUniform1f("blurAmnt", blurValue_);
			fboBlur.draw(0, 0, ofGetWidth(), ofGetHeight());
			shaderBlurY.end();
			pFbo->end();
		}
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

void fboRenderer::resize() {
	fboBlur.allocate(ofGetWidth(), ofGetHeight());
}