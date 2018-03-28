#include "inspector.h"

Inspector::Inspector()
{
    panel.setup();
    panel.setName(headerText);
    panel.setHeaderBackgroundColor(headerColor);
}

void Inspector::draw()
{
    panel.draw();
}
