#include "Gameplay.h"

Gameplay::Gameplay()
{
	player = Player();
}


Gameplay::~Gameplay()
{
}

void Gameplay::Update(InputManager inputManager)
{
	player.Update(inputManager.upPressed, inputManager.downPressed, inputManager.leftPressed, inputManager.rightPressed);
}

void Gameplay::Draw()
{
	Renderer::Instance()->Clear();

	player.Draw();

	Renderer::Instance()->Render();
}
