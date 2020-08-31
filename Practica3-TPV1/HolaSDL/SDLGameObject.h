#pragma once
#include "Vector2D.h"
#include "GameObject.h"
#include "Texture.h"
class GameState;

class SDLGameObject : public GameObject
{
public:
	virtual ~SDLGameObject() {};
	virtual void update() {};
	virtual void render();
protected:
	SDLGameObject(Point2D pos_, int width_, int height_, Texture* texture_, GameState* estado_) :pos(pos_), width(width_),
		height(height_), texture(texture_), state(estado_) {}
	Point2D pos;
	Texture* texture;
	int width, height;
	GameState* state=nullptr;
	

};

