#include "gameObject.h"
#include "texture.h"

class Building : public GameObject {
public:
	Building() : x(0), y(0), scale(0), texture(NULL) {}
	Building(float xp, float yp, float sc, Texture* t) : 
		x(xp), y(yp), scale(sc), texture(t) {}
	~Building() {}

	void update(int stage);
	void draw(SDL_Renderer* render);
private:
	float x,y,scale;
	Texture* texture;

	//disallow unwanted functions
	Building(const Building&);
	Building& operator=(const Building&);
};
