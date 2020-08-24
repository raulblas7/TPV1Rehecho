#pragma once
#include "ArrowsGameObject.h"

class Butterfly:public ArrowsGameObject
{
private:
	int row;
public:
	Butterfly(Point2D pos_, Vector2D vel_, int width_, int height_, int row_, Texture* balloon_, Game* game_);
	~Butterfly() {};
	void render();
	void update();
	SDL_Rect getRect() { return SDL_Rect{ (int)pos.getX(), (int)pos.getY(), width, height }; };
};

