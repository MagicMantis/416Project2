#include "building.h"

void Building::update(int stage) {
	if (stage == 0) x -= 7*scale;
}

void Building::draw(SDL_Renderer* render) {
	SDL_Rect dstrect = {x, y, texture->getWidth()*scale, texture->getHeight()*scale};
	SDL_RenderCopy(render, texture->getImage(), NULL, &dstrect);
}
