#pragma once
#include "ofxGui.h"

template<typename T>
class Selector
{
public:
    void setup(std::string headerText, T noSelectionItem)
    {
        this->headerText = headerText;
        this->noSelectionItem = noSelectionItem;
        setupPanel();

        selectedItem = noSelectionItem;
    }

    virtual void update()
    {
        /*
        Note: we have to fake events by polling instead of adding listeners to the buttons, because a button listener is only called
        when the button is released (see ofxButton::valueChanged in ofxButton.cpp, line 52).
        */
        for (const auto& pair : itemButtons)
        {
            if (*pair.second)
            {
                setSelectedItem(pair.first);
                ofNotifyEvent(buttonPressedEvent, (T)pair.first);
                break;
            }
        }
    }

    void draw()
    {
        panel.draw();
    }

    template<class ListenerClass, typename ListenerMethod>
    void addListener(ListenerClass * listener, ListenerMethod method)
    {
        buttonPressedEvent.add(listener, method, OF_EVENT_ORDER_AFTER_APP);
    }

    void addItem(T item, std::string itemName)
    {
        ofxButton *newButton = new ofxButton();
        itemButtons.insert(std::make_pair(item, newButton));
        newButton->setBackgroundColor(baseButtonColor);
        panel.add(newButton->setup(ofParameter<string>(itemName)));
    }

    void setSelectedItem(T item)
    {
        deselectItem();

        selectedItem = item;
        itemButtons.at(selectedItem)->setBackgroundColor(highlightedButtonColor);
    }

    virtual void deselectItem()
    {
        if (isAnyItemSelected())
        {
            itemButtons.at(selectedItem)->setBackgroundColor(baseButtonColor);
            selectedItem = noSelectionItem;
        }
    }

    virtual ~Selector()
    {
        for (const auto& pair : itemButtons)
        {
            delete pair.second;
        }
        itemButtons.clear();
    }

protected:
    const ofColor baseButtonColor = ofColor(24, 24, 24);
    const ofColor highlightedButtonColor = ofColor(24, 24, 240);

    ofxPanel panel;
    std::map<T, ofxButton*> itemButtons;

    void setupPanel()
    {
        panel.setup();
        panel.setName(headerText);
        panel.setHeaderBackgroundColor(headerColor);
    }

private:
    const ofColor headerColor = ofColor(24, 120, 24);

    std::string headerText;
    T selectedItem;
    T noSelectionItem;
    ofEvent<T> buttonPressedEvent;

    bool isAnyItemSelected()
    {
        return selectedItem != noSelectionItem;
    }
};
