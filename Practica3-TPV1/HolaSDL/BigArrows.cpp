#include "BigArrows.h"
#include "Game.h"

BigArrows::BigArrows(Point2D esqIzq, Vector2D vel, uint ancho, uint alto, Texture* premio, Texture* _burbuje, Game* game, int _color) :Reward(esqIzq, vel, ancho, alto, _color, premio, _burbuje, game)
{}
void BigArrows::accion(bool active) {
	if (!active)
	{
		suma *= -1;
	}
	game->ArrowSize(suma);
}
