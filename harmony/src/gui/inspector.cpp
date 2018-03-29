#include "inspector.h"

Inspector::Inspector()
{
    panel.setup();
    panel.setName(headerText);
    panel.setHeaderBackgroundColor(headerColor);
}

void Inspector::update(GameObject* gameObject)
{
    positionFields = gameObject->getPosition();
    rotation = gameObject->getEulerAngles();
    scaleFields = gameObject->getScale();

    colorPicker.setColor(gameObject->getColor());
}

void Inspector::draw()
{
    panel.draw();
}
