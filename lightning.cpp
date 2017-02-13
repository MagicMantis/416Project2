#include "lightning.h"

void Lightning::draw(SDL_Renderer* render) {
	if (doDraw) {
		SDL_Rect dstrect = {x, y, texture->getWidth(), texture->getHeight()};
		SDL_RenderCopy(render, texture->getImage(), NULL, &dstrect);
		SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(render, 255,255,255,100);
		SDL_Rect fillrect = {0,0,640,640};
		SDL_RenderFillRect(render, &fillrect);
	}
}
