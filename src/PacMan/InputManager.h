#pragma once
#include <SDL.h>
#include "../mtdl/mtdl.h"

class InputManager
{
public:
	mtdl::Vector2 mousePosition;
	bool mousePressed;
	bool escPressed;
	bool spacePressed;
	bool pPressed;
	bool wPressed;
	bool sPressed;
	bool aPressed;
	bool dPressed;
	bool upPressed;
	bool downPressed;
	bool leftPressed;
	bool rightPressed;
	bool quit;

	SDL_Event event;

	InputManager();
	~InputManager();

	void Update();
};
