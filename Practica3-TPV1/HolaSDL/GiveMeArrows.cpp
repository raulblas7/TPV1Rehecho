#include "GiveMeArrows.h"
#include"Game.h"

GiveMeArrows::GiveMeArrows(Point2D esqIzq, Vector2D vel, uint ancho, uint alto, Texture* premio, Texture* _burbuje, Game* game, int _color) :Reward(esqIzq, vel, ancho, alto, _color, premio, _burbuje, game) {}

void GiveMeArrows::accion(bool active) {
	if (active)
	{
		game->AddArrows(2);
	}
}
