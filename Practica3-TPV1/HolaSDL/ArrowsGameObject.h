#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"
#include <list>
#include <fstream>

class Game;

class ArrowsGameObject:public GameObject
{
protected:
	Point2D pos;
	Vector2D vel;
	Texture* texture;
	int width, height;
	SDL_Rect* rect = nullptr;
	Game* game = nullptr;
	list<GameObject*>::iterator it;

	ArrowsGameObject(Point2D pos_, Vector2D vel_, int width_, int height_, Texture* texture_, Game* game_)
		: GameObject(), pos(pos_), vel(vel_), width(width_), height(height_), texture(texture_), game(game_) {};
public:
	virtual void render();
	virtual void update();
	SDL_Rect getDestRect() {
		return SDL_Rect{ (int)pos.getX() , (int)pos.getY(), width , height };
	}
	SDL_Rect getCollisionRect()
	{
		return SDL_Rect{ (int)pos.getX() + width / 2,(int)pos.getY() + height / 2, width/2,height/2 };
	}
	void setItList(list<GameObject*>::iterator it);
	virtual void loadFromFile(ifstream& input);
	virtual void saveToFile(ofstream& outuput);

};

