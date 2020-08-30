#pragma once

#include "Reward.h";

class BigArrows :public Reward
{
public:
	int suma = 20;
	BigArrows(Point2D esqIzq, Vector2D vel, uint ancho, uint alto, Texture* premio, Texture* _burbuje, Game* game, int _color,int timePower);
private:
	void accion(bool active);
};


