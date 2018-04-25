#include "gameobject_selector.h"

void GameObjectSelector::setup()
{
    Selector::setup(headerText);

    panel.setPosition(xOffset, yOffset);

    selectedControlPoint = nullptr;
}

void GameObjectSelector::update()
{
    Selector<GameObject*>::update();
    
    for (const auto& pair : controlPointsButtons)
    {
        if (*pair.second)
        {
            setSelectedControlPoint(pair.first);
            ofNotifyEvent(controlPointButtonPressedEvent, (ControlPoint*)pair.first);
            break;
        }
    }
}

void GameObjectSelector::setSelectedControlPoint(ControlPoint* controlPoint)
{
    deselectItem();

    selectedControlPoint = controlPoint;
    controlPointsButtons.at(selectedControlPoint)->setBackgroundColor(highlightedButtonColor);
}

void GameObjectSelector::deselectItem()
{
    Selector<GameObject*>::deselectItem();

    if (isAnyControlPointSelected())
    {
        controlPointsButtons.at(selectedControlPoint)->setBackgroundColor(baseButtonColor);
        selectedControlPoint = nullptr;
    }
}

bool GameObjectSelector::isAnyControlPointSelected()
{
    return selectedControlPoint != nullptr;
}

void GameObjectSelector::addControlPoint(Curve * curve, ControlPoint* controlPoint)
{
    ofxButton *newButton = new ofxButton();
    controlPointsButtons.insert(std::make_pair(controlPoint, newButton));
    panel.add(newButton->setup(ofParameter<string>(controlPoint->getName())));

    newButton->setBackgroundColor(baseButtonColor);
    newButton->setPosition(newButton->getPosition() + ofVec3f(controlPointButtonXOffset, 0));
    newButton->setSize(newButton->getWidth() - controlPointButtonXOffset, newButton->getHeight());
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

void GameObjectSelector::visit(ControlPoint * controlPoint)
{
    visit((GameObject*)controlPoint);
}

void GameObjectSelector::visit(Model3D * model3D)
{
    visit((GameObject*)model3D);
}

GameObjectSelector::~GameObjectSelector()
{
    for (const auto& pair : controlPointsButtons)
    {
        delete pair.second;
    }
    controlPointsButtons.clear();
}
