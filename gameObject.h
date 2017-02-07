#include <SDL.h>

class GameObject {
public:
	virtual ~GameObject() {}
	virtual void update()=0;	
	virtual void draw(SDL_Renderer* render)=0;
};