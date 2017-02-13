#include "gameObject.h"
#include "texture.h"

class Detective : public GameObject {
public:
	Detective(float xp, float yp, Texture* t) : 
		x(xp), y(yp), imgIndex(0), texture(t) {}
	~Detective() {}

	void update(int stage);
	void draw(SDL_Renderer* render);
private:
	float x, y;
	int imgIndex;
	Texture* texture;

	//disallow unwanted functions
	Detective();
	Detective(const Detective&);
};
