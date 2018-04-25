#include "gameobject_selector.h"

void GameObjectSelector::setup()
{
    Selector::setup(headerText);

    panel.setPosition(xOffset, yOffset);
}

void GameObjectSelector::visit(GameObject * gameObject)
{
    addItem(gameObject);
}

void GameObjectSelector::visit(Curve * curve)
{
    addItem(curve);
    for (ControlPoint* controlPoint : curve->getControlPoints())
    {
        addControlPoint(curve, controlPoint);
    }
}

void GameObjectSelector::addControlPoint(Curve * curve, ControlPoint* controlPoint)
{
    ofxButton *newButton = new ofxButton();
    itemButtons.insert(std::make_pair(controlPoint, newButton));
    newButton->setBackgroundColor(baseButtonColor);
    panel.add(newButton->setup(ofParameter<string>(controlPoint->getName())));
    newButton->setPosition(newButton->getPosition() + ofVec3f(10, 0));
}
