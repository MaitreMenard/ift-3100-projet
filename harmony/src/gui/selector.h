#pragma once
#include "ofxGui.h"

class Selector
{
public:
    void setup(std::string headerText);
    void update();
    void draw();

    template<class ListenerClass, typename ListenerMethod>
    void addListener(ListenerClass * listener, ListenerMethod method)
    {
        buttonPressedEvent.add(listener, method, OF_EVENT_ORDER_AFTER_APP);
    }

    void addItem(std::string itemName);
    void setSelectedItem(size_t itemID);

    ~Selector();

protected:
    ofxPanel panel;

private:
    const ofColor headerColor = ofColor(24, 120, 24);
    const ofColor baseButtonColor = ofColor(24, 24, 24);
    const ofColor highlightedButtonColor = ofColor(24, 24, 240);

    size_t selectedButtonIndex;
    std::vector<ofxButton*> buttons;
    ofEvent<size_t> buttonPressedEvent;

    bool isAnyItemSelected();
};
