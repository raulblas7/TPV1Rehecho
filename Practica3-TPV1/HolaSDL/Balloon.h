#pragma once
#include "ArrowsGameObject.h"

using uint = unsigned int;
class Game;
const uint TIME_PER_FRAME = 100;

class Balloon:public ArrowsGameObject
{
private:
	int row;
	bool pinchado = false;
	uint pinchazoTime;
	int frameAnimation =0;
public:
	Balloon(Point2D pos_, Vector2D vel_, int width_, int height_, int row_, Texture* balloon_, Game* game_);
	~Balloon() {};
	void render();
	void update() ;
	SDL_Rect getRect() { return SDL_Rect{ (int)pos.getX(), (int)pos.getY(), width, height }; };
};

