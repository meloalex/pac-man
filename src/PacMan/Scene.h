#pragma once
#include "InputManager.h"
#include "Renderer.h"
#include "../mtdl/mtdl.h"

enum class SceneState { RUNNING, PAUSED, EXIT };

class Scene
{
protected:
	std::string backgroundTexture;
	mtdl::Rect backgroundRect;
	SceneState state;

public:
	Scene();
	~Scene();

	virtual void Update(InputManager inputManager) = 0;
	virtual void Draw() = 0;
};
