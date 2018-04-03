#include "gameobject_selector.h"

void GameObjectSelector::setup()
{
    panel.setup();
    panel.setName(headerText);
    panel.setHeaderBackgroundColor(headerColor);

    selectedGameObjectButtonIndex = -1;
}

void GameObjectSelector::update()
{
    /*
    Note: we have to fake events by polling instead of adding listeners to the buttons, because a button listener is only called
    when the button is released (see ofxButton::valueChanged in ofxButton.cpp, line 52).
    */
    for (size_t i = 0; i < buttons.size(); i++)
    {
        if (*buttons[i])
        {
            setSelectedGameObject(i);
            callListeners();
            break;
        }
    }
}

void GameObjectSelector::callListeners()
{
    for (std::function<void(size_t)> listener : listeners)
    {
        listener(selectedGameObjectButtonIndex);
    }
}

void GameObjectSelector::draw()
{
    panel.draw();
}

void GameObjectSelector::addListener(std::function<void(size_t)> method)
{
    listeners.push_back(method);
}

void GameObjectSelector::setSelectedGameObject(size_t gameObjectID)
{
    if (isAnyGameObjectSelected())
    {
        buttons.at(selectedGameObjectButtonIndex)->setBackgroundColor(baseButtonColor);
    }

    selectedGameObjectButtonIndex = gameObjectID;
    buttons.at(gameObjectID)->setBackgroundColor(highlightedButtonColor);
}

bool GameObjectSelector::isAnyGameObjectSelected()
{
    return selectedGameObjectButtonIndex != -1;
}

void GameObjectSelector::addGameObject(string gameObjectName)
{
    ofxButton *newButton = new ofxButton();
    buttons.push_back(newButton);
    panel.add(newButton->setup(ofParameter<string>(gameObjectName)));
}

GameObjectSelector::~GameObjectSelector()
{
    for (ofxButton* button : buttons)
    {
        delete button;
    }
    buttons.clear();
}
