#include "texture_selector.h"

void TextureSelector::setup()
{
    panel.setup();
    panel.setName(headerText);
    panel.setHeaderBackgroundColor(headerColor);

    selectedTextureID = 0;

    for (int i = 0; i < textureTexts.size(); i++)
    {
        ofxButton* button = new ofxButton();
        button->setBackgroundColor(baseButtonColor);
        panel.add(button->setup(ofParameter<string>(textureTexts.at(i))));
        texture_buttons.push_back(button);
    }

    texture_buttons.at(selectedTextureID)->setBackgroundColor(highlightedButtonColor);

    panel.setPosition(2, ofGetHeight() - panel.getHeight() - 2);
}

void TextureSelector::draw()
{
    panel.draw();
}

void TextureSelector::update()
{
    /*
    Note: we have to fake events by polling instead of adding listeners to the buttons, because a button listener is only called
    when the button is released (see ofxButton::valueChanged in ofxButton.cpp, line 52). 
    */
    for (size_t i = 0; i < texture_buttons.size(); i++)
    {
        if (*texture_buttons.at(i))
        {
            setSelectedTexture(i);
            callListeners();
            break;
        }
    }
}

void TextureSelector::callListeners()
{
    for (std::function<void(size_t)> listener : listeners)
    {
        listener(selectedTextureID);
    }
}

void TextureSelector::addListener(std::function<void(size_t)> method)
{
    listeners.push_back(method);
}

void TextureSelector::setSelectedTexture(size_t textureID)
{
    texture_buttons.at(selectedTextureID)->setBackgroundColor(baseButtonColor);
    selectedTextureID = textureID;
    texture_buttons.at(selectedTextureID)->setBackgroundColor(highlightedButtonColor);
}

TextureSelector::~TextureSelector()
{
    for (ofxButton* button : texture_buttons)
    {
        delete button;
    }
    texture_buttons.clear();
}
