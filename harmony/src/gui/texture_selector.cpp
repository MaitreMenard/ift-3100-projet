#include "texture_selector.h"

void TextureSelector::setup(TextureFactory& textureFactory)
{
    Selector::setup(headerText, nullptr);

    for (Texture* texture : textureFactory.getAllTextures())
    {
        addItem(texture, texture->getName());
    }

    setSelectedItem(textureFactory.getEmptyTexture());

    onWindowResized();
}

void TextureSelector::onWindowResized()
{
    panel.setPosition(2, ofGetHeight() - panel.getHeight() - 2);
}
