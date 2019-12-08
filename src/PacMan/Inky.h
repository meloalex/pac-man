#pragma once
#include "Enemy.h"


class Inky
	:public Enemy
{
public:
	mtdl::Rect position;
	std::string texture;
	mtdl::Rect myRect;
	EnemyType type;
	int speed;
	int reward;

	void Draw();
	void Update(bool _up, bool _down, bool _left, bool _right);

	void MoveInky(bool _up, bool _down, bool _left, bool _right); //Moves like the player
	void Animate();

	Inky();
	Inky(mtdl::Vector2 pos);
	~Inky();
};