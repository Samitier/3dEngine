#pragma once
#pragma comment(lib,"MD2Model")

#include "Scene.h"
#include "Data.h"
#include "Camera.h"
#include "Entity.h"
#include "MD2Model.h"

class Game
{
public:
	Game(void);
	virtual ~Game(void);

	bool init();
	bool Loop();
	void finalize();

	//Input
	void readKeyboard(unsigned char key, int x, int y, bool press);
	void readMouse(int button, int state, int x, int y);
	void readMousePosition(int x, int y);

	//Process
	bool process();
	//Output
	void render();

private:
	unsigned char keys[256];
	Scene scene;
	Data data;
	Camera camera;
	Entity entity;
	MD2Model models[6];
};
