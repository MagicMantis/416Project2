[1mdiff --git a/building.cpp b/building.cpp[m
[1mindex f126f2e..2e1cb20 100644[m
[1m--- a/building.cpp[m
[1m+++ b/building.cpp[m
[36m@@ -5,6 +5,7 @@[m [mvoid Building::update(int stage) {[m
 }[m
 [m
 void Building::draw(SDL_Renderer* render) {[m
[32m+[m	[32mif (!inBounds(x,y,texture->getWidth(),texture->getHeight())) return;[m
 	SDL_Rect dstrect = {x, y, texture->getWidth()*scale, texture->getHeight()*scale};[m
 	SDL_RenderCopy(render, texture->getImage(), NULL, &dstrect);[m
 }[m
[1mdiff --git a/criminal.cpp b/criminal.cpp[m
[1mindex 94de43b..cf02d54 100644[m
[1m--- a/criminal.cpp[m
[1m+++ b/criminal.cpp[m
[36m@@ -4,7 +4,7 @@[m [mvoid Criminal::update(int stage) {[m
 	if (stage == 0) {[m
 		x -= 7;[m
 	}[m
[31m-	if (stage == 5) {[m
[32m+[m	[32mif (stage == 4) {[m
 		imgIndex = 1;[m
 	}[m
 	if (stage == 7) {[m
[1mdiff --git a/detective.cpp b/detective.cpp[m
[1mindex f70d3cb..9d6a7bd 100644[m
[1m--- a/detective.cpp[m
[1m+++ b/detective.cpp[m
[36m@@ -4,7 +4,7 @@[m [mvoid Detective::update(int stage) {[m
 	if (stage == 0) {[m
 		x -= 7;[m
 	}[m
[31m-	if (stage == 5) {[m
[32m+[m	[32mif (stage == 4) {[m
 		imgIndex = 1;[m
 	}[m
 }[m
[1mdiff --git a/frameGenerator.h b/frameGenerator.h[m
[1mindex d2d4974..01ea6e4 100644[m
[1m--- a/frameGenerator.h[m
[1m+++ b/frameGenerator.h[m
[36m@@ -1,3 +1,6 @@[m
[32m+[m[32m#ifndef FRAMEGEN_H[m
[32m+[m[32m#define FRAMEGEN_H[m
[32m+[m
 #include <string>[m
 #include <SDL.h>[m
 [m
[36m@@ -22,3 +25,5 @@[m [mprivate:[m
   FrameGenerator(const FrameGenerator&);[m
   FrameGenerator& operator=(const FrameGenerator&);[m
 };[m
[32m+[m
[32m+[m[32m#endif[m
[1mdiff --git a/gameObject.cpp b/gameObject.cpp[m
[1mindex e69de29..fbe0016 100644[m
[1m--- a/gameObject.cpp[m
[1m+++ b/gameObject.cpp[m
[36m@@ -0,0 +1,6 @@[m
[32m+[m[32m#include "gameObject.h"[m
[32m+[m
[32m+[m[32mbool GameObject::inBounds(int x, int y, int w, int h) {[m
[32m+[m	[32mif (x < 0-w || x > WIDTH || y < 0-h || y > HEIGHT) return false;[m
[32m+[m	[32mreturn true;[m
[32m+[m[32m}[m
[1mdiff --git a/gameObject.h b/gameObject.h[m
[1mindex dc1a82f..1c5add4 100644[m
[1m--- a/gameObject.h[m
[1m+++ b/gameObject.h[m
[36m@@ -2,12 +2,15 @@[m
 #define GAMEOBJECT_H[m
 [m
 #include <SDL.h>[m
[32m+[m[32m#include "frameGenerator.h"[m
 [m
 class GameObject {[m
 public:[m
 	virtual ~GameObject() {}[m
 	virtual void update(int stage)=0;	[m
 	virtual void draw(SDL_Renderer* render)=0;[m
[32m+[m
[32m+[m	[32mbool inBounds(int x, int y, int w, int h);[m
 };[m
 [m
 #endif[m
[1mdiff --git a/images/criminal.xcf b/images/criminal.xcf[m
[1mindex b9de64c..9749649 100644[m
Binary files a/images/criminal.xcf and b/images/criminal.xcf differ
[1mdiff --git a/main.cpp b/main.cpp[m
[1mindex f472e5f..2776bf2 100644[m
[1m--- a/main.cpp[m
[1m+++ b/main.cpp[m
[36m@@ -35,7 +35,7 @@[m [mSDL_Texture* getTexture(SDL_Renderer* rend, const std::string& filename) {[m
   }[m
 }[m
 [m
[31m-void initGameObjects(std::vector<GameObject*>& gameObjects, Texture** textures) {[m
[32m+[m[32mvoid initGameObjects(std::vector<GameObject*>& gameObjects, std::vector<Texture*>& textures) {[m
 [m
   for (int i = 0; i < rain_count*2; i++) {[m
     gameObjects.push_back(new Rain(i*(WIDTH/rain_count), (rand()%HEIGHT), rand()%3+3, HEIGHT, 5));[m
[36m@@ -133,15 +133,15 @@[m [mint main( ) {[m
   SDL_Texture *lightning = getTexture(renderer, "images/lightning.png");[m
 [m
   //create texture wrappers[m
[31m-  Texture* textures[10];[m
[31m-  textures[0] = new Texture(building1, 300, 450);[m
[31m-  textures[1] = new Texture(building2, 300, 450);[m
[31m-  textures[2] = new Texture(rooftop, 640, 400);[m
[31m-  textures[3] = new Texture(detective, 32, 64);[m
[31m-  textures[4] = new Texture(criminal, 128, 64);[m
[31m-  textures[5] = new Texture(dtext, 640, 100);[m
[31m-  textures[6] = new Texture(ctext, 640, 100);[m
[31m-  textures[7] = new Texture(lightning, 300, 300);[m
[32m+[m[32m  std::vector<Texture*> textures;[m
[32m+[m[32m  textures.push_back(new Texture(building1, 300, 450));[m
[32m+[m[32m  textures.push_back(new Texture(building2, 300, 450));[m
[32m+[m[32m  textures.push_back(new Texture(rooftop, 640, 400));[m
[32m+[m[32m  textures.push_back(new Texture(detective, 32, 64));[m
[32m+[m[32m  textures.push_back(new Texture(criminal, 128, 64));[m
[32m+[m[32m  textures.push_back(new Texture(dtext, 640, 100));[m
[32m+[m[32m  textures.push_back(new Texture(ctext, 640, 100));[m
[32m+[m[32m  textures.push_back(new Texture(lightning, 300, 300));[m
 [m
   SDL_Event event;[m
   const Uint8* keystate;[m
[36m@@ -178,6 +178,8 @@[m [mint main( ) {[m
       case 5: if (counter > 35) { stage++; counter = 0; } break;[m
       case 6: if (counter > 75) { stage++; counter = 0; } break;[m
       case 7: if (counter > 10) { stage++; counter = 0; } break;[m
[32m+[m[32m      case 8: if (counter > 122) { stage++; counter = 0; } break;[m
[32m+[m[32m      case 9: done = true; break;[m
     }[m
     counter++;[m
 [m
[36m@@ -190,7 +192,7 @@[m [mint main( ) {[m
     delete gameObjects[i];[m
   }[m
   SDL_DestroyTexture(background);[m
[31m-  for (int i = 0; i < 8; i++) {[m
[32m+[m[32m  for (size_t i = 0; i < textures.size(); i++) {[m
     delete textures[i];[m
   }[m
 [m
[1mdiff --git a/stageObject.cpp b/stageObject.cpp[m
[1mindex 5873914..0edb854 100644[m
[1m--- a/stageObject.cpp[m
[1m+++ b/stageObject.cpp[m
[36m@@ -3,8 +3,10 @@[m
 [m
 void StageObject::update(int stage) {[m
 	doDraw = (stage == drawStage);[m
[31m-	x += rand()%3-1;[m
[31m-	y += rand()%3-1;[m
[32m+[m	[32mif (doDraw) {[m
[32m+[m		[32mx += rand()%3-1;[m
[32m+[m		[32my += rand()%3-1;[m[41m	[m
[32m+[m	[32m}[m
 }[m
 [m
 void StageObject::draw(SDL_Renderer* render) {[m
[1mdiff --git a/texture.h b/texture.h[m
[1mindex 06d7628..32f4509 100644[m
[1m--- a/texture.h[m
[1m+++ b/texture.h[m
[36m@@ -1,10 +1,12 @@[m
 #ifndef TEXTURE_H[m
 #define TEXTURE_H[m
 [m
[32m+[m[32m#include <iostream>[m
[32m+[m
 class Texture {[m
 public:[m
 	Texture(SDL_Texture* i, int w, int h) : img(i), width(w), height(h) {}[m
[31m-	~Texture() { SDL_DestroyTexture(img); }[m
[32m+[m	[32m~Texture() { std::cout << "Called that one" << std::endl; SDL_DestroyTexture(img); }[m
 [m
 	SDL_Texture* getImage() const { return img; }[m
 	int getWidth() const { return width; }[m
