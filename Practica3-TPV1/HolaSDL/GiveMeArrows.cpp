#include "GiveMeArrows.h"
#include"PlayState.h"

GiveMeArrows::GiveMeArrows(Point2D esqIzq, Vector2D vel, uint ancho, uint alto, Texture* premio, Texture* _burbuje, int _color,GameState* game ) :Reward(esqIzq, vel, ancho, alto, _color, premio, _burbuje,0, game) {}

void GiveMeArrows::accion(bool active) {
	if (active)
	{
		dynamic_cast<PlayState*>(state)->AddArrows(2);
	}
}
