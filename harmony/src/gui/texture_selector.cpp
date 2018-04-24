#include "texture_selector.h"

void TextureSelector::setup(TextureFactory& textureFactory)
{
    Selector::setup(headerText);

    for (Texture* texture : textureFactory.getAllTextures())
    {
        addItem(texture);
    }

    setSelectedItem(textureFactory.getEmptyTexture());

    panel.setPosition(2, ofGetHeight() - panel.getHeight() - 2);
}
