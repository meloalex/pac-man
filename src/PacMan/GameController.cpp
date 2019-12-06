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
		if (currentScene->state == SceneState::GOTO_MENU)
		{
			gameState = GameState::MENU;
			delete(currentScene);
			currentScene = new Menu();
		}
		break;

	case GameState::MENU:

		switch (currentScene->state)
		{
		case SceneState::GOTO_GAMEPLAY:
			gameState = GameState::GAMEPLAY;
			delete(currentScene);
			currentScene = new Gameplay();
			break;

		case SceneState::EXIT:
			gameState = GameState::EXIT;
			break;
		default:
			break;
		}

		break;
	case GameState::GAMEPLAY:
		switch (currentScene->state)
		{
		case SceneState::GOTO_MENU:
			gameState = GameState::MENU;
			delete(currentScene);
			currentScene = new Menu();
			break;

		default:
			break;
		}
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