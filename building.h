#include "gameObject.h"

class Building : public GameObject {
public:
	Building() : x(0), y(0), scale(0), img(NULL) {}
	Building(float xp, float yp, float sc, SDL_Texture* i) : 
		x(xp), y(yp), scale(sc), img(i) {}
	~Building() {}

	void update();
	void draw(SDL_Renderer* render);
private:
	float x,y,scale;
	SDL_Texture* img;
	Building(const Building&);
	Building& operator=(const Building&);
};
