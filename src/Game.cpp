#include "Game.h"
#include "Globals.h"


Game::Game(void) {}
Game::~Game(void){}

bool Game::init()
{
	bool res=true;

	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glEnable(GL_DEPTH_TEST);
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	//Scene initialization
	entity.init();
	camera.init(&entity);
	data.init();
	if(!res) return false;

	//Models initialization
	char *s[] = {"bauul","rat","knight","boost","hammer","teleporter"};
	for(int i=0;i<6;i++)
	{
		res = models[i].Load(s[i]);
		if(!res) return false;
	}

	models[0].SetAnimation(ANIM_STAND);
	models[1].SetAnimation(ANIM_RUN);
	models[2].SetAnimation(ANIM_JUMP);

	return res;
}

bool Game::Loop()
{
	bool res=true;

	res = process();
	if(res) render();

	return res;
}

void Game::finalize()
{
}

//Input
void Game::readKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;
}

void Game::readMouse(int button, int state, int x, int y)
{
}

void Game::readMousePosition(int x, int y){
	camera.setRotation(x,y);
}


//Process
bool Game::process()
{
	bool res=true;
	
	//Process Input
	if(keys[27])	res=false;	
	if(keys['1']){
		camera.setState(STATE_THIRD_PERSON);
	}
	else if(keys['2']){
		camera.setState(STATE_TOP);
	}
	else if(keys['3']){
		camera.setState(STATE_FIRST_PERSON);
	}
	if(keys['w']||keys['W']) entity.moveZ(-VELOCITY_ENTITY);
	if(keys['s']||keys['S']) entity.moveZ(VELOCITY_ENTITY);
	if(keys['a']||keys['A']) entity.moveX(-VELOCITY_ENTITY);
	if(keys['d']||keys['D']) entity.moveX(VELOCITY_ENTITY);

	return res;
}

//Output
void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glTranslatef(0.0f,-2.0f,-10.0f);
	//glRotatef(20,1.0f,0.0f,0.0f);

	static float n=0; n+=0.01;
	models[0].Render(-3,0,0,  -90,0,   0 + (int)n%40,1,  1,1,  0,0,0);
	models[1].Render( 0,0,0,  -90,0,  40 + (int)n% 6,1,	 1,1,  0,0,0);
	models[2].Render( 3,0,0,  -90,0,  66 + (int)n% 6,1,  1,1,  0,0,0);

	camera.render();
	scene.render(&data);
	if(camera.state != STATE_FIRST_PERSON) entity.render(&data);

	glutSwapBuffers();
}
