#pragma once

#include "Reward.h";

class BigArrows :public Reward
{
public:
	int suma = 20;
	//BigArrows();
	BigArrows(Point2D esqIzq, Vector2D vel, uint ancho, uint alto, Texture* premio, Texture* _burbuje, Game* game, int _color);

	//Reward::Reward(Point2D esqIzq, Vector2D vel, uint ancho, uint alto, Texture* premio, Texture* _burbuje, Game* game, int _color) :ArrowsGameObject(esqIzq, vel, ancho, alto, premio, game) {

private:
	void accion(bool active);
};


