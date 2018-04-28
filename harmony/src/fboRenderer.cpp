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
    blurIsSet_ = false;
    shaderBlurX.load("shadersGL3/shaderBlurX");
    shaderBlurY.load("shadersGL3/shaderBlurY");


    // setup black and white shaders
    blackWhiteIsSet_ = false;
    shaderBlackWhite.load("shaders/blackwhite");

    // setup sepia shaders
    sepiaIsSet_ = false;
    shaderSepia.load("shaders/sepia");

    // setup toon shaders
    toonIsSet_ = false;
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
    if (toonIsSet_)
    {
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

    if (blurIsSet_)
    {
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
    }

    if (blackWhiteIsSet_)
    {
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

    if (sepiaIsSet_)
    {
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

void FboRenderer::setBlurParam(float pBlurValue, int pBlurIteration)
{
    blurValue_ = pBlurValue;
    blurIterations_ = pBlurIteration;
}

void FboRenderer::enableBlur()
{
    blurIsSet_ = true;
}

void FboRenderer::disableBlur()
{
    blurIsSet_ = false;
}

bool FboRenderer::isBlurSet()
{
    return blurIsSet_;
}

void FboRenderer::enableBW()
{
    blackWhiteIsSet_ = true;
}

void FboRenderer::disableBW()
{
    blackWhiteIsSet_ = false;
}

bool FboRenderer::isBlackWhiteSet()
{
    return blackWhiteIsSet_;
}

void FboRenderer::enableSepia()
{
    sepiaIsSet_ = true;
}
void FboRenderer::disableSepia()
{
    sepiaIsSet_ = false;
}
bool FboRenderer::isSepiaSet()
{
    return sepiaIsSet_;
}

void FboRenderer::enableToon()
{
    toonIsSet_ = true;
}

void FboRenderer::disableToon()
{
    toonIsSet_ = false;
}

bool FboRenderer::is8bitsSet()
{
    return toonIsSet_;
}

void FboRenderer::resize()
{
    fboFirstPass.allocate(ofGetWidth(), ofGetHeight());
}

void FboRenderer::next()
{
    fboEffect = (effectType)(((int)fboEffect + 1) % 5);
    switch (fboEffect)
    {
    case effectType::none:
        effectName = "No effect";
        disableBlur();
        disableBW();
        disableSepia();
        disableToon();
        isActive = false;
        break;
    case effectType::blur:
        effectName = "Gaussian Blur";
        enableBlur();
        disableBW();
        disableSepia();
        disableToon();
        isActive = true;
        break;
    case effectType::black_white:
        effectName = "Black and White";
        disableBlur();
        enableBW();
        disableSepia();
        disableToon();
        isActive = true;
        break;
    case effectType::sepia:
        effectName = "Sepia";
        disableBlur();
        disableBW();
        enableSepia();
        disableToon();
        isActive = true;
        break;
    case effectType::toon:
        effectName = "Toon";
        disableBlur();
        disableBW();
        disableSepia();
        enableToon();
        isActive = true;
        break;
    default:
        break;
    }
}

void FboRenderer::onWindowResized()
{
    fboFirstPass.allocate(ofGetWidth(), ofGetHeight());
    fboSecondPass.allocate(ofGetWidth(), ofGetHeight());
}
