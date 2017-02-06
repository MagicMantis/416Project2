// To compile and link, need to add link flag in Makefile: -lSDL2_image
// Also need to install libsdl2-image-dev

#include <iostream>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include "frameGenerator.h"

const int X_POS = 10;
const int Y_POS = 10;
const float X_VEL = 150.0;
const float Y_VEL = 150.0;
const int rain_count = 100;

// Approximately 60 frames per second: 60/1000
const unsigned int DT = 17u; // ***

SDL_Texture* getTexture(SDL_Renderer* rend, const std::string& filename) {
  try {
    SDL_Texture *texture = IMG_LoadTexture(rend, filename.c_str());
    if ( texture == NULL ) {
      throw std::string("Couldn't load ") + filename;
    }
    return texture;
  }
  catch( const std::string& msg ) { 
    std::cout << msg << std::endl; 
    std::terminate();
  }
}

void initGameObjects(vector<GameObject*> gameObjects) {
	for (int i = 0; i < rain_count; i++) {
		gameObjects.push_back(new Rain(i*2, -10, 5, 1, 1));
	}
}

void draw(SDL_Renderer* rend, SDL_Texture* back, SDL_Texture* star,
          const SDL_Rect& dstrect) {
  SDL_RenderClear(rend);
  SDL_RenderCopy(rend, back, NULL, NULL);
  SDL_RenderCopy(rend, star, NULL, &dstrect);
  SDL_RenderPresent(rend);
}

inline float clamp(const float val, const float lo, const float hi){
  return val <= lo ? lo : ( val >= hi ? hi : val);
}

void update(SDL_Rect& dstrect, FrameGenerator& frameGen, bool makeVideo) {
  static float x = X_POS;
  static float y = Y_POS;

  static unsigned int remainder = 0u; // ***
  static unsigned int prevTicks = SDL_GetTicks();
  unsigned int currentTicks = SDL_GetTicks();
  unsigned int elapsedTicks = currentTicks - prevTicks + remainder; // ***

  if( elapsedTicks < DT ) return;

  // Generate a frame:
  if ( makeVideo ) frameGen.makeFrame();

  float dx = X_VEL * DT * 0.001;
  x += dx;
  float dy = Y_VEL * DT * 0.001;
  y += dy;
  x = clamp(x,0.f,WIDTH-dstrect.w);
  y = clamp(y,0.f,HEIGHT-dstrect.h);

  prevTicks = currentTicks;
  remainder = elapsedTicks - DT; // ***

  dstrect.x = x;
  dstrect.y = y;
}

int main( ) {
  int posX = 100, posY = 100;
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = 
    SDL_CreateWindow("Star Animation", posX, posY, WIDTH, HEIGHT, 0);

  SDL_Renderer *renderer = 
    SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

  SDL_Texture *background = getTexture(renderer, "images/axis.png");
  SDL_Texture *yellowstar = getTexture(renderer, "images/yellowstar.png");

  SDL_Event event;
  const Uint8* keystate;
  int nKeys=-1;
  SDL_Rect dstrect = {X_POS, Y_POS, 32, 32};
  bool makeVideo = false;
  bool done = false;
  FrameGenerator frameGen(renderer, window);

  vector<GameObject*> gameObjects;
  initGameObjects(gameObjects);

  while ( !done ) {
    while ( SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        done = true;
      }
      keystate = SDL_GetKeyboardState(&nKeys);
      if (keystate[SDL_SCANCODE_ESCAPE]) { 
        done = true; 
      }
      if (keystate[SDL_SCANCODE_F4]) { 
        makeVideo = true;
      }
    }

    draw(renderer, background, yellowstar, dstrect);
    update(dstrect, frameGen, makeVideo);
  }

  SDL_DestroyTexture(yellowstar);
  SDL_DestroyTexture(background);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
