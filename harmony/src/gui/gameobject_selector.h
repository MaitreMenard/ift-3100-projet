#pragma once
#include "selector.h"
#include "gameobject.h"
#include "gameobject_visitor.h"
#include "gameobjects/curve.h"
#include "gameobjects/controlpoint.h"

class GameObjectSelector : public Selector<GameObject*>, public GameObjectVisitor
{
public:
    void setup();
    void update();
    void setSelectedControlPoint(ControlPoint* controlPoint);
    void deselectItem();
    void addControlPoint(Curve* curve, ControlPoint* controlPoint);

    template<class ListenerClass, typename ListenerMethod>
    void addControlPointListener(ListenerClass * listener, ListenerMethod method)
    {
        controlPointButtonPressedEvent.add(listener, method, OF_EVENT_ORDER_AFTER_APP);
    }

    void visit(GameObject* gameObject);
    void visit(Curve* curve);

    ~GameObjectSelector();

private:
    const std::string headerText = "Scene";
    const int xOffset = 2;
    const int yOffset = 2;
    const int controlPointButtonXOffset = 15;

    ControlPoint* selectedControlPoint;
    ofEvent<ControlPoint*> controlPointButtonPressedEvent;
    std::map<ControlPoint*, ofxButton*> controlPointsButtons;

    bool isAnyControlPointSelected();
};
