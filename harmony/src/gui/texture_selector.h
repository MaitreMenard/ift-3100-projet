#pragma once
#include "ofMain.h"
#include "ofxGui.h"

class TextureSelector
{
private:
    const string headerText = "Texture";
    const vector<string> textureTexts = { "None" , "Cloud" , "Marble" , "Noise" , "Turbulence" , "Zoom" };
    const ofColor headerColor = ofColor(24, 120, 24);
    const ofColor baseButtonColor = ofColor(24, 24, 24);
    const ofColor highlightedButtonColor = ofColor(24, 24, 240);

    vector<ofxButton*> texture_buttons;
    ofxPanel panel;
    size_t selectedTextureID;

public:
    void setup();
    void draw();
    void update();

    size_t getSelectedTextureID();
    void setSelectedTexture(size_t textureID);

    ~TextureSelector();
};
