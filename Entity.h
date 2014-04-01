#pragma once
#include "Globals.h"

class Entity
{
public:
	Entity(void);
	~Entity(void);

	void init();
	void render();

	void moveX(float velocity);
	void moveZ(float velocity);

private:
	float x ,y ,z;
	GLUquadricObj *mesh;
};

