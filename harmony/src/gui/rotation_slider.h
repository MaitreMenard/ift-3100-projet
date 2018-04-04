#pragma once
#include "ofxGui.h"

class RotationSlider : public ofxVec3Slider
{
public:
    RotationSlider();
    RotationSlider* setup(const string labelText, ofVec3f value, ofVec3f minValues, ofVec3f maxValues);

    template<class ListenerClass, typename ListenerMethod>
    void addListener(ListenerClass * listener, ListenerMethod method)
    {
        valueChangedEvent.add(listener, method, OF_EVENT_ORDER_AFTER_APP);
    }

    ofVec3f operator=(const ofVec3f & v);

private:
    const ofColor labelColor = ofColor(48, 48, 72);

    bool eventsEnabled;
    ofEvent<ofVec3f> valueChangedEvent;

    void slidersListener(float & value);
    void callListenersWithSliderValues();
};
