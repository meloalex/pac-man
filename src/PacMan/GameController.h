#pragma once
#include "InputManager.h"
#include "Scene.h"
#include "Menu.h"
#include "SplashScreen.h"
#include "Gameplay.h"

enum class GameState { SPLASH_SCREEN, MENU, GAMEPLAY, RANKING, EXIT };

class GameController
{
private:
	GameState gameState;
	InputManager inputManager;
	Scene* currentScene;

public:
	bool gameRunning;

	GameController();
	~GameController();
	void Update();
};
