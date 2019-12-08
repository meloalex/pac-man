#pragma once
#include "Enemy.h"

class Clyde
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

	void MoveClyde(bool _up, bool _down, bool _left, bool _right); //Moves the oposite of the player
	void Animate();

	Clyde();
	Clyde(mtdl::Vector2 pos);
	~Clyde();
};