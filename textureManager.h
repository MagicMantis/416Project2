#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>
#include "texture.h"

/**
 * TextureManager class: this class loads and manages references to
 * all textures neccessary for the game. It also manages the memory
 * and frees used textures upon deconstruction.
 */
class TextureManager {
public:
	TextureManager() : textures() {}
	~TextureManager();

	Texture* getTexture(const std::string&) const;
	SDL_Texture* getBackgroundTexture() const;
	void initTextures(SDL_Renderer*);
private:
	std::map<std::string, Texture*> textures;
	SDL_Texture* background;

	//internal functions
	SDL_Texture* loadTexture(SDL_Renderer*, const std::string&);
};

#endif
