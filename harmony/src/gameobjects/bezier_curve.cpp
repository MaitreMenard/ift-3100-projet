#include "bezier_curve.h"

BezierCurve::BezierCurve()
{
    updateCurvePoints();
}

ofVec3f BezierCurve::interpolate(float t)
{
    ofVec3f point = ofVec3f(0);
    int n = controlPoints.size() - 1;

    for (int k = 0; k <= n; k++)
    {
        point += combinations(n, k) * std::powf(t, k) * std::powf(1 - t, n - k) * controlPoints[k];
    }

    return point;
}

int BezierCurve::combinations(int n, int k)
{
    // Taken from https://stackoverflow.com/questions/9330915/number-of-combinations-n-choose-r-in-c?noredirect=1&lq=1

    if (k == 0) return 1;
    if (k > n) return 0;
    if (k > n / 2) k = n - k;

    int result = 1;

    for (int r = 1; r <= k; r++)
    {
        result *= n - r + 1;
        result /= r;
    }

    return result;
}

void BezierCurve::drawOutline()
{
    ofPushStyle();
    ofSetColor(outlineColor);
    ofSetLineWidth(outlineWidth);

    for (int i = 0; i < controlPoints.size() - 1; i++)
    {
        ofDrawLine(controlPoints[i], controlPoints[i + 1]);
    }
    ofDrawLine(controlPoints[controlPoints.size() - 1], controlPoints[0]);

    ofPopStyle();
}

