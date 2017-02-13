#ifndef STAGEOBJECT_H
#define STAGEOBJECT_H

#include "gameObject.h"
#include "texture.h"

class StageObject : public GameObject {
public:
	StageObject(int xp, int yp, int w, int h, int ds, Texture* t) : 
			x(xp), y(yp), width(w), height(h), drawStage(ds), doDraw(false), texture(t) {}
	~StageObject() {}

	void update(int stage);
	virtual void draw(SDL_Renderer* render);
protected:
	int x,y,width,height,drawStage;
	bool doDraw;
	Texture* texture;

	//disallow compiler generated constructors
	StageObject();
	StageObject(const StageObject&);
};

#endif
