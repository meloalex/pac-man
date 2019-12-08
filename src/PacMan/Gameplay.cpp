#include "Gameplay.h"

Gameplay::Gameplay()
{
	internalState = GameplayState::GAME_START;

	texture = "spritesheet";

	wallSprite = mtdl::Rect(SPRITESHEET_RECT_SIZE * 4, SPRITESHEET_RECT_SIZE * 6, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);

	LoadMap();

	player = Player(initialPlayerPosition * SPRITE_PIXEL_SIZE);
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
		Collision();
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

	for (int i = 0; i < map.size(); i++)
	{
		Renderer::Instance()->PushSprite(texture, wallSprite, mtdl::Rect(map[i].position.x * SPRITE_PIXEL_SIZE, map[i].position.y * SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE));
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
			{
				map.push_back(Tile(mtdl::Vector2(x, y), TileType::PLAYER));
				initialPlayerPosition = mtdl::Vector2(x, y);
			}
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

			map.push_back(Tile(mtdl::Vector2(x, y), TileType::WALL));
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void Gameplay::Collision()
{
	// Player collision
	mtdl::Vector2 playerActualPos;
	mtdl::Vector2 playerNextPos;
	for (int pos = 0; pos < map.size(); pos++)
	{
		if (map[pos].type == TileType::PLAYER)
		{
			playerActualPos = mtdl::Vector2(map[pos].position.x, map[pos].position.y);
			playerNextPos = mtdl::Vector2(playerActualPos.x + player.GetDirection().x, playerActualPos.y - player.GetDirection().y);  //---tindre en compte la x,y del sdl

			for (int pos2 = 0; pos2 < map.size(); pos2++) {

				if(map[pos2].position.x ==  playerNextPos.x && map[pos2].position.y == playerNextPos.y) ////-------AQUI 
				{
					if (map[pos2].type == TileType::WALL)
					{
						player.SetDirection(0, 0);
						break;
					}
					//if (map[pos2].type == TileType::ENEMY)// Add player with and without powerUp state 
					//{
					//	lives--;
					//	if (lives == 0) player.SetAnimation(Animation::DIE);
					//	
					//}
					//if (map[pos2].type == TileType::POWERUP)// Add player powerUp state
					//	//player.animation = Animation::POWERUP
					
					break;
				}
				
			}
		}
	}

}

//sprite_pixel_size

void Gameplay::Collision(InputManager inputManager)
{
	// Player collision
	mtdl::Vector2 playerActualPos;
	mtdl::Vector2 playerNextPos;
	for (int pos = 0; pos < map.size(); pos++)
	{
		if (map[pos].type == TileType::PLAYER)
		{
			playerActualPos = mtdl::Vector2(map[pos].position.x, map[pos].position.y);
			playerNextPos = mtdl::Vector2(playerActualPos.x + player.GetDirection().x, playerActualPos.y - player.GetDirection().y);  //---tindre en compte la x,y del sdl
			break;
		}
	}
	for (int pos = 0; pos < map.size(); pos++)
	{
		if (map[pos].type == TileType::WALL && map[pos].position.x == playerNextPos.x && map[pos].position.y == playerNextPos.y)
		{
			
			player.SetDirection(0, 0);
			inputManager.downPressed = inputManager.upPressed = inputManager.rightPressed = inputManager.leftPressed = false;
			break;
		}
	}

}
