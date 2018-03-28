#include "colorpicker.h"

ColorPicker::ColorPicker()
{
    eventsEnabled = true;
}

ColorPicker* ColorPicker::setup(ofColor initialColor)
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
    
    RGB_r.addListener(this, &ColorPicker::rgbFieldsListener);
    RGB_g.addListener(this, &ColorPicker::rgbFieldsListener);
    RGB_b.addListener(this, &ColorPicker::rgbFieldsListener);
    RGB_a.addListener(this, &ColorPicker::rgbFieldsListener);

    hsb_label.setBackgroundColor(labelColor);
    add(hsb_label.setup(ofParameter<string>(hsbText)));

    add(HSB_h.setup(hText, initialColor.getHue(), 0, 255));
    add(HSB_s.setup(sText, initialColor.getSaturation(), 0, 255));
    add(HSB_b.setup(bText, initialColor.getBrightness(), 0, 255));
    add(HSB_a.setup(aText, initialColor.a, 0, 255));
    
    HSB_h.addListener(this, &ColorPicker::hsbFieldsListener);
    HSB_s.addListener(this, &ColorPicker::hsbFieldsListener);
    HSB_b.addListener(this, &ColorPicker::hsbFieldsListener);
    HSB_a.addListener(this, &ColorPicker::hsbFieldsListener);

    return this;
}

void ColorPicker::addListener(std::function<void(ofColor)> method)
{
    listeners.push_back(method);
}

void ColorPicker::setColor(ofColor color)
{
    updateRGBFields(color);
    updateHSBFields(color);
}

void ColorPicker::rgbFieldsListener(int& value)
{
    if (eventsEnabled)
    {
        ofColor newColor = ofColor(RGB_r, RGB_g, RGB_b, RGB_a);

        updateHSBFields(newColor);

        callListenersWithNewColor(newColor);
    }
}

void ColorPicker::hsbFieldsListener(int& value)
{
    if (eventsEnabled)
    {
        ofColor newColor = ofColor(0);
        newColor.setHsb(HSB_h, HSB_s, HSB_b, HSB_a);

        updateRGBFields(newColor);

        callListenersWithNewColor(newColor);
    }
}

void ColorPicker::updateRGBFields(ofColor color)
{
    eventsEnabled = false;

    RGB_r = color.r;
    RGB_g = color.g;
    RGB_b = color.b;
    RGB_a = color.a;

    eventsEnabled = true;
}

void ColorPicker::updateHSBFields(ofColor color)
{
    eventsEnabled = false;

    HSB_h = color.getHue();
    HSB_s = color.getSaturation();
    HSB_b = color.getBrightness();
    HSB_a = color.a;

    eventsEnabled = true;
}

void ColorPicker::callListenersWithNewColor(ofColor color)
{
    for (std::function<void(ofColor)> listener : listeners)
    {
        listener(color);
    }
}
