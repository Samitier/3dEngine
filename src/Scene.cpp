#include "Scene.h"
#include "Globals.h"

Scene::Scene(void) {}
Scene::~Scene(void){}

void Scene::render(Data *Data)
{
	float d  = SCENE_DEPTH/2.0f,
		  w  = SCENE_WIDTH/2.0f,
		  h  = SCENE_HEIGHT/2.0f,
		  //Tiling
		  td = SCENE_DEPTH/4.0f,
		  tw = SCENE_WIDTH/4.0f,
		  th = SCENE_HEIGHT/4.0f;

	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_WALL));
	glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-w, -h,  d);
		glTexCoord2f(  tw, 0.0f); glVertex3f( w, -h,  d);
		glTexCoord2f(  tw,   th); glVertex3f( w,  h,  d);
		glTexCoord2f(0.0f,   th); glVertex3f(-w,  h,  d);
		// Back Face
		glTexCoord2f(  tw, 0.0f); glVertex3f(-w, -h, -d);
		glTexCoord2f(  tw,   th); glVertex3f(-w,  h, -d);
		glTexCoord2f(0.0f,   th); glVertex3f( w,  h, -d);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( w, -h, -d);
		// Right face
		glTexCoord2f(  td, 0.0f); glVertex3f( w, -h, -d);
		glTexCoord2f(  td,   th); glVertex3f( w,  h, -d);
		glTexCoord2f(0.0f,   th); glVertex3f( w,  h,  d);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( w, -h,  d);
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-w, -h, -d);
		glTexCoord2f(  td, 0.0f); glVertex3f(-w, -h,  d);
		glTexCoord2f(  td,   th); glVertex3f(-w,  h,  d);
		glTexCoord2f(0.0f,   th); glVertex3f(-w,  h, -d);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_FLOOR));
	glBegin(GL_QUADS);
		// Bottom Face
		glTexCoord2f(  tw,   td); glVertex3f(-w, -h, -d);
		glTexCoord2f(0.0f,   td); glVertex3f( w, -h, -d);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( w, -h,  d);
		glTexCoord2f(  tw, 0.0f); glVertex3f(-w, -h,  d);
	glEnd();
	/*
	glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_ROOF));
	glBegin(GL_QUADS);
		// Top Face
		glTexCoord2f(0.0f,   td); glVertex3f(-w,  h, -d);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-w,  h,  d);
		glTexCoord2f(  tw, 0.0f); glVertex3f( w,  h,  d);
		glTexCoord2f(  tw,   td); glVertex3f( w,  h, -d);
	glEnd();
	*/
	glDisable(GL_TEXTURE_2D);
}