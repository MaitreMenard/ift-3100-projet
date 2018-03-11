#include "rotation_slider.h"

RotationSlider::RotationSlider()
{
    eventsEnabled = true;
}

RotationSlider * RotationSlider::setup(const string labelText, ofVec3f value, ofVec3f minValues, ofVec3f maxValues)
{
    ofxVec3Slider::setup(labelText, value, minValues, maxValues);
    setHeaderBackgroundColor(labelColor);

    getFloatSlider("x").addListener(this, &RotationSlider::slidersListener);
    getFloatSlider("y").addListener(this, &RotationSlider::slidersListener);
    getFloatSlider("z").addListener(this, &RotationSlider::slidersListener);

    return this;
}

void RotationSlider::addListener(std::function<void(ofVec3f)> method)
{
    listeners.push_back(method);
}

void RotationSlider::enableEvents()
{
    eventsEnabled = true;
}

void RotationSlider::disableEvents()
{
    eventsEnabled = false;
}

ofVec3f RotationSlider::operator=(const ofVec3f & v)
{
    value = v;
    return value;
}

void RotationSlider::slidersListener(float & value)
{
    if (eventsEnabled)
    {
        callListenersWithSliderValues();
    }
}

void RotationSlider::callListenersWithSliderValues()
{
    ofVec3f values = ofVec3f(getFloatSlider("x"), getFloatSlider("y"), getFloatSlider("z"));

    for (std::function<void(ofVec3f)> listener : listeners)
    {
        listener(values);
    }
}

RotationSlider::~RotationSlider()
{
    listeners.clear();
}
