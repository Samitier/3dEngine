#include "Data.h"

Data::Data(void) {}
Data::~Data(void){}

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