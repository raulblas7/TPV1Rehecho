#pragma once

#include "Reward.h";

class GiveMeArrows :public Reward
{
public:
	GiveMeArrows(Point2D esqIzq, Vector2D vel, uint ancho, uint alto, Texture* premio, Texture* _burbuje, int _color ,GameState* game);
	~GiveMeArrows() {};
private:

	void accion(bool active);
};


