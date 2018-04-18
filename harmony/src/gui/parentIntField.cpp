#include "parentIntField.h"

ParentIntField* ParentIntField::setup(size_t currentParentID, size_t gameObjectCount)
{
    ofxIntField::setBackgroundColor(baseLabelColor);
    ofxIntField::setup(headerText, currentParentID, 0, gameObjectCount);
    value.addListener(this, &ParentIntField::internalListener);

    return this;
}

void ParentIntField::update(size_t currentParentID, size_t gameObjectCount)
{
    eventsEnabled = false;

    ofxIntField::setMax(gameObjectCount);
    value = currentParentID;

    eventsEnabled = true;
}

void ParentIntField::internalListener(int& value)
{
    if (eventsEnabled)
    {
        callListeners();
    }
}

void ParentIntField::callListeners()
{
    ofNotifyEvent(valueChangedEvent, (int)value);
}
