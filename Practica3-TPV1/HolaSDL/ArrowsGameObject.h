#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"
#include <list>
#include <fstream>
#include "SDLGameObject.h"
#include "GameState.h"


class ArrowsGameObject:public SDLGameObject
{
protected:
	Vector2D vel;

	ArrowsGameObject(Point2D pos_, Vector2D vel_, int width_, int height_, Texture* texture_, GameState* state)
		: SDLGameObject(pos_,width_,height_,texture_,state),vel(vel_) {};
	
public:
	~ArrowsGameObject() {};
	virtual void render();
	virtual void update();
	SDL_Rect getDestRect() {
		
		return SDL_Rect{ (int)pos.getX() , (int)pos.getY(), width , height };
	}
	SDL_Rect getCollisionRect()
	{
		return SDL_Rect{ (int)pos.getX() + width / 2,(int)pos.getY() + height / 2, width/2,height/2 };
	}
	virtual void loadFromFile(ifstream& input);
	virtual void saveToFile(ofstream& outuput);

};

