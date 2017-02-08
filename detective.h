#include "gameObject.h"
#include "texture.h"

class Detective : public GameObject {
public:
	Detective(float xp, float yp, Texture* t) : x(xp), y(yp), texture(t) {}
	~Detective() {}

	void update(int stage);
	void draw(SDL_Renderer* render);
private:
	float x, y;
	Texture* texture;

	//disallow unwanted functions
	Detective();
	Detective(const Detective&);
};
