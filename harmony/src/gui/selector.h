#pragma once
#include "ofxGui.h"

template<typename T>
class Selector
{
public:
    void setup(std::string headerText)
    {
        panel.setup();
        panel.setName(headerText);
        panel.setHeaderBackgroundColor(headerColor);

        selectedItem = nullptr;
    }

    void update()
    {
        /*
        Note: we have to fake events by polling instead of adding listeners to the buttons, because a button listener is only called
        when the button is released (see ofxButton::valueChanged in ofxButton.cpp, line 52).
        */
        for (std::pair<T, ofxButton*> &p : itemButtons)
        {
            if (*p[1])
            {
                setSelectedItem(p[0]);
                ofNotifyEvent(buttonPressedEvent, p[0]);
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

    void addItem(T item)
    {
        ofxButton *newButton = new ofxButton();
        itemButtons.insert(std::pair<T, ofxButton>(item, newButton));
        newButton->setBackgroundColor(baseButtonColor);
        panel.add(newButton->setup(ofParameter<string>(item->getName())));  //FIXME: getName might not work here -> make abstract method
    }

    void setSelectedItem(T item)
    {
        if (isAnyItemSelected())
        {
            itemButtons.at(selectedItem)->setBackgroundColor(baseButtonColor);
        }

        selectedItem = item;
        itemButtons.at(selectedItem)->setBackgroundColor(highlightedButtonColor);
    }

    ~Selector()
    {
        for (const std::pair<T, ofxButton*> &p : itemButtons)
        {
            delete p[1];
        }
        itemButtons.clear();
    }

protected:
    ofxPanel panel;

private:
    const ofColor headerColor = ofColor(24, 120, 24);
    const ofColor baseButtonColor = ofColor(24, 24, 24);
    const ofColor highlightedButtonColor = ofColor(24, 24, 240);

    T selectedItem;
    std::map<T, ofxButton*> itemButtons;
    ofEvent<T> buttonPressedEvent;

    bool isAnyItemSelected()
    {
        selectedItem != nullptr;
    }
};
