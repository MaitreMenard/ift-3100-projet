#pragma once
#include "ofxGui.h"

class Selector
{
public:
    void setup(std::string headerText);
    void update();
    void draw();

    void addListener(std::function<void(size_t)> method);
    void setSelectedItem(size_t itemID);
    void addItem(std::string itemName);

    ~Selector();

protected:
    ofxPanel panel;

private:
    const ofColor headerColor = ofColor(24, 120, 24);
    const ofColor baseButtonColor = ofColor(24, 24, 24);
    const ofColor highlightedButtonColor = ofColor(24, 24, 240);

    size_t selectedButtonIndex;
    std::vector<ofxButton*> buttons;
    std::vector<std::function<void(size_t)>> listeners;

    void callListeners();
    bool isAnyItemSelected();
};
