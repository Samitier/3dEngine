#include "Data.h"

Data::Data(void) {}
Data::~Data(void){}

bool Data::init() {
	bool res = true;
	res = res && LoadImage(IMG_WALL,"wall.png",GL_RGBA);
	res = res && LoadImage(IMG_FLOOR,"floor.png",GL_RGBA);
	res = res && LoadImage(IMG_ROOF,"roof.png",GL_RGBA);
	res = res && LoadImage(IMG_SUN, "sun.jpg", GL_RGBA);
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