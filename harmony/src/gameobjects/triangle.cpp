#include "triangle.h"


Triangle::Triangle(std::string name, Texture* texture) : GameObject(name, texture)
{
    nbVertex = 3;
    model.setMode(OF_PRIMITIVE_TRIANGLES);
    model.addVertex(ofVec3f(0.f, 0.5f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(0, 0));
    model.addVertex(ofVec3f(-0.433f, -0.25f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(0.5f, 1));
    model.addVertex(ofVec3f(0.433f, -0.25f, 0.f));
    model.addTexCoord(texture->getCoordFromPercent(1, 0));

    model.addIndex(0);
    model.addIndex(1);
    model.addIndex(2);

    gameObjectIs2D = true;
    _hasMaterial = true;

	vector< ofMeshFace > faces = model.getUniqueFaces();

	for (int i = 0; i < faces.size(); i++) {
		faces[i].setVertex(0, faces[i].getVertex(0));
		faces[i].setNormal(0, faces[i].getFaceNormal());
		faces[i].setNormal(1, faces[i].getFaceNormal());
		faces[i].setNormal(2, faces[i].getFaceNormal());
	}
	model.setFromTriangles(faces);
	model.smoothNormals(60);

    boundingBox.set(1, 1, 0.01f);
}
