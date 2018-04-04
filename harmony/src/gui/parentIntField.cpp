#include "parentIntField.h"

ParentIntField* ParentIntField::setup(size_t currentParentID, size_t gameObjectCount)
{
    ofxIntField::setBackgroundColor(baseLabelColor);
    ofxIntField::setup(headerText, currentParentID, 0, gameObjectCount);

    return this;
}

void ParentIntField::update(size_t currentParentID, size_t gameObjectCount)
{
    value.disableEvents();

    ofxIntField::setMax(gameObjectCount);
    value = currentParentID;

    value.enableEvents();
}
