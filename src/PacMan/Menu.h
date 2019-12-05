#pragma once
#include "Scene.h"
#include "Button.h"
#include <map>
#include <string>
#include "AudioManager.h"

class Menu :
	public Scene
{
private:
	std::unordered_map<std::string, Button*> buttons;
	bool soundOn;

public:
	Menu();
	~Menu();

	void Update(InputManager inputmanager);
	void Draw();
};

