#pragma once

#include "Scene.h"
#include "Data.h"
#include "Camera.h"
#include "Entity.h"

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

class Game
{
public:
	Game(void);
	virtual ~Game(void);

	bool init();
	bool Loop();
	void Finalize();

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process();
	//Output
	void render();

private:
	unsigned char keys[256];
	Scene scene;
	Data data;
	Camera camera;
	Entity entity;
};
