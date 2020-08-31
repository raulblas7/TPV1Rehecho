#include "Scoreboard.h"
#include "checkML.h"
#include "PlayState.h"
using namespace std;
Scoreboard::Scoreboard() : GameObject(), esqIzq(), ancho(), alto(), points(), arrows(),game() {
}
Scoreboard::Scoreboard(Point2D esqIzq, uint ancho, uint alto, Texture* points, Texture* arrows,PlayState*game)
	: GameObject(), esqIzq(esqIzq), ancho(ancho), alto(alto), points(points), arrows(arrows),game(game)
{
	digitos.push_back(0);

}

//metodo que controla los puntos
void Scoreboard::Puntuacion(int score)
{
	digitos.clear();

	int digito = 0;
	while (score > 9) {

		digitos.push_back(score % 10);

		score = score / 10;
	}
	digitos.push_back(score);


}
void Scoreboard::render() {

	SDL_Rect destRect;
	destRect.x = esqIzq.getX();
	destRect.y = esqIzq.getY();
	destRect.w = ancho;
	destRect.h = alto;
	for (int i = 0; i < digitos.size(); i++)
	{
		destRect.x -= 25;

		points->renderFrame(destRect, 0, digitos[i], 0, SDL_FLIP_NONE);
		
	}
	for (int i = 0; i < game->GetNumberArrows() ; i++)
	{

		destRect.x -= 25;

		arrows->render(destRect, SDL_FLIP_NONE);
	}

}





