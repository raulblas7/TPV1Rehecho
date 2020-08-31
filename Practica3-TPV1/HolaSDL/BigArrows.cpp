#include "BigArrows.h"
#include "PlayState.h"

BigArrows::BigArrows(Point2D esqIzq, Vector2D vel, uint ancho, uint alto, Texture* premio, Texture* _burbuje, int _color,int timePower, GameState* game) :Reward(esqIzq, vel, ancho, alto, _color, premio, _burbuje, timePower,game )
{}
void BigArrows::accion(bool active) {
	if (!active)
	{
		suma *= -1;
	}
	dynamic_cast<PlayState*>(state)->ArrowSize(suma);
}

