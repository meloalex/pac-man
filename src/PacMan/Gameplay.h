#pragma once
#include "Scene.h"
#include "Renderer.h"

#include "../../dep/inc/xml/rapidxml.hpp"
#include "../../dep/inc/xml/rapidxml_iterators.hpp"
#include "../../dep/inc/xml/rapidxml_print.hpp"
#include "../../dep/inc/xml/rapidxml_utils.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "Player.h"
#include "HUD.h"
#include "Button.h"
#include "AudioManager.h"
#include "Tile.h"

#define CONFIG_FILE_PATH "../../res/files/config.xml"

enum class GameplayState {GAME_START, RUNNING, PAUSED, GAME_OVER};

class Gameplay :
	public Scene
{
private:
	GameplayState internalState;

	// UI
	HUD hud;
	std::unordered_map<std::string, Button*> buttons;
	std::unordered_map<std::string, mtdl::Rect> texts;

	// Gameplay
	Player player;
	Tile** map;
	int xMapSize, yMapSize;

	mtdl::Vector2 initialPlayerPosition;
	mtdl::Vector2 initialBlinkyPosition;
	mtdl::Vector2 initialInkyPosition;
	mtdl::Vector2 initialClykePosition;

	std::vector<mtdl::Vector2> powerUpsPositions;

	mtdl::Rect wallSprite;
	std::string texture;
public:
	int score = 0;
	int lives = 3;

	Gameplay();
	~Gameplay();

	void Update(InputManager inputManager);
	void Draw();

	void LoadMap();
};

