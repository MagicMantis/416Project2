#include "gameObject.h"
#include "texture.h"

class Criminal : public GameObject {
public:
	Criminal(float xp, float yp, Texture *t) : x(xp), y(yp), texture(t) {}
	~Criminal() {}

	void update(int stage);
	void draw(SDL_Renderer* render);
private: 
	float x,y;
	Texture *texture;

	//explicitly disallow compiler generated functions
	Criminal(); //disallow default constructor
	Criminal(const Criminal&); //disallow copy constructor
};
