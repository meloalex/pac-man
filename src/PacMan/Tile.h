#pragma once
#include "../mtdl/mtdl.h"

enum class TileType { NORMAL, WALL, ENEMY, PLAYER, POWERUP };

struct Tile
{
	mtdl::Vector2 position;
	TileType type;

	Tile() {}
	Tile(mtdl::Vector2 _position, TileType _type)
	{
		position = _position;
		type = _type;
	}
};