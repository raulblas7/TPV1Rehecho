#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"
#include <list>
class Game;

class ArrowsGameObject:public GameObject
{
private:
	Point2D pos;
	Vector2D vel;
	Texture* arrow;
	int width, height;
	SDL_Rect* rect = nullptr;
	Game* game = nullptr;
	list<GameObject*>::iterator i;

protected:
	ArrowsGameObject(Point2D pos_, Vector2D vel_, int width_, int height_, Texture* arrow_, Game* game_)
		: GameObject(), pos(pos_), vel(vel_), width(width_), height(height_), arrow(arrow_), game(game_) {};
public:
	virtual void render();
	virtual void update();
	SDL_Rect getRect() {
		return SDL_Rect{ (int)pos.getX() , (int)pos.getY(), width , height };
	}
	void setItList(list<GameObject*>::iterator it);

};

