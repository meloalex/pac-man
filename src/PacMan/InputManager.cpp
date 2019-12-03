#include "InputManager.h"
#include <iostream>

InputManager::InputManager()
{
	mousePosition.x = 0;
	mousePosition.y = 0;
	mousePressed = false;
	escPressed = false;
	spacePressed = false;
	wPressed = false;
	sPressed = false;
	upPressed = false;
	downPressed = false;
	quit = false;
}

InputManager::~InputManager()
{

}

void InputManager::Update()
{
	if (event.key.keysym.sym == SDLK_ESCAPE) escPressed = false;
	if (event.key.keysym.sym == SDLK_SPACE) spacePressed = false;
	if (event.key.keysym.sym == SDLK_p) pPressed = false;
	mousePressed = false;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			mousePressed = true;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) escPressed = true;
			if (event.key.keysym.sym == SDLK_SPACE) spacePressed = true;
			if (event.key.keysym.sym == SDLK_p) pPressed = true;
			if (event.key.keysym.sym == SDLK_w) wPressed = true;
			if (event.key.keysym.sym == SDLK_s) sPressed = true;
			if (event.key.keysym.sym == SDLK_UP) upPressed = true;
			if (event.key.keysym.sym == SDLK_DOWN) downPressed = true;
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_w) wPressed = false;
			if (event.key.keysym.sym == SDLK_s) sPressed = false;
			if (event.key.keysym.sym == SDLK_UP) upPressed = false;
			if (event.key.keysym.sym == SDLK_DOWN) downPressed = false;
			break;
		case SDL_MOUSEMOTION:
			mousePosition.x = event.motion.x;
			mousePosition.y = event.motion.y;
			break;
		default:
			break;
		}
	}
}