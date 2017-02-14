#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>
#include "texture.h"

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
