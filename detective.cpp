#include "detective.h"

void Detective::update(int stage) {
	if (stage == 0) {
		x -= 7;
	}
	if (stage == 4) {
		imgIndex = 1;
	}
}

void Detective::draw(SDL_Renderer* render) {
	SDL_Rect srcrect = {texture->getWidth()*imgIndex, 0, texture->getWidth(), texture->getHeight()};
	SDL_Rect dstrect = {x, y, texture->getWidth(), texture->getHeight()};
	SDL_RenderCopy(render, texture->getImage(), &srcrect, &dstrect);
}
