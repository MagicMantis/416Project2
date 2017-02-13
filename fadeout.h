#include "stageObject.h"

class FadeOut : public StageObject {
public:
	FadeOut(int xp, int yp, int w, int h, int ds) : 
		StageObject(xp,yp,w,h,ds,NULL), fade(0) {}

	void update(int stage);
	void draw(SDL_Renderer* render);
private:
	int fade;
};
