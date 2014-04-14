#pragma once

#include "Data.h"

#define SCENE_WIDTH		16
#define SCENE_DEPTH		32
#define SCENE_HEIGHT	 4

class Scene
{
public:
	Scene(void);
	virtual ~Scene(void);

	bool init();
	void render(Data *Data);
};
