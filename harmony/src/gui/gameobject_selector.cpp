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
    //TODO: use events instead of polling
    for (size_t i = 0; i < buttons.size(); i++)
    {
        if (*buttons[i])
        {
            setSelectedGameObject(i);
            break;
        }
    }
}

void GameObjectSelector::draw()
{
    panel.draw();
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

size_t GameObjectSelector::getSelectedGameObjectID()
{
    return selectedGameObjectButtonIndex;
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
