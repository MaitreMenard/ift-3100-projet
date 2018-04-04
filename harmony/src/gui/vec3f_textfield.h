#pragma once
#include "ofxGui.h"
#include "ofxInputField.h"

class Vec3fTextField : public ofxGuiGroup
{
public:
    Vec3fTextField();
    Vec3fTextField* setup(const string labelText, ofVec3f values, ofVec3f minValues, ofVec3f maxValues);

    template<class ListenerClass, typename ListenerMethod>
    void addListener(ListenerClass * listener, ListenerMethod method)
    {
        valueChangedEvent.add(listener, method, OF_EVENT_ORDER_AFTER_APP);
    }

    ofVec3f operator=(const ofVec3f & v);

private:
    const ofColor labelColor = ofColor(48, 48, 72);

    ofxTextField x;
    ofxTextField y;
    ofxTextField z;

    ofVec3f minValues;
    ofVec3f maxValues;

    const string xText = "X: ";
    const string yText = "Y: ";
    const string zText = "Z: ";
    const string exceptionInvalidInput = " is not a valid input.";

    bool eventsEnabled;
    ofEvent<ofVec3f> valueChangedEvent;

    void textFieldsListener(string & value);
    void callListenersWithTextFieldValues();
    float convertTextFieldValueToFloat(string stringValue, float minValue, float maxValue);
};
