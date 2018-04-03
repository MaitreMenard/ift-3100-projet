#pragma once
#include "ofxGui.h"
#include "gameobject.h"

class GameObjectSelector
{
private:
    const string headerText = "Scene";
    const ofColor headerColor = ofColor(24, 120, 24);
    const ofColor baseButtonColor = ofColor(24, 24, 24);
    const ofColor highlightedButtonColor = ofColor(24, 24, 240);

    size_t selectedGameObjectButtonIndex;
    ofxPanel panel;
    vector<ofxButton*> buttons;

public:
    void setup();
    void update();
    void draw();

    void setSelectedGameObject(size_t gameObjectID);
    bool isAnyGameObjectSelected();
    size_t getSelectedGameObjectID();
    void addGameObject(string gameObjectName);

    ~GameObjectSelector();
};
