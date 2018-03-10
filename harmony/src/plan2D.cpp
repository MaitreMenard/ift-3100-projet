#include "plan2D.h"


plan2D::plan2D()
{
    texture.allocate(1, 1, GL_RGB);

    nbVertex = 4;
    model.setMode(OF_PRIMITIVE_TRIANGLES);
	
	model.addVertex(ofPoint(-0.5f, -0.5f, 0.01f));
	model.addTexCoord(texture.getCoordFromPercent(0, 0));
	model.addVertex(ofPoint(0.5f, -0.5f, 0.01f));
	model.addTexCoord(texture.getCoordFromPercent(0, 1));
	model.addVertex(ofPoint(-0.5f, 0.5f, 0.01f));
	model.addTexCoord(texture.getCoordFromPercent(1, 0));
	model.addVertex(ofPoint(0.5f, 0.5f, 0.01f));
	model.addTexCoord(texture.getCoordFromPercent(1, 1));


	model.addIndex(0);
	model.addIndex(1);
	model.addIndex(2);

	model.addIndex(3);
	model.addIndex(2);
	model.addIndex(1);
}

void plan2D::setColor(ofColor color) {
	model.clearColors();
	for (int i = 0; i < nbVertex; i++) {
		model.addColor(color);
	}
}