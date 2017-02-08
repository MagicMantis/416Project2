#include <iostream>
#include "building.h"

void Building::update() {

}

void Building::draw(SDL_Renderer* render) {
	SDL_Rect dstrect = {x, y, 200*scale, 400*scale};
	SDL_RenderCopy(render, img, NULL, &dstrect);
}
