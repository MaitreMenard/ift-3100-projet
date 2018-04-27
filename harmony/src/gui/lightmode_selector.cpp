#include "lightmode_selector.h"

void LightModeSelector::setup(enum LightMode defaultLightMode)
{
    Selector::setup(headerText, -1);

    for (int i = 0; i < 4; i++)
    {
        addItem(i, lightModeLabels[i]);
    }

    setSelectedItem((int)defaultLightMode);

    panel.setPosition(2, ofGetHeight() - panel.getHeight() - 2);
}
