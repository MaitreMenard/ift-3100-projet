#include "lightmode_selector.h"

void LightModeSelector::setup(enum LightMode defaultLightMode)
{
    Selector::setup(headerText, -1);

    for (int i = 0; i < 4; i++)
    {
        addItem(i, lightModeLabels[i]);
    }

    setSelectedItem((int)defaultLightMode);

    onWindowResized();
}

void LightModeSelector::visit(GameObject * gameObject)
{}

void LightModeSelector::visit(Light * light)
{
    setSelectedItem((int)light->getLightMode());
}

void LightModeSelector::onWindowResized()
{
    panel.setPosition(2, ofGetHeight() - panel.getHeight() - 2);
}
