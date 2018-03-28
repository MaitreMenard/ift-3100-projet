#pragma once
#include "ofxGui.h"

class Inspector
{
private:
    const string headerText = "Inspector";
    const ofColor headerColor = ofColor(24, 120, 24);
    ofxPanel panel;

public:
    Inspector();

    void draw();
};
