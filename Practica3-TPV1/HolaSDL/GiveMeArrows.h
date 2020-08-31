#pragma once

#include "Reward.h";

class GiveMeArrows :public Reward
{
public:
	GiveMeArrows(Point2D esqIzq, Vector2D vel, uint ancho, uint alto, Texture* premio, Texture* _burbuje, Game* game, int _color);
	~GiveMeArrows() {};
private:

	void accion(bool active);
};


