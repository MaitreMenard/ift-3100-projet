#pragma once
#include <vector>
#include <functional>
#include "ofxGui.h"

class RotationSlider : public ofxVec3Slider
{
public:
    void addListener(std::function<void(ofVec3f)> method);
    void removeListener(std::function<void(ofVec3f)> method);
    ofVec3f operator=(const ofVec3f & v);
    ~RotationSlider();

private:
    std::vector<std::function<void(ofVec3f)>> listeners;

    void slidersListener(float & value);
};
