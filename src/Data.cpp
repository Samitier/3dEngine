#include "Data.h"

Data::Data(void) {}
Data::~Data(void){}

bool Data::init() {
	bool res = true;
	res = res && LoadImage(IMG_WALL,"assets/textures/wall.png",GL_RGBA);
	res = res && LoadImage(IMG_FLOOR,"assets/textures/floor.png",GL_RGBA);
	res = res && LoadImage(IMG_ROOF,"assets/textures/roof.png",GL_RGBA);
	res = res && LoadImage(IMG_SUN, "assets/textures/sun.jpg", GL_RGBA);
	return res;
}

int Data::GetID(int img)
{
	return texture[img].GetID();
}

void Data::GetSize(int img, int *w, int *h)
{
	texture[img].GetSize(w,h);
}

bool Data::LoadImage(int img, char *filename, int type)
{
	int res;

	res = texture[img].Load(filename,type);
	if(!res) return false;

	return true;
}