#include "GameController.h"

GameController::GameController()
{
	gameRunning = true;
	gameState = GameState::SPLASH_SCREEN;
	currentScene = new SplashScreen();
}

GameController::~GameController()
{
	delete(currentScene);
}

void GameController::Update()
{
	if (inputManager.quit) gameState = GameState::EXIT;

	switch (gameState)
	{
	case GameState::SPLASH_SCREEN:
		
		break;
	case GameState::MENU:
		break;
	case GameState::GAMEPLAY:
		break;
	case GameState::RANKING:
		break;
	case GameState::EXIT:
		gameRunning = false;
		break;
	default:
		break;
	}

	inputManager.Update();
	currentScene->Update(inputManager);
	currentScene->Draw();
}