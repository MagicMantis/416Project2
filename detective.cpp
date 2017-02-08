#include "detective.h"

void Detective::update(int stage) {
	if (stage == 0) {
		x -= 7;
	}
}

void Detective::draw(SDL_Renderer* render) {
	SDL_Rect dstrect = {x, y, texture->getWidth(), texture->getHeight()};
	SDL_RenderCopy(render, texture->getImage(), NULL, &dstrect);
}
