#include "colorpicker.h"

ColorPicker::ColorPicker()
{
    eventsEnabled = true;
}

ColorPicker* ColorPicker::setup(std::string headerText,  ofColor initialColor)
{
    ofxGuiGroup::setup(headerText, "", 0, 0);
    setName(headerText);
    setHeaderBackgroundColor(labelColor);

    rgb_label.setBackgroundColor(labelColor);
    add(rgb_label.setup(rgbText, ""));

    add(RGB_r.setup(RText, initialColor.r, 0, 255));
    add(RGB_g.setup(GText, initialColor.g, 0, 255));
    add(RGB_b.setup(BText, initialColor.b, 0, 255));
    add(RGB_a.setup(AText, initialColor.a, 0, 255));
    
    RGB_r.addListener(this, &ColorPicker::rgbFieldsListener);
    RGB_g.addListener(this, &ColorPicker::rgbFieldsListener);
    RGB_b.addListener(this, &ColorPicker::rgbFieldsListener);
    RGB_a.addListener(this, &ColorPicker::rgbFieldsListener);

    hsb_label.setBackgroundColor(labelColor);
    add(hsb_label.setup(hsbText, ""));

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
    ofNotifyEvent(colorChangedEvent, color);
}
