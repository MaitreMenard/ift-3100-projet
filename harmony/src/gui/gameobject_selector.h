#pragma once
#include "selector.h"
#include "gameobject.h"
#include "gameobject_visitor.h"
#include "gameobjects/curve.h"
#include "gameobjects/bezier_curve.h"
#include "gameobjects/controlpoint.h"

class GameObjectSelector : public Selector<GameObject*>, public GameObjectVisitor
{
public:
    void setup();
    void update();
    void setSelectedControlPoint(ControlPoint* controlPoint);
    void deselectItem();
    // This method is used when adding a new ControlPoint to an already existing curve with the button in the UI
    void addControlPoint(Curve* curve, ControlPoint* controlPoint);

    template<class ListenerClass, typename ListenerMethod>
    void addControlPointListener(ListenerClass * listener, ListenerMethod method)
    {
        controlPointButtonPressedEvent.add(listener, method, OF_EVENT_ORDER_AFTER_APP);
    }

    // These methods are used when adding new GameObjects via the keyboard shortcuts
    void visit(GameObject* gameObject);
    void visit(Curve* curve);
    void visit(BezierCurve* bezierCurve);
    void visit(ControlPoint* controlPoint);
    void visit(Model3D* model3D);

    ~GameObjectSelector();

private:
    const std::string headerText = "Scene";
    const int xOffset = 2;
    const int yOffset = 2;
    const int controlPointButtonXOffset = 15;

    ControlPoint* selectedControlPoint;
    ofEvent<ControlPoint*> controlPointButtonPressedEvent;
    std::map<ControlPoint*, ofxButton*> controlPointsButtons;
    std::list<GameObject*> gameObjectList;

    ofxButton* createControlPointButton(ControlPoint* controlPoint);
    void addControlPointButtonToPanel(ofxButton* button);
    bool isAnyControlPointSelected();
    void addAllGameObjectButtonsToPanel();
    void addCurveControlPointsButtonsToPanel(Curve* curve);
};
