#pragma once
#include "Renderer.h"
#include "../../dep/inc/mtdl/mtdl.h"

class HUD
{
private:
	mtdl::Rect HUDBackgroundSprite;
	mtdl::Rect HUDPosition;
	std::string texture;

	// Text
	mtdl::Rect scoreTextRect;

	// Lives
	mtdl::Rect livesPositions[3];
	mtdl::Rect livesSprite[3];

public:
	HUD();
	~HUD();

	void Update(int _score, int _lives);
	void Draw();
};

