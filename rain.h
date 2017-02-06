class Rain : GameObject {
public:
	Rain() : x(0), y(0),length(0),wrap(0),speed(0) {}
	Rain(float xp, float yp, int len, int w, float s) : 
		x(xp), y(yp), length(len), wrap(w), speed((float) len / 10.0f * s) {}
	~Rain() {}

	void update();
	void draw(SDL_Renderer* render);
private:
	float x, y;
	int length, wrap;
	float speed;
};