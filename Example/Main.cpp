#include "Example.h"

int main()
{
	LUX::Console console("Example Game", 60, 30, false);

	ExampleGame game(&console);

	game.Run();

	return 0;
}