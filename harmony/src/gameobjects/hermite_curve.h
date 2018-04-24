#pragma once
#include "ofMain.h"
#include "curve.h"
#include "texture.h"

class HermiteCurve : public Curve
{
public:
    HermiteCurve(std::string name, Texture* texture);

private:
    ofVec3f interpolate(float t);
    void drawOutline();
};
