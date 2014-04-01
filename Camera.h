#pragma once

#include"Globals.h"

#define STATE_DEFAULT		0
#define STATE_2				1
#define STATE_3				2
#define STATE_4				3
#define STATE_5				4

class Camera
{
public:
	Camera(void);
	~Camera(void);

	void init();

	void setState(int state);

	void render();

private: 
	int state;
	//int x, y, z;
};

