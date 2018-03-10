#include "rotation_slider.h"

void RotationSlider::addListener(std::function<void(ofVec3f)> method)
{
    listeners.push_back(method);

    getFloatSlider("x").addListener(this, &RotationSlider::slidersListener);
    getFloatSlider("y").addListener(this, &RotationSlider::slidersListener);
    getFloatSlider("z").addListener(this, &RotationSlider::slidersListener);
}

ofVec3f RotationSlider::operator=(const ofVec3f & v)
{
    value = v;
    return value;
}

void RotationSlider::slidersListener(float & value)
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
