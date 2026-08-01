#include <iostream.h>

#include "engine\engine.h"
#include "game\st_game.h"

// #include "test\testtype.h"

int main() {
//	TestTypes();

	Engine engine;
  StateGame gameState;

  engine.Init();
  engine.SetGameState(&gameState);
  while (engine.Run() != 0);
  engine.Shutdown();

	return 0;
}