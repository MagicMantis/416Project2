// To compile and link, need to add link flag in Makefile: -lSDL2_image
// Also need to install libsdl2-image-dev

#include <iostream>
#include <cstdlib>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
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

void initGameObjects(std::vector<GameObject*>& gameObjects, Texture** textures) {

  for (int i = 0; i < rain_count*2; i++) {
    gameObjects.push_back(new Rain(i*(WIDTH/rain_count), (rand()%HEIGHT), rand()%3+3, HEIGHT, 5));
  }

  //create buildings
  gameObjects.push_back(new Building(400,250,.7,textures[0]));
  gameObjects.push_back(new Building(670,200,.9,textures[1]));
  gameObjects.push_back(new Building(1000,250,.8,textures[0]));
  gameObjects.push_back(new Building(1100,370,.5,textures[1]));
  gameObjects.push_back(new Building(1100,200,.5,textures[1]));

  //create back ground rain drops
  for (int i = 0; i < rain_count; i++) {
    gameObjects.push_back(new Rain(i*(WIDTH/rain_count), (rand()%HEIGHT), rand()%3+6, HEIGHT, 4));
  }

  //create rooftop
  gameObjects.push_back(new Building(1250,100,1,textures[2]));

  //create characters
  gameObjects.push_back(new Detective(1400,370,textures[3]));
  gameObjects.push_back(new Criminal(1650,370,textures[4]));

  //create raindrops
	for (int i = 0; i < rain_count; i++) {
		gameObjects.push_back(new Rain(i*(WIDTH/rain_count), (rand()%HEIGHT), rand()%2+9, HEIGHT, 4));
	}

  //create text and lightning effects
  gameObjects.push_back(new StageObject(0,0,500,100,1,textures[5]));
  gameObjects.push_back(new StageObject(0,0,500,100,3,textures[6]));
  gameObjects.push_back(new Lightning(300,-70,300,300,5,textures[7]));

  //create fadeout object
  gameObjects.push_back(new FadeOut(0,0,640,480,8));
}

void draw(SDL_Renderer* rend, SDL_Texture* back, std::vector<GameObject*>& gameObjects) {
  SDL_RenderClear(rend);

  //draw background
  SDL_RenderCopy(rend, back, NULL, NULL);

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

  //load textures
  SDL_Texture *background = getTexture(renderer, "images/bkgnd.png");
  SDL_Texture *building1 = getTexture(renderer, "images/building1.png");
  SDL_Texture *building2 = getTexture(renderer, "images/building2.png");
  SDL_Texture *rooftop = getTexture(renderer, "images/rooftop.png");
  SDL_Texture *detective = getTexture(renderer, "images/detective.png");
  SDL_Texture *criminal = getTexture(renderer, "images/criminal.png");
  SDL_Texture *dtext = getTexture(renderer, "images/dtext.png");
  SDL_Texture *ctext = getTexture(renderer, "images/ctext.png");
  SDL_Texture *lightning = getTexture(renderer, "images/lightning.png");

  //create texture wrappers
  Texture* textures[10];
  textures[0] = new Texture(building1, 300, 450);
  textures[1] = new Texture(building2, 300, 450);
  textures[2] = new Texture(rooftop, 640, 400);
  textures[3] = new Texture(detective, 32, 64);
  textures[4] = new Texture(criminal, 128, 64);
  textures[5] = new Texture(dtext, 640, 100);
  textures[6] = new Texture(ctext, 640, 100);
  textures[7] = new Texture(lightning, 300, 300);

  SDL_Event event;
  const Uint8* keystate;
  int nKeys=-1;
  bool makeVideo = false;
  bool done = false;
  FrameGenerator frameGen(renderer, window);

  std::vector<GameObject*> gameObjects;
  initGameObjects(gameObjects,textures);
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
    }
    counter++;

    draw(renderer, background, gameObjects);
    update(frameGen, makeVideo, gameObjects, stage);
  }

  //cleanup
  for (size_t i = 0; i < gameObjects.size(); i++) {
    delete gameObjects[i];
  }
  SDL_DestroyTexture(background);
  for (int i = 0; i < 8; i++) {
    delete textures[i];
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
}
