#pragma once

#include"Globals.h"
#include "Entity.h"

#define STATE_THIRD_PERSON	0
#define STATE_TOP			1
#define STATE_FIRST_PERSON	2


class Camera
{
public:
	Camera(void);
	~Camera(void);

	void init(Entity *player);

	void setState(int state);
	void setRotation(int x, int y);

	void render();
	
	int state;
	float xRot, yRot;

private: 
	float xPos, yPos, zPos;

	Entity *player;
};

