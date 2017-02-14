#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include "frameGenerator.h"

class GameObject {
public:
	virtual ~GameObject() {}
	virtual void update(int stage)=0;	
	virtual void draw(SDL_Renderer* render)=0;

	bool inBounds(int x, int y, int w, int h);
};

#endif
