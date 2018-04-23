#include "selector.h"
//TODO: delete this file

//void Selector::setup(std::string headerText)
//{
//    panel.setup();
//    panel.setName(headerText);
//    panel.setHeaderBackgroundColor(headerColor);
//
//    //selectedButtonIndex = -1;
//}

//template<typename T>
//void Selector::update()
//{
//    /*
//    Note: we have to fake events by polling instead of adding listeners to the buttons, because a button listener is only called
//    when the button is released (see ofxButton::valueChanged in ofxButton.cpp, line 52).
//    */
//    /*for (size_t i = 0; i < buttons.size(); i++)
//    {
//        if (*buttons.at(i))
//        {
//            setSelectedItem(i);
//            ofNotifyEvent(buttonPressedEvent, selectedButtonIndex);
//            break;
//        }
//    }*/
//    for (const std::pair<T, ofxButton*> &p : itemButtons)
//    {
//        if (*p[1])
//        {
//            setSelectedItem(p[0]);
//            ofNotifyEvent(buttonPressedEvent, p[0]);
//            break;
//        }
//    }
//}

//template<typename T>
//void Selector::draw()
//{
//    panel.draw();
//}

//template<typename T>
//void Selector::addItem(T item)
//{
//    ofxButton *newButton = new ofxButton();
//    //buttons.push_back(newButton);
//    itemButtons.insert(std::pair<T, ofxButton>(item, newButton))
//    newButton->setBackgroundColor(baseButtonColor);
//    panel.add(newButton->setup(ofParameter<string>(itemName)));
//}
//
//template<typename T>
//void Selector::setSelectedItem(T item)
//{
//    if (isAnyItemSelected())
//    {
//        buttons.at(selectedButtonIndex)->setBackgroundColor(baseButtonColor);
//    }
//
//    selectedButtonIndex = itemID;
//    buttons.at(selectedButtonIndex)->setBackgroundColor(highlightedButtonColor);
//}

//Selector::~Selector()
//{
//    for (ofxButton* button : buttons)
//    {
//        delete button;
//    }
//    buttons.clear();
//}

//bool Selector::isAnyItemSelected()
//{
//    return selectedButtonIndex != -1;
//}
