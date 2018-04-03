#pragma once
#include "ofMain.h"
#include "ofxGui.h"

class TextureSelector
{
private:
    const std::string headerText = "Texture";
    const std::vector<string> textureTexts = { "None" , "Cloud" , "Marble" , "Noise" , "Turbulence" , "Zoom" };
    const ofColor headerColor = ofColor(24, 120, 24);
    const ofColor baseButtonColor = ofColor(24, 24, 24);
    const ofColor highlightedButtonColor = ofColor(24, 24, 240);

    std::vector<std::function<void(size_t)>> listeners;
    std::vector<ofxButton*> texture_buttons;
    ofxPanel panel;
    size_t selectedTextureID;

    void callListeners();

public:
    void setup();
    void draw();
    void update();

    void addListener(std::function<void(size_t)> method);
    void setSelectedTexture(size_t textureID);

    ~TextureSelector();
};
