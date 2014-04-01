#include "Entity.h"


Entity::Entity(void)
{
}


Entity::~Entity(void)
{
}

void Entity::init() {
	mesh = gluNewQuadric();
	gluSphere(mesh, 1,16,16);
}

void Entity::moveZ(float velocity) {}

void Entity::moveX(float velocity){}

void Entity::render() {
}