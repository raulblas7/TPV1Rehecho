#include <iostream>
#include "checkML.h"
#include "SDLApplication.h"

using namespace std;

int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	SDLApplication* a = new SDLApplication();
	delete a;
	a = nullptr;
	return 0;
}