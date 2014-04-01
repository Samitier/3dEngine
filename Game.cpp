#include "Game.h"
#include "Globals.h"


Game::Game(void) {}
Game::~Game(void){}

bool Game::init()
{
	bool res=true;
	camera.init();

	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	
	glEnable(GL_DEPTH_TEST);
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	//Scene initialization
	res = data.LoadImage(IMG_WALL,"wall.png",GL_RGBA);
	if(!res) return false;
	res = data.LoadImage(IMG_FLOOR,"floor.png",GL_RGBA);
	if(!res) return false;
	res = data.LoadImage(IMG_ROOF,"roof.png",GL_RGBA);
	if(!res) return false;

	return res;
}

bool Game::Loop()
{
	bool res=true;

	res = Process();
	if(res) render();

	return res;
}

void Game::Finalize()
{
}

//Input
void Game::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;
}

void Game::ReadMouse(int button, int state, int x, int y)
{
}

//Process
bool Game::Process()
{
	bool res=true;
	
	//Process Input
	if(keys[27])	res=false;	
	
	else if(keys['2']){
		camera.setState(STATE_2);
	}
	else if(keys['3']){
		camera.setState(STATE_3);
	}
	else if(keys['4']){
        camera.setState(STATE_4);
	}
	else if(keys['5']){
		camera.setState(STATE_5);
	}

	return res;
}

//Output
void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	camera.render();

	scene.render(&data);

	glutSwapBuffers();
}
