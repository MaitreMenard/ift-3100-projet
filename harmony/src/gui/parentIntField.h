#pragma once
#include "ofxInputField.h"

class ParentIntField : public ofxIntField
{
public:
    ParentIntField* setup(size_t currentParentID, size_t gameObjectCount);
    void update(size_t currentParentID, size_t gameObjectCount);

    template<class ListenerClass, typename ListenerMethod>
    void addListener(ListenerClass * listener, ListenerMethod method)
    {
        valueChangedEvent.add(listener, method, OF_EVENT_ORDER_AFTER_APP);
    }

private:
    const string headerText = "Parent: ";
    const ofColor baseLabelColor = ofColor(48, 48, 72);

    bool eventsEnabled;
    ofEvent<int> valueChangedEvent;
    void internalListener(int& value);
    void callListeners();
};
