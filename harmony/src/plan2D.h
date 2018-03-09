#pragma once
#include "gameobject.h"
#include "texelFactory.h"

class plan2D :
	public GameObject
{
private:
	ofTexture texture;
public:
	plan2D();
	void draw();
	void setTexture(ofPixels * pixels);
};

