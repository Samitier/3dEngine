#pragma once
#include "Globals.h"
#include "Data.h"

class Entity
{
public:
	Entity(void);
	~Entity(void);

	void init();
	void render(Data *data);

	void moveX(float velocity);
	void moveZ(float velocity);

	float x ,y ,z;
	float rot;

private:

};

