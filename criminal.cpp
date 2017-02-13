#include "criminal.h"

void Criminal::update(int stage) {
	if (stage == 0) {
		x -= 7;
	}
	if (stage == 5) {
		imgIndex = 1;
	}
	if (stage == 7) {
		imgIndex = 2;
	}
}

void Criminal::draw(SDL_Renderer* render) {
	SDL_Rect srcrect = {texture->getWidth()*imgIndex, 0, texture->getWidth(), texture->getHeight()};
	SDL_Rect dstrect = {x, y, texture->getWidth(), texture->getHeight()};
	SDL_RenderCopy(render, texture->getImage(), &srcrect, &dstrect);
}
