#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxInputField.h"

class ColorPicker : public ofxGuiGroup
{
public:
    ColorPicker();
    ColorPicker* setup(ofColor initialColor);

    template<class ListenerClass, typename ListenerMethod>
    void addListener(ListenerClass * listener, ListenerMethod method)
    {
        colorChangedEvent.add(listener, method, OF_EVENT_ORDER_AFTER_APP);
    }

    void setColor(ofColor color);

private:
    const string headerText = "Color:";
    const string rgbText = "RGB";
    const string hsbText = "HSB";
    const string aText = "A: ";
    const string bText = "B: ";
    const string gText = "G: ";
    const string hText = "H: ";
    const string rText = "R: ";
    const string sText = "S: ";
    const ofColor labelColor = ofColor(48, 48, 72);

    ofxLabel rgb_label;
    ofxIntField RGB_r;
    ofxIntField RGB_g;
    ofxIntField RGB_b;
    ofxIntField RGB_a;

    ofxLabel hsb_label;
    ofxIntField HSB_h;
    ofxIntField HSB_s;
    ofxIntField HSB_b;
    ofxIntField HSB_a;

    bool eventsEnabled;
    ofEvent<ofColor> colorChangedEvent;

    void rgbFieldsListener(int& value);
    void hsbFieldsListener(int& value);
    void updateRGBFields(ofColor color);
    void updateHSBFields(ofColor color);
    void callListenersWithNewColor(ofColor color);
};
