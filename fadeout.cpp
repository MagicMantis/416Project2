#include "fadeout.h"

void FadeOut::update(int stage) {
	if (stage == drawStage) {
		doDraw = true;
		fade += 2;
		if (fade > 255) fade = 255;
	}
}

void FadeOut::draw(SDL_Renderer* render) {
	if (doDraw) {
		SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(render, 0,0,0,fade);
		SDL_Rect fillrect = {0,0,640,640};
		SDL_RenderFillRect(render, &fillrect);
	}
}
