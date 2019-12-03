#include "GameController.h"

int main(int, char*[])
{
	GameController gameController;

	while (gameController.gameRunning)
		gameController.Update();

	return 0;
}