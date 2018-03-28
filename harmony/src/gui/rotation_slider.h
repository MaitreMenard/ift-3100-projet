#pragma once
#include <vector>
#include <functional>
#include "ofxGui.h"

class RotationSlider : public ofxVec3Slider
{
public:
    RotationSlider();
    RotationSlider* setup(const string labelText, ofVec3f value, ofVec3f minValues, ofVec3f maxValues);
    void addListener(std::function<void(ofVec3f)> method);
    ofVec3f operator=(const ofVec3f & v);
    ~RotationSlider();

private:
    const ofColor labelColor = ofColor(48, 48, 72);

    std::vector<std::function<void(ofVec3f)>> listeners;
    bool eventsEnabled;

    void slidersListener(float & value);
    void callListenersWithSliderValues();
};
