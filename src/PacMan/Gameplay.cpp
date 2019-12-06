#include "Gameplay.h"

Gameplay::Gameplay()
{
	texture = "spritesheet";

	wallSprite = mtdl::Rect(SPRITESHEET_RECT_SIZE * 4, SPRITESHEET_RECT_SIZE * 6, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);

	LoadMap();

	player = Player(initialPlayerPosition * SPRITE_PIXEL_SIZE);
	hud = HUD();
}


Gameplay::~Gameplay()
{
}

void Gameplay::Update(InputManager inputManager)
{
	player.Update(inputManager.upPressed, inputManager.downPressed, inputManager.leftPressed, inputManager.rightPressed);
	hud.Update(score, lives);
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

			map.push_back(Tile(mtdl::Vector2(x, y), TileType::WALL));
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}