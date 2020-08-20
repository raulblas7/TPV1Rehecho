#pragma once
#include "Vector2D.h"
#include "Texture.h"
using uint = unsigned int;
class Game;
class Balloon
{
private:
	Point2D pos;
	Vector2D vel;
	Texture* balloon;
	int width, height;
	bool pinchado = false;
	uint pinchazoTime;
	Game* game;

public:
	Balloon(Point2D pos_, Vector2D vel_, int width_, int height_, Texture* balloon_ , Game* game_);
	~Balloon();
	void render()const;
	bool update() const;
};
