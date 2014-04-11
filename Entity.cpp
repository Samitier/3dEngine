#include "Entity.h"


Entity::Entity(void)
{
}


Entity::~Entity(void)
{
}

void Entity::init() {
	x=y=z=rot=0;
}

void Entity::moveZ(float velocity) {
	z -=cos(rot*RADIAN)*velocity;
	x +=sin(rot*RADIAN)*velocity;
}

void Entity::moveX(float velocity){
	z -=sin(rot*RADIAN)*velocity;
	x -=cos(rot*RADIAN)*velocity;
}

void Entity::render(Data *data) {
	glPushMatrix();
	glTranslatef(x,y,z);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,data->GetID(IMG_SUN));
	GLUquadricObj *mesh = gluNewQuadric();
	gluSphere(mesh, 1,16,16);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}