#include "lightmode_selector.h"

void LightModeSelector::setup(LightMode defaultLightMode)
{
    Selector::setup(headerText);

    for (int i = 0; i < 4; i++)
    {
        ofxButton *newButton = new ofxButton();
        itemButtons.insert(std::make_pair((LightMode)i, newButton));
        newButton->setBackgroundColor(baseButtonColor);
        panel.add(newButton->setup(ofParameter<string>(lightModeLabels[i])));
    }

    setSelectedItem(defaultLightMode);

    panel.setPosition(2, ofGetHeight() - panel.getHeight() - 2);
}
