#pragma once

#include "Texture.h"
#include "Globals.h"

//Image array size
#define NUM_IMG		4

//Image identifiers
#define IMG_WALL	0
#define IMG_FLOOR	1
#define IMG_ROOF	2
#define IMG_SUN     3

class Data
{
public:
	Data(void);
	~Data(void);

	bool init();
	int  GetID(int img);
	void GetSize(int img,int *w,int *h);
	bool LoadImage(int img,char *filename,int type = GL_RGBA);

private:
	Texture texture[NUM_IMG];
};
