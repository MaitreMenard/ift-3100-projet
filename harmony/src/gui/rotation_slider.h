#pragma once
#include <vector>
#include <functional>
#include "ofxGui.h"

class RotationSlider : public ofxVec3Slider
{
public:
    RotationSlider();
    void addListener(std::function<void(ofVec3f)> method);
    void enableEvents();
    void disableEvents();
    ofVec3f operator=(const ofVec3f & v);
    ~RotationSlider();

private:
    std::vector<std::function<void(ofVec3f)>> listeners;
    bool eventsEnabled;

    void slidersListener(float & value);
    void callListenersWithSliderValues();
};
