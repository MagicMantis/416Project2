// To compile and link, need to add link flag in Makefile: -lSDL2_image
// Also need to install libsdl2-image-dev

#include <iostream>
#include <cstdlib>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "textureManager.h"
#include "rain.h"
#include "building.h"
#include "texture.h"
#include "detective.h"
#include "criminal.h"
#include "stageObject.h"
#include "lightning.h"
#include "fadeout.h"
//#include "frameGenerator.h"

const int rain_count = 200;

// Approximately 60 frames per second: 60/1000
const unsigned int DT = 17u; // ***

void initGameObjects(std::vector<GameObject*>& gameObjects, TextureManager& tm) {

  for (int i = 0; i < rain_count*2; i++) {
    gameObjects.push_back(new Rain(i*(WIDTH/rain_count), (rand()%HEIGHT), rand()%3+3, HEIGHT, 5));
  }

  //create buildings
  gameObjects.push_back(new Building(400,250,.7,tm.getTexture("building1")));
  gameObjects.push_back(new Building(670,200,.9,tm.getTexture("building2")));
  gameObjects.push_back(new Building(1000,250,.8,tm.getTexture("building1")));
  gameObjects.push_back(new Building(1100,370,.5,tm.getTexture("building2")));
  gameObjects.push_back(new Building(1100,200,.5,tm.getTexture("building2")));

  //create back ground rain drops
  for (int i = 0; i < rain_count; i++) {
    gameObjects.push_back(new Rain(i*(WIDTH/rain_count), (rand()%HEIGHT), rand()%3+6, HEIGHT, 4));
  }

  //create rooftop
  gameObjects.push_back(new Building(1250,100,1,tm.getTexture("rooftop")));

  //create characters
  gameObjects.push_back(new Detective(1400,370,tm.getTexture("detective")));
  gameObjects.push_back(new Criminal(1650,370,tm.getTexture("criminal")));

  //create raindrops
  for (int i = 0; i < rain_count; i++) {
    gameObjects.push_back(new Rain(i*(WIDTH/rain_count), (rand()%HEIGHT), rand()%2+9, HEIGHT, 4));
  }

  //create text and lightning effects
  gameObjects.push_back(new StageObject(0,0,500,100,1,tm.getTexture("dtext")));
  gameObjects.push_back(new StageObject(0,0,500,100,3,tm.getTexture("ctext")));
  gameObjects.push_back(new Lightning(300,-70,300,300,5,tm.getTexture("lightning")));

  //create fadeout object
  gameObjects.push_back(new FadeOut(0,0,640,480,8));
}

void draw(SDL_Renderer* rend, TextureManager& tm, std::vector<GameObject*>& gameObjects) {
  SDL_RenderClear(rend);

  //draw background
  SDL_RenderCopy(rend, tm.getBackgroundTexture(), NULL, NULL);

  //call draw() for all game objects
  for ( size_t   i = 0; i < gameObjects.size(); i++ ) {
    gameObjects[i]->draw(rend);
  }

  //render results
  SDL_RenderPresent(rend);
}

void update(FrameGenerator& frameGen, bool makeVideo, 
    std::vector<GameObject*>& gameObjects, int stage) {

  static unsigned int remainder = 0u; // ***
  static unsigned int prevTicks = SDL_GetTicks();
  unsigned int currentTicks = SDL_GetTicks();
  unsigned int elapsedTicks = currentTicks - prevTicks + remainder; // ***

  if( elapsedTicks < DT ) return;

  // Generate a frame:
  if ( makeVideo ) frameGen.makeFrame();

  prevTicks = currentTicks;
  remainder = elapsedTicks - DT; // ***

  //update all game objects
  for ( size_t i = 0; i < gameObjects.size(); i++ ) {
    gameObjects[i]->update(stage);
  }
}

int main( ) {
  int posX = 100, posY = 100;
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = 
    SDL_CreateWindow("The Chase", posX, posY, WIDTH, HEIGHT, 0);

  SDL_Renderer *renderer = 
    SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);


  SDL_Event event;
  const Uint8* keystate;
  int nKeys=-1;
  bool makeVideo = false;
  bool done = false;
  FrameGenerator frameGen(renderer, window);

  TextureManager tm;
  tm.initTextures(renderer);

  std::vector<GameObject*> gameObjects;
  initGameObjects(gameObjects,tm);
  int stage = 0, counter = 0;

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

    //update game state
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
      case 9: done = true; break;
    }
    counter++;

    draw(renderer, tm, gameObjects);
    update(frameGen, makeVideo, gameObjects, stage);
  }

  //cleanup
  for (size_t i = 0; i < gameObjects.size(); i++) {
    delete gameObjects[i];
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
}
