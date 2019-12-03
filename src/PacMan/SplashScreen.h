#pragma once
#include "Scene.h"
#include <time.h>
#include <iostream>

class SplashScreen :
	public Scene
{
private: 
	float timer;
	clock_t lastTime;
	float deltaTime;

public:
	SplashScreen();
	~SplashScreen();
	void Update(InputManager inputmanager);
	void Draw();
};

