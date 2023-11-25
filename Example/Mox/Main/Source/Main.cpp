#include "Game.h"
#include "Engine/LUX.h"

int main()
{
	LUX::Console console("Mox", 80, 40, false);

	MoxGame game(&console);

	game.Run();

	return 0;
}