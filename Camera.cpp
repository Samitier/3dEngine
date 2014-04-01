#include "Camera.h"


Camera::Camera(void)
{
}


Camera::~Camera(void)
{
}

void Camera::init(){
	state = STATE_DEFAULT;
}

void Camera::setState(int sta) {
	state = sta;
}

void Camera::render(){
	switch(state) {
		case STATE_DEFAULT:
			glTranslatef(0.0f,-2.0f,-40.0f);
			glRotatef(20,1.0f,0.0f,0.0f);
			break;
		case STATE_2:	
			gluLookAt(0,40,0,0,0,0,0,0,-1);
			break;
		case STATE_3:
			gluLookAt(0,30,40,0,0,0,0,1,0);
			break;
		case STATE_4:
			gluLookAt(40,30,0,0,0,0,0,1,0);
			break;
		case STATE_5:
			gluLookAt(-40,30,0,0,0,0,0,1,0);
			break;
	}
}