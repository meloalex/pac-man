#include "Menu.h"

Menu::Menu()
{
	// Buttons
	buttons["play"] = new Button("Play", mtdl::Vector2(0, 100), mtdl::Color(0, 0, 0, 255), mtdl::Color(255, 0, 0, 255), "pacman38", true);
	buttons["ranking"] = new Button("Ranking", mtdl::Vector2(0, 200), mtdl::Color(0, 0, 0, 255), mtdl::Color(255, 0, 0, 255), "pacman38", true);
	buttons["exit"] = new Button("Exit", mtdl::Vector2(0, 400), mtdl::Color(0, 0, 0, 255), mtdl::Color(255, 0, 0, 255), "pacman38", true);
	buttons["toggleSound"] = new Button("Sound ON", mtdl::Vector2(0, 300), mtdl::Color(0, 0, 0, 255), mtdl::Color(255, 0, 0, 255), "pacman38", true);

	// Audio
	if (!AudioManager::Instance()->audioStarted) {
		AudioManager::Instance()->StartAudio("main_theme", 50, -1);
		AudioManager::Instance()->audioStarted = true;
	}

	if (!AudioManager::Instance()->audioOn)
		buttons["toggleSound"]->UpdateText("Sound OFF");
}


Menu::~Menu()
{
	for (std::pair<std::string, Button*> pair : buttons)
		delete(pair.second);
}

void Menu::Update(InputManager inputManager)
{
	//Update buttons
	for (std::pair<std::string, Button*> pair : buttons)
		pair.second->Update(inputManager.mousePosition);

	if (buttons["exit"]->isPressed(inputManager.mousePosition, inputManager.mousePressed))
		state = SceneState::EXIT;
		
	if (buttons["play"]->isPressed(inputManager.mousePosition, inputManager.mousePressed))
		state = SceneState::GOTO_GAMEPLAY;

	if (buttons["toggleSound"]->isPressed(inputManager.mousePosition, inputManager.mousePressed) && AudioManager::Instance()->audioOn)
	{
		buttons["toggleSound"]->UpdateText("Sound Off");
		AudioManager::Instance()->PauseAudio();
	}
	else if (buttons["toggleSound"]->isPressed(inputManager.mousePosition, inputManager.mousePressed))
	{
		buttons["toggleSound"]->UpdateText("Sound On");
		AudioManager::Instance()->ResumeAudio();
	}

}

void Menu::Draw()
{
	Renderer::Instance()->Clear();

	//Draw each button
	for (std::pair<std::string, Button*> pair : buttons)
		pair.second->Draw();

	Renderer::Instance()->Render();
}