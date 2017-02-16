// To compile and link, need to add link flag in Makefile: -lSDL2_image
// Also need to install libsdl2-image-dev

#include <iostream>
#include <cstdlib>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "textureManager.h"
#include "objectManager.h"
//#include "frameGenerator.h"

// Approximately 60 frames per second: 1000
const unsigned int DT = 17u; // ***

void draw(SDL_Renderer* rend, TextureManager& tm, ObjectManager& om) {
  //clear the screen
  SDL_RenderClear(rend);

  //draw background and game objects
  SDL_RenderCopy(rend, tm.getBackgroundTexture(), NULL, NULL);
  om.drawObjects(rend);

  //render results
  SDL_RenderPresent(rend);
}

void update(FrameGenerator& frameGen, bool makeVideo, ObjectManager& om, int stage) {

  static unsigned int remainder = 0u; // ***
  static unsigned int prevTicks = SDL_GetTicks();
  unsigned int currentTicks = SDL_GetTicks();
  unsigned int elapsedTicks = currentTicks - prevTicks + remainder; // ***

  if( elapsedTicks < DT ) return;

  // Generate a frame:
  if ( makeVideo ) frameGen.makeFrame();

  prevTicks = currentTicks;
  remainder = elapsedTicks - DT; // ***

  //update objects
  om.updateObjects(stage);
}

int main( ) {
  //setup SDL
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = 
    SDL_CreateWindow("The Chase", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

  SDL_Renderer *renderer = 
    SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

  //initailize neccessary variables and objects
  SDL_Event event;
  const Uint8* keystate;
  int nKeys=-1;
  bool makeVideo = false;
  bool done = false;
  FrameGenerator frameGen(renderer, window);

  //load textures with texture manager
  TextureManager tm;
  tm.initTextures(renderer);

  //initalize game objects through object manager
  ObjectManager om;
  om.initGameObjects(tm);

  //stage is the current step in the animation, counter is frame in current stage
  int stage = 0, counter = 0;

  while ( !done ) {
    //poll for input
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

    //update game state to handle different stages of animation
    switch (stage) {
      case 0: if (counter > 180) { stage++; counter = 0; } break;
      case 1: if (counter > 100) { stage++; counter = 0; } break;
      case 2: if (counter > 60) { stage++; counter = 0; } break;
      case 3: if (counter > 100) { stage++; counter = 0; } break;
      case 4: if (counter > 140) { stage++; counter = 0; } break;
      case 5: if (counter > 35) { stage++; counter = 0; } break;
      case 6: if (counter > 75) { stage++; counter = 0; } break;
      case 7: if (counter > 10) { stage++; counter = 0; } break;
      case 8: if (counter > 122) { stage++; counter = 0; } break;
      case 9: done = true; break; //end the game animation completes
    }
    counter++;

    draw(renderer, tm, om);
    update(frameGen, makeVideo, om, stage);
  }

  //cleanup
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
