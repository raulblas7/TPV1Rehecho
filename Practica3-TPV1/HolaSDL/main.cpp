#include <iostream>
#include "checkML.h"
#include "Game.h"

using namespace std;

int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game* g = new Game();
	/*delete g;
	g = nullptr;*/
	return 0;
}