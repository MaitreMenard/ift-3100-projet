#include "colorpicker.h"

ColorPicker::ColorPicker()
{
    eventsEnabled = true;
}

void ColorPicker::setup(ofColor initialColor)
{
    ofxGuiGroup::setup(headerText, "", 0, 0);
    setName(headerText);
    setHeaderBackgroundColor(labelColor);

    rgb_label.setBackgroundColor(labelColor);
    add(rgb_label.setup(ofParameter<string>(rgbText)));
    add(RGB_r.setup(rText, initialColor.r, 0, 255));
    add(RGB_g.setup(gText, initialColor.g, 0, 255));
    add(RGB_b.setup(bText, initialColor.b, 0, 255));
    add(RGB_a.setup(aText, initialColor.a, 0, 255));
    addRGBListeners();

    hsb_label.setBackgroundColor(labelColor);
    add(hsb_label.setup(ofParameter<string>(hsbText)));
    add(HSB_h.setup(hText, initialColor.getHue(), 0, 255));
    add(HSB_s.setup(sText, initialColor.getSaturation(), 0, 255));
    add(HSB_b.setup(bText, initialColor.getBrightness(), 0, 255));
    add(HSB_a.setup(aText, initialColor.a, 0, 255));
    addHSBListeners();
}

void ColorPicker::addListener(std::function<void(ofColor)> method)
{
    listeners.push_back(method);
}

void ColorPicker::setColor(ofColor color)
{
    disableEvents();

    RGB_r = color.r;
    RGB_g = color.g;
    RGB_b = color.b;
    RGB_a = color.a;

    HSB_h = color.getHue();
    HSB_s = color.getSaturation();
    HSB_b = color.getBrightness();
    HSB_a = color.a;

    enableEvents();
}

void ColorPicker::enableEvents()
{
    eventsEnabled = true;
}

void ColorPicker::disableEvents()
{
    eventsEnabled = false;
}

void ColorPicker::intFieldsListener(int & value)
{
    if (eventsEnabled)
    {

    }
}

void ColorPicker::callListenersWithIntFieldValues()
{
    for (std::function<void(ofColor)> listener : listeners)
    {
        listener(ofColor(RGB_r, RGB_g, RGB_b, RGB_a));
    }
}
