#include "vec3f_textfield.h"

Vec3fTextField::Vec3fTextField()
{
    eventsEnabled = true;
}

Vec3fTextField* Vec3fTextField::setup(string labelText, ofVec3f values, ofVec3f minValues, ofVec3f maxValues)
{
    ofxGuiGroup::setup(labelText, "", 0, 0);
    setName(labelText);
    setHeaderBackgroundColor(labelColor);

    add(x.setup(xText, to_string(values.x)));
    add(y.setup(yText, to_string(values.y)));
    add(z.setup(zText, to_string(values.z)));

    this->minValues = minValues;
    this->maxValues = maxValues;

    x.addListener(this, &Vec3fTextField::textFieldsListener);
    y.addListener(this, &Vec3fTextField::textFieldsListener);
    z.addListener(this, &Vec3fTextField::textFieldsListener);

    return this;
}

ofVec3f Vec3fTextField::operator=(const ofVec3f & v)
{
    eventsEnabled = false;
    x = to_string(v.x);
    y = to_string(v.y);
    z = to_string(v.z);
    eventsEnabled = true;

    return v;
}

void Vec3fTextField::textFieldsListener(string & value)
{
    if (eventsEnabled)
    {
        callListenersWithTextFieldValues();
    }
}

void Vec3fTextField::callListenersWithTextFieldValues()
{
    float xValue = convertTextFieldValueToFloat(x, minValues.x, maxValues.x);
    float yValue = convertTextFieldValueToFloat(y, minValues.y, maxValues.y);
    float zValue = convertTextFieldValueToFloat(z, minValues.z, maxValues.z);

    ofVec3f newVec = ofVec3f(xValue, yValue, zValue);

    ofNotifyEvent(valueChangedEvent, newVec);
}

float Vec3fTextField::convertTextFieldValueToFloat(string stringValue, float minValue, float maxValue)
{
    float fValue;
    try
    {
        fValue = stof(stringValue);
        fValue = CLAMP(fValue, minValue, maxValue);
    }
    catch (...)
    {
        ofLog() << stringValue << exceptionInvalidInput;
        return 0;
    }
    return fValue;
}
