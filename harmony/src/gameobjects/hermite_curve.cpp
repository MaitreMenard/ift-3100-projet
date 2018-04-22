#include "hermite_curve.h"

HermiteCurve::HermiteCurve()
{
    updateCurvePoints();
}

ofVec3f HermiteCurve::interpolate(float t)
{
    //TODO
    return ofVec3f();
}

void HermiteCurve::drawOutline()
{
    //TODO: draw lines between control points 1-2 and 3-4
}
