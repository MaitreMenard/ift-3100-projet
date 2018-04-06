#include "texture_selector.h"

void TextureSelector::setup()
{
    Selector::setup(headerText);

    for (std::string textureName : textureTexts)
    {
        addItem(textureName);
    }

    setSelectedItem(0);

    panel.setPosition(2, ofGetHeight() - panel.getHeight() - 2);
}
