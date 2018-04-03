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
    //TODO: use events instead of polling
    for (size_t i = 0; i < texture_buttons.size(); i++)
    {
        if (*texture_buttons.at(i))
        {
            setSelectedTexture(i);
            break;
        }
    }
}

size_t TextureSelector::getSelectedTextureID()
{
    return selectedTextureID;
}

void TextureSelector::setSelectedTexture(size_t textureID)
{
    texture_buttons.at(selectedTextureID)->setBackgroundColor(baseButtonColor);
    selectedTextureID = textureID;
    texture_buttons.at(selectedTextureID)->setBackgroundColor(highlightedButtonColor);
}

TextureSelector::~TextureSelector()
{
    for (ofxButton* button2 : texture_buttons)
    {
        delete button2;
    }
    texture_buttons.clear();
}
