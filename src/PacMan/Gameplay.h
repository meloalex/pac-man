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

#define CONFIG_FILE_PATH "../../res/files/config.xml"

enum class TileType {NORMAL, WALL, ENEMY, PLAYER, POWERUP};

enum class GameplayState {GAME_START, RUNNING, PAUSED, GAME_OVER};

struct Tile
{
	mtdl::Vector2 position;
	TileType type;

	Tile() {}
	Tile(mtdl::Vector2 _position, TileType _type)
	{
		position = _position;
		type = _type;
	}
};

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
	std::vector<Tile> map;
	
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

