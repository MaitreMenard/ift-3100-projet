#include "hermite_curve.h"

HermiteCurve::HermiteCurve(std::string name) : Curve(name)
{
    updateCurvePoints();
}

ofVec3f HermiteCurve::interpolate(float t)
{
    ofVec3f tangent1 = controlPoints[1] - controlPoints[0];
    ofVec3f tangent2 = controlPoints[2] - controlPoints[3];

    float t_squared = t*t;
    float t_cubed = t_squared * t;

    return (2 * t_cubed - 3 * t_squared + 1)*controlPoints[0] + (t_cubed - 2 * t_squared + t)*tangent1
        + (t_cubed - t_squared)*tangent2 + (-2 * t_cubed + 3 * t_squared)*controlPoints[3];
}

void HermiteCurve::drawOutline()
{
    ofPushStyle();
    ofSetColor(outlineColor);
    ofSetLineWidth(outlineWidth);

    ofDrawLine(controlPoints[0], controlPoints[1]);
    ofDrawLine(controlPoints[2], controlPoints[3]);

    ofPopStyle();
}
