#include "Gameplay.h"

Gameplay::Gameplay()
{
	internalState = GameplayState::GAME_START;

	texture = "spritesheet";

	wallSprite = mtdl::Rect(SPRITESHEET_RECT_SIZE * 4, SPRITESHEET_RECT_SIZE * 6, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);

	LoadMap();

	map[initialPlayerPosition.x][initialPlayerPosition.y].type = TileType::PLAYER;
	player = Player(initialPlayerPosition, map);
	hud = HUD();

	buttons["toggleSound"] = new Button("Sound ON", mtdl::Vector2(0, 300), mtdl::Color(0, 0, 0, 255), mtdl::Color(255, 0, 0, 255), "pacman38", true);
	
	Renderer::Instance()->LoadTextureText("pacman38", mtdl::Text("PRESS SPACE BAR", mtdl::Color(255, 255, 255, 255), "pressSpace"));
	texts["pressSpace"] = mtdl::Rect(SCREEN_WIDTH / 2 - Renderer::Instance()->GetTextureSize("pressSpace").x / 2, 250, Renderer::Instance()->GetTextureSize("pressSpace"));
	
	if (!AudioManager::Instance()->audioOn)
		buttons["toggleSound"]->UpdateText("Sound OFF");
}


Gameplay::~Gameplay()
{
}

void Gameplay::Update(InputManager inputManager)
{
	switch (internalState)
	{
	case GameplayState::GAME_START:
		if (inputManager.spacePressed) internalState = GameplayState::RUNNING;
		if (inputManager.escPressed) state = SceneState::GOTO_MENU;
		break;

	case GameplayState::RUNNING:
		if (inputManager.pPressed) internalState = GameplayState::PAUSED;
		player.Update(inputManager.upPressed, inputManager.downPressed, inputManager.leftPressed, inputManager.rightPressed);
		hud.Update(score, lives);
		break;

	case GameplayState::PAUSED:
		if (inputManager.spacePressed) internalState = GameplayState::RUNNING;
		if (inputManager.escPressed) state = SceneState::GOTO_MENU;

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
		break;

	case GameplayState::GAME_OVER:
		break;

	default:
		break;
	}
}

void Gameplay::Draw()
{
	Renderer::Instance()->Clear();

	for (int i = 0; i < xMapSize; i++)
	{
		for (int j = 0; j < yMapSize; j++)
			Renderer::Instance()->PushSprite(texture, wallSprite, mtdl::Rect(map[i][j].position.x * SPRITE_PIXEL_SIZE, map[i][j].position.y * SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE));
	}

	player.Draw();
	hud.Draw();

	switch (internalState)
	{
	case GameplayState::GAME_START:
		Renderer::Instance()->PushImage("pressSpace", texts["pressSpace"]);
		break;

	case GameplayState::RUNNING:
		break;

	case GameplayState::PAUSED:
		buttons["toggleSound"]->Draw();
		Renderer::Instance()->PushImage("pressSpace", texts["pressSpace"]);
		break;

	case GameplayState::GAME_OVER:
		break;

	default:
		break;
	}
	Renderer::Instance()->Render();
}

void Gameplay::LoadMap()
{
	try
	{
		rapidxml::xml_document<> doc;
		std::ifstream file(CONFIG_FILE_PATH);
		std::stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		std::string content(buffer.str());
		doc.parse<0>(&content[0]);

		rapidxml::xml_node<> *pRoot = doc.first_node();
		
		// Get Element position information
		rapidxml::xml_node<> *pPositions = pRoot->first_node("Positions");

		// Read map dimensions
		rapidxml::xml_attribute<> *pMapSize = pPositions->first_attribute();
		xMapSize = std::stoi(pMapSize->value());
		yMapSize = std::stoi(pMapSize->next_attribute()->value());

		// Allocate map memory
		map = new Tile* [xMapSize];
		for (int i = 0; i < xMapSize; i++)
			map[i] = new Tile[yMapSize];

		rapidxml::xml_node<> *pNode = pPositions->first_node();	// First node inside Positions

		for (rapidxml::xml_node<> *pNode = pPositions->first_node(); pNode; pNode = pNode->next_sibling())
		{
			std::string nodeName = pNode->name();
			rapidxml::xml_attribute<> *pAttribute;

			if (nodeName.compare("PowerUps") == 0)
			{
				for (rapidxml::xml_node<> *qNode = pNode->first_node(); qNode; qNode = qNode->next_sibling())
				{
					pAttribute = qNode->first_attribute();
					int x = std::stoi(pAttribute->value());
					int y = std::stoi(pAttribute->next_attribute()->value());

					powerUpsPositions.push_back(mtdl::Vector2(x - POSITION_TO_PIXEL_OFFSET, y - POSITION_TO_PIXEL_OFFSET));
				}
				break;
			}

			pAttribute = pNode->first_attribute();
			int x = std::stoi(pAttribute->value());
			int y = std::stoi(pAttribute->next_attribute()->value());

			x -= POSITION_TO_PIXEL_OFFSET;
			y -= POSITION_TO_PIXEL_OFFSET;

			if (nodeName.compare("Player") == 0)
				initialPlayerPosition = mtdl::Vector2(x, y);
			else if (nodeName.compare("Blinky") == 0)
				initialBlinkyPosition = mtdl::Vector2(x, y);
			else if (nodeName.compare("Inky") == 0)
				initialInkyPosition = mtdl::Vector2(x, y);
			else if (nodeName.compare("Clyke") == 0)
				initialClykePosition = mtdl::Vector2(x, y);
		}

		// Get Map information
		rapidxml::xml_node<> *pMap = pPositions->next_sibling();
		std::cout << pMap->name();

		for (rapidxml::xml_node<> *wNode = pMap->first_node(); wNode; wNode = wNode->next_sibling())
		{
			rapidxml::xml_attribute<> *pAttribute = wNode->first_attribute();

			int x = std::stoi(pAttribute->value());
			int y = std::stoi(pAttribute->next_attribute()->value());

			x -= POSITION_TO_PIXEL_OFFSET;
			y -= POSITION_TO_PIXEL_OFFSET;

			map[x][y] = Tile(mtdl::Vector2(x, y), TileType::WALL);
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}
