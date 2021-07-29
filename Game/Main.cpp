#include "Game.h"

Game game;

bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	game.Update(dt);
	
	return quit;
}

void Draw(Core::Graphics& graphics)
{
	game.Draw(graphics);
}

int main()
{
	char name[] = "THIS IS A WINDOW";
	Core::Init(name, 800, 600, 120);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	game.Initialize();

	Core::GameLoop();
	Core::Shutdown();

	game.Shutdown();
}