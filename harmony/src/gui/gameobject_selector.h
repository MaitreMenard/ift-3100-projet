#pragma once
#include "ofxGui.h"
#include "gameobject.h"

class GameObjectSelector
{
private:
    const std::string headerText = "Scene";
    const ofColor headerColor = ofColor(24, 120, 24);
    const ofColor baseButtonColor = ofColor(24, 24, 24);
    const ofColor highlightedButtonColor = ofColor(24, 24, 240);

    size_t selectedGameObjectButtonIndex;
    ofxPanel panel;
    std::vector<ofxButton*> buttons;
    std::vector<std::function<void(size_t)>> listeners;

    void callListeners();
    bool isAnyGameObjectSelected();

public:
    void setup();
    void update();
    void draw();

    void addListener(std::function<void(size_t)> method);
    void setSelectedGameObject(size_t gameObjectID);
    void addGameObject(std::string gameObjectName);

    ~GameObjectSelector();
};
