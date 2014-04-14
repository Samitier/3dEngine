#include "Camera.h"


Camera::Camera(void)
{
}


Camera::~Camera(void)
{
}

void Camera::init(Entity *p){
	player = p;
	setState(STATE_THIRD_PERSON);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	xPos = yPos = zPos = yRot = xRot = 0;
}

void Camera::setState(int sta) {
	switch (state) {
		case STATE_FIRST_PERSON: player->rot =0;  break;
		case STATE_THIRD_PERSON: player->rot =180; break;
		case STATE_TOP: player->rot = 180; break;
	}
	state = sta;
}

void Camera::setRotation(int x, int y) {
	if(state == STATE_FIRST_PERSON) {
		yRot = (float)x/(float)SCREEN_WIDTH; //posem la coordenada relativa a la pantalla
		xRot = (float)y/(float)SCREEN_HEIGHT;
		xRot-=0.5; yRot -= 0.5; //li restem el punt central per a ke surtin graus positius i neg
		xRot *=180; yRot *=360; //la camera pot girar com a maxim 180 graus en les x i 360 en y
		player->rot =yRot;
	}
}

void Camera::render(){
	switch(state) {
		case STATE_THIRD_PERSON:
			glTranslatef(0.0f,-2.0f,-40.0f);
			glRotatef(20,1.0f,0.0f,0.0f);
			break;
		case STATE_TOP:	
			gluLookAt(0,40,0,0,0,0,0,0,-1);
			break;
		case STATE_FIRST_PERSON:
			glRotatef(xRot,1.0f,0.0f,0.0f);
			glRotatef(yRot, 0.0, 1.0, 0.0);
			glTranslatef(player->x, 0.0f, player->z);
			break;
	}
}