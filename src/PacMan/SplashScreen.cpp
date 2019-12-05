#include "SplashScreen.h"



SplashScreen::SplashScreen()
{
	backgroundTexture = "backgroundSplashScreen";
	backgroundRect = mtdl::Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// Time settings
	timer = 3;
	deltaTime = 0;
	lastTime = clock();
}


SplashScreen::~SplashScreen()
{
	
}

void SplashScreen::Update(InputManager inputManager)
{
	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
	timer -= deltaTime;

	if (timer < 0.0)
		state = SceneState::GOTO_MENU;
}

void SplashScreen::Draw()
{
	Renderer::Instance()->Clear();
	Renderer::Instance()->PushImage(backgroundTexture, backgroundRect);
	Renderer::Instance()->Render();
}