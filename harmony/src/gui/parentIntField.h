#pragma once
#include "ofxInputField.h"

class ParentIntField : public ofxIntField
{
public:
    ParentIntField* setup(size_t currentParentID, size_t gameObjectCount);
    void update(size_t currentParentID, size_t gameObjectCount);

private:
    const string headerText = "Parent: ";
    const ofColor baseLabelColor = ofColor(48, 48, 72);
};
