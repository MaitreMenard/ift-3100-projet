#include "bezier_curve.h"

BezierCurve::BezierCurve()
{
    texture.allocate(1, 1, GL_RGB);
    nbVertex = 0;
    gameObjectIs2D = false; //todo: true

    curveColor = ofColor(0, 255, 0);

    for (int i = 0; i <= resolution; i++)
    {
        curvePoints.addVertex(ofVec3f());
    }

    controlPoints.push_back(ofVec3f(-0.5, 0, 1));
    controlPoints.push_back(ofVec3f(0, 0.3, 0));
    controlPoints.push_back(ofVec3f(0.5, 0, -1));

    updateCurvePoints();

    //todo: update boundingBox
}

void BezierCurve::updateCurvePoints()
{
    for (int i = 0; i <= resolution; i++)
    {
        float t = i / (float)resolution;
        ofVec3f point = ofVec3f(0);
        int n = controlPoints.size() - 1;

        for (int k = 0; k <= n; k++)
        {
            point += combinations(n, k) * std::powf(t, k) * std::powf(1 - t, n - k) * controlPoints[k];
        }

        curvePoints[i] = point;
    }
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

void BezierCurve::draw()
{
    ofPushMatrix();
    transform.applyToModelViewMatrix();

    //TODO: texture.bind();
    drawCurve();
    //TODO: texture.unbind();

    for (GameObject* child : children)
    {
        child->draw();
    }

    if (isSelected)
    {
        drawBoundingBox();
        drawControlPoints();
    }

    ofPopMatrix();
}

void BezierCurve::drawCurve()
{
    ofPushStyle();

    ofSetColor(curveColor);
    ofSetLineWidth(curveWidth);
    curvePoints.draw();

    ofPopStyle();
}

void BezierCurve::drawControlPoints()
{
    ofPushStyle();

    ofSetColor(controlPointsColor);
    for (ofVec3f controlPoint : controlPoints)
    {
        ofDrawSphere(controlPoint, controlPointsRadius);
    }

    ofPopStyle();
}

ofColor BezierCurve::getColor()
{
    return curveColor;
}

void BezierCurve::setColor(ofColor color)
{
    curveColor = color;
}

BezierCurve::~BezierCurve()
{
    curvePoints.clear();
}
