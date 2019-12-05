#pragma once
#include "Scene.h"
#include "Player.h"

class Gameplay :
	public Scene
{
private:
	Player player;

public:
	Gameplay();
	~Gameplay();

	void Update(InputManager inputManager);
	void Draw();
};

