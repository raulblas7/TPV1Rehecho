#pragma once
#include "ArrowsGameObject.h"

class Arrow:public ArrowsGameObject
{
public:
	Arrow(Point2D pos_, Vector2D vel_, int width_, int height_, Texture* arrow_, Game* game_);
	~Arrow();
	void render();
	void update();
	SDL_Rect getRect() {
		return SDL_Rect{ (int)pos.getX() + (width / 3) * 2, (int)pos.getY(), width / 3, height };
	}
};

