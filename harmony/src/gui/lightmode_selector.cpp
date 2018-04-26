#include "lightmode_selector.h"

void LightModeSelector::setup(enum LightMode defaultLightMode)
{
    Selector::setup(headerText, -1);

    for (int i = 0; i < 4; i++)
    {
        ofxButton *newButton = new ofxButton();
        itemButtons.insert(std::make_pair(i, newButton));
        newButton->setBackgroundColor(baseButtonColor);
        panel.add(newButton->setup(ofParameter<string>(lightModeLabels[i])));
    }

    setSelectedItem((int)defaultLightMode);

    panel.setPosition(2, ofGetHeight() - panel.getHeight() - 2);
}
