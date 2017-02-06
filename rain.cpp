#include "rain.h"

void Rain::update() {
	y += speed;
	if (y > wrap) y = -length;
	x -= speed/10;
	if (x < 0) x += 1000;
}

void Rain::draw(SDL_Renderer* render) {
	SDL_RenderSetScale(render, (float)length/10.0f+.5, (float)length/10.0f+.5);
	SDL_SetRenderDrawColor(render, 0xff,0x05,0xff,0xff);
	SDL_RenderDrawLine(render, (int)x,(int)y,(int)x,(int)y+length);
	SDL_RenderSetScale(render, 1,1);
}