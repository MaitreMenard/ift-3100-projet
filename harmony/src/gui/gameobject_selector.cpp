#include "gameobject_selector.h"

void GameObjectSelector::setup()
{
    Selector::setup(headerText, nullptr);
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
    createControlPointButton(controlPoint);

    panel.clear();
    setupPanel();
    panel.setPosition(xOffset, yOffset);

    addAllGameObjectButtonsToPanel();
}

ofxButton* GameObjectSelector::createControlPointButton(ControlPoint* controlPoint)
{
    ofxButton *newButton = new ofxButton();
    newButton->setup(ofParameter<string>(controlPoint->getName()));
    newButton->setBackgroundColor(baseButtonColor);
    newButton->setSize(newButton->getWidth() - controlPointButtonXOffset, newButton->getHeight());
    controlPointsButtons.insert(std::make_pair(controlPoint, newButton));
    return newButton;
}

void GameObjectSelector::addAllGameObjectButtonsToPanel()
{
    for (GameObject* gameObject : gameObjectList)
    {
        panel.add(itemButtons.at(gameObject));
        Curve* curve = dynamic_cast <Curve*>(gameObject);
        if (curve != nullptr)
        {
            addCurveControlPointsButtonsToPanel(curve);
        }
    }
}

void GameObjectSelector::addCurveControlPointsButtonsToPanel(Curve * curve)
{
    for (ControlPoint* controlPoint : curve->getControlPoints())
    {
        ofxButton* button = controlPointsButtons.at(controlPoint);
        addControlPointButtonToPanel(button);
    }
}

void GameObjectSelector::addControlPointButtonToPanel(ofxButton * button)
{
    panel.add(button);
    button->setPosition(button->getPosition() + ofVec3f(controlPointButtonXOffset, 0));
}

void GameObjectSelector::visit(GameObject * gameObject)
{
    addItem(gameObject, gameObject->getName());
    gameObjectList.push_back(gameObject);
}

void GameObjectSelector::visit(Curve * curve)
{
    visit((GameObject*)curve);
    for (ControlPoint* controlPoint : curve->getControlPoints())
    {
        ofxButton* newButton = createControlPointButton(controlPoint);
        addControlPointButtonToPanel(newButton);
    }
}

void GameObjectSelector::visit(BezierCurve * bezierCurve)
{
    visit((Curve*)bezierCurve);
}

void GameObjectSelector::visit(ControlPoint * controlPoint)
{
    visit((GameObject*)controlPoint);
}

void GameObjectSelector::visit(Model3D * model3D)
{
    visit((GameObject*)model3D);
}

void GameObjectSelector::visit(Light * light)
{
    visit((GameObject*)light);
}

GameObjectSelector::~GameObjectSelector()
{
    for (const auto& pair : controlPointsButtons)
    {
        delete pair.second;
    }
    controlPointsButtons.clear();
    gameObjectList.clear();
}
