#pragma once
#include "Renderer.h"
#include "../mtdl/mtdl.h"
#include <time.h>
#include <iostream>
#include <vector>

#define ANIMATION_TIME 0.3
#define MOVEMENT_ANIMATION_KEYFRAMES 2
#define DIE_ANIMATION_KEYFRAMES 12
#define DIE_ANIMATION_OFFSET 4

enum class Animation {MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, DIE};

class Player
{
private:
	mtdl::Vector2 direction;
	int speed;

	// Animation
	Animation animation, lastDirection;
	int key_frame;
	std::string texture;
	mtdl::Rect position;
	mtdl::Rect spritePosition;
	bool breakAnimation;

	// Time
	float timer;
	clock_t lastTime;
	float deltaTime;

public:
	Player();
	Player(mtdl::Vector2 pos);
	~Player();

	void Update(bool _up, bool _down, bool _left, bool _right);
	void Draw();

	void Animate();
	void Move(bool _up, bool _down, bool _left, bool _right);
	void Collision();
};

