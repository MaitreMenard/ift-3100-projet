#include "selector.h"

void Selector::setup(std::string headerText)
{
    panel.setup();
    panel.setName(headerText);
    panel.setHeaderBackgroundColor(headerColor);

    selectedButtonIndex = -1;
}

void Selector::update()
{
    /*
    Note: we have to fake events by polling instead of adding listeners to the buttons, because a button listener is only called
    when the button is released (see ofxButton::valueChanged in ofxButton.cpp, line 52).
    */
    for (size_t i = 0; i < buttons.size(); i++)
    {
        if (*buttons.at(i))
        {
            setSelectedItem(i);
            ofNotifyEvent(buttonPressedEvent, selectedButtonIndex);
            break;
        }
    }
}

void Selector::draw()
{
    panel.draw();
}

void Selector::addItem(std::string itemName)
{
    ofxButton *newButton = new ofxButton();
    buttons.push_back(newButton);
    newButton->setBackgroundColor(baseButtonColor);
    panel.add(newButton->setup(ofParameter<string>(itemName)));
}

void Selector::setSelectedItem(size_t itemID)
{
    if (isAnyItemSelected())
    {
        buttons.at(selectedButtonIndex)->setBackgroundColor(baseButtonColor);
    }

    selectedButtonIndex = itemID;
    buttons.at(selectedButtonIndex)->setBackgroundColor(highlightedButtonColor);
}

Selector::~Selector()
{
    for (ofxButton* button : buttons)
    {
        delete button;
    }
    buttons.clear();
}

bool Selector::isAnyItemSelected()
{
    return selectedButtonIndex != -1;
}
