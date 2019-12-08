#pragma once
#include "InputManager.h"
#include "Renderer.h"
#include "../../dep/inc/mtdl/mtdl.h"

enum class SceneState { RUNNING, PAUSED, GOTO_MENU, GOTO_GAMEPLAY, GOTO_RANKING, EXIT };

class Scene
{
protected:
	std::string backgroundTexture;
	mtdl::Rect backgroundRect;
	
public:
	Scene();
	~Scene();

	SceneState state;

	virtual void Update(InputManager inputManager) = 0;
	virtual void Draw() = 0;
};
