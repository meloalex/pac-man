#include "HUD.h"


HUD::HUD()
{
	texture = "spritesheet";

	// HUD Background
	HUDBackgroundSprite = mtdl::Rect(SPRITESHEET_RECT_SIZE * 7, SPRITESHEET_RECT_SIZE * 6, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
	HUDPosition = mtdl::Rect(SCREEN_WIDTH - 200, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// Lives
	livesPositions[0] = mtdl::Rect(SCREEN_WIDTH - 160, SCREEN_HEIGHT - 200, 50, 50);
	livesPositions[1] = mtdl::Rect(SCREEN_WIDTH - 120, SCREEN_HEIGHT - 200, 50, 50);
	livesPositions[2] = mtdl::Rect(SCREEN_WIDTH - 80, SCREEN_HEIGHT - 200, 50, 50);

	livesSprite[0] = mtdl::Rect(SPRITESHEET_RECT_SIZE * 6, 0, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
	livesSprite[1] = mtdl::Rect(SPRITESHEET_RECT_SIZE * 6, 0, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
	livesSprite[2] = mtdl::Rect(SPRITESHEET_RECT_SIZE * 6, 0, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
}


HUD::~HUD()
{
}

void HUD::Update(int _score, int _lives)
{
	// Score
	std::string score = std::to_string(_score);
	Renderer::Instance()->LoadTextureText("gameplay24", mtdl::Text(score, mtdl::Color(0, 0, 0, 255), "score"));
	scoreTextRect = mtdl::Rect(SCREEN_WIDTH - 100, 200, Renderer::Instance()->GetTextureSize("score"));

	// Lives
	switch (_lives)
	{
	case 0: livesSprite[2] = mtdl::Rect(SPRITESHEET_RECT_SIZE * 3, SPRITESHEET_RECT_SIZE * 6, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);

	case 1: livesSprite[1] = mtdl::Rect(SPRITESHEET_RECT_SIZE * 3, SPRITESHEET_RECT_SIZE * 6, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
	
	case 2: livesSprite[0] = mtdl::Rect(SPRITESHEET_RECT_SIZE * 3, SPRITESHEET_RECT_SIZE * 6, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);

	default:
		break;
	}
	
}

void HUD::Draw()
{
	// HUD Background
	Renderer::Instance()->PushSprite(texture, HUDBackgroundSprite, HUDPosition);

	// Lives
	Renderer::Instance()->PushSprite(texture, livesSprite[0], livesPositions[0]);
	Renderer::Instance()->PushSprite(texture, livesSprite[1], livesPositions[1]);
	Renderer::Instance()->PushSprite(texture, livesSprite[2], livesPositions[2]);

	// Score
	Renderer::Instance()->PushImage("score", scoreTextRect);
}