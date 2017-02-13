#include "stageObject.h"

class Lightning : public StageObject {
public:
	Lightning(int xp, int yp, int w, int h, int ds, Texture* t) : 
		StageObject(xp,yp,w,h,ds,t) {}

	void draw(SDL_Renderer* render);
};
