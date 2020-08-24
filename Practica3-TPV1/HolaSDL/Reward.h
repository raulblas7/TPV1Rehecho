#pragma once
#include "EventHandler.h"
#include "ArrowsGameObject.h"
class Reward:public ArrowsGameObject, EventHandler
{
private:
	bool burbuja = true;
	Texture* bubble;
	int row;
public:
	Reward(Point2D pos_, Vector2D vel_, int width_, int height_, int row_, Texture* reward_, Texture* bubble_, Game* game_);
	void render();
	void update();
	void handleEvents(SDL_Event& event);
};

