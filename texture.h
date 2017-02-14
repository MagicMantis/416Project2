#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>

class Texture {
public:
	Texture(SDL_Texture* i, int w, int h) : img(i), width(w), height(h) {}
	~Texture() { SDL_DestroyTexture(img); }

	SDL_Texture* getImage() const { return img; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }

private:
	SDL_Texture* img;
	int width, height;

	//disallow unused constructors
	Texture();
	Texture(const Texture&);
	Texture& operator=(const Texture&);
};

#endif
