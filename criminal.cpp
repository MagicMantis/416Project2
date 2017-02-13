#include "criminal.h"

void Criminal::update(int stage) {
	if (stage == 0) {
		x -= 7;
	}
}

void Criminal::draw(SDL_Renderer* render) {
	SDL_Rect dstrect = {x, y, texture->getWidth(), texture->getHeight()};
	SDL_RenderCopy(render, texture->getImage(), NULL, &dstrect);
}
