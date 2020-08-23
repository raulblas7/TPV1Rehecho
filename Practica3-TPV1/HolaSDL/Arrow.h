#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"
class Arrow
{
private:
	Point2D pos;
	Vector2D vel;
	Texture* arrow;
	int width, height;
	SDL_Rect* rect = nullptr;

public:
	Arrow(Point2D pos_, Vector2D vel_, int width_, int height_, Texture* arrow_);
	~Arrow();
	void render();
	bool update();
	SDL_Rect getRect() {
		return SDL_Rect{ (int)pos.getX() + (width / 3) * 2, (int)pos.getY(), width / 3, height };
	}
};

