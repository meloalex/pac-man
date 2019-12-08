#include "Player.h"

Player::Player()
{

}

Player::Player(mtdl::Vector2 pos, Tile** _map)
{
	map = _map;

	texture = "spritesheet";
	playerPositionOnGrid = mtdl::Vector2(pos.x, pos.y);
	position = mtdl::Rect(pos * SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE);

	// Time
	timer = ANIMATION_TIME;
	deltaTime = 0;
	lastTime = clock();

	// Animation
	key_frame = 0;
	animation = Animation::MOVE_RIGHT;
	breakAnimation = false;
	spritePosition = mtdl::Rect(0, 0, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);

	// Movement
	direction = mtdl::Vector2(0, 0);
	speed = 1;
}


Player::~Player()
{

}

void Player::Update(bool _up, bool _down, bool _left, bool _right)
{
	Move(_up, _down, _left, _right);
	Animate();
}

void Player::Draw()
{
	Renderer::Instance()->PushSprite(texture, spritePosition, position);
	// Renderer::Instance()->PushImage("debug", tile);
}

void Player::Move(bool _up, bool _down, bool _left, bool _right)
{
	lastPlayerPositionOnGrid = mtdl::Vector2(round((position.position.x + (position.w / 2)) / SPRITE_PIXEL_SIZE), round((position.position.y + (position.h / 2))/ SPRITE_PIXEL_SIZE));

	// Asign vector movement and animation
	if (_up)
	{
		lastDirection != Animation::MOVE_UP ? breakAnimation = true : breakAnimation = false;

		direction = mtdl::Vector2(0, -1);
		animation = Animation::MOVE_UP;
	}
	else if (_down)
	{
		lastDirection != Animation::MOVE_DOWN ? breakAnimation = true : breakAnimation = false;

		direction = mtdl::Vector2(0, 1);
		animation = Animation::MOVE_DOWN;
	}
	else if (_left)
	{
		lastDirection != Animation::MOVE_LEFT ? breakAnimation = true : breakAnimation = false;

		direction = mtdl::Vector2(-1, 0);
		animation = Animation::MOVE_LEFT;
	} 
	else if (_right)
	{
		lastDirection != Animation::MOVE_RIGHT ? breakAnimation = true : breakAnimation = false;

		direction = mtdl::Vector2(1, 0);
		animation = Animation::MOVE_RIGHT;
	}
	
	// Check if still can move
	switch (animation)
	{
	case Animation::MOVE_UP:
		if (Collision() == CollisionSide::TOP) return;
		break;
	case Animation::MOVE_DOWN:
		if (Collision() == CollisionSide::BOTTOM) return;
		break;
	case Animation::MOVE_LEFT:
		if (Collision() == CollisionSide::LEFT) return;
		break;
	case Animation::MOVE_RIGHT:
		if (Collision() == CollisionSide::RIGHT) return;
		break;
	}

	// Update Last Direction
	lastDirection = animation;

	// Apply movement
	position.position.x += direction.x * speed;
	position.position.y += direction.y * speed;

	// Update player's position on grid
	map[lastPlayerPositionOnGrid.x][lastPlayerPositionOnGrid.y].type = TileType::NORMAL;	// Erase last position
	playerPositionOnGrid = mtdl::Vector2(round((position.position.x + (position.w / 2)) / SPRITE_PIXEL_SIZE), round((position.position.y + (position.h / 2)) / SPRITE_PIXEL_SIZE));	// Calculate new position on grid
	map[playerPositionOnGrid.x][playerPositionOnGrid.y].type = TileType::PLAYER;	// Update position on grid
}

void Player::Animate()
{
	// Time
	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
	timer -= deltaTime;

	if (timer < 0.0 || breakAnimation)
	{
		timer = ANIMATION_TIME;
		deltaTime = 0;
		lastTime = clock();

		if (breakAnimation) key_frame = 0;	// Start animation

		switch (animation)
		{
		case Animation::MOVE_UP:

			if (key_frame == 1 || lastDirection != Animation::MOVE_UP)
			{
				spritePosition.position.x = 0;
				key_frame = 0;
			}
			else if (key_frame == 0) {
				spritePosition.position.x = SPRITESHEET_RECT_SIZE * 1;
				key_frame++;
			}
			break;

		case Animation::MOVE_DOWN:
			
			if (key_frame == 1 || lastDirection != Animation::MOVE_DOWN)
			{
				spritePosition.position.x = SPRITESHEET_RECT_SIZE * 2;
				key_frame = 0;
			}
			else if (key_frame == 0) {
				spritePosition.position.x = SPRITESHEET_RECT_SIZE * 3;
				key_frame++;
			}
			break;

		case Animation::MOVE_LEFT:
			if (key_frame == 1 || lastDirection != Animation::MOVE_LEFT)
			{
				spritePosition.position.x = SPRITESHEET_RECT_SIZE * 6;
				key_frame = 0;
			}
			else if (key_frame == 0) {
				spritePosition.position.x = SPRITESHEET_RECT_SIZE * 7;
				key_frame++;
			}
			break;

		case Animation::MOVE_RIGHT:
			if (key_frame == 1 || lastDirection != Animation::MOVE_RIGHT)
			{
				spritePosition.position.x = SPRITESHEET_RECT_SIZE * 4;
				key_frame = 0;
			}
			else if (key_frame == 0) {
				spritePosition.position.x = SPRITESHEET_RECT_SIZE * 5;
				key_frame++;
			}
			break;

		case Animation::DIE:
			if (key_frame == 0)
			{
				spritePosition.position.x = SPRITESHEET_RECT_SIZE * 4;
				spritePosition.position.y = SPRITESHEET_RECT_SIZE * 4;
			}
			else if (key_frame < 4)
			{
				spritePosition.position.x += SPRITESHEET_RECT_SIZE;
			}
			else if (key_frame < 12)
			{
				spritePosition.position.x = SPRITESHEET_RECT_SIZE * key_frame - DIE_ANIMATION_OFFSET;
				spritePosition.position.y = SPRITESHEET_RECT_SIZE * 5;
			}

			key_frame++;
			break;

		default:
			break;
		}
	}
}

CollisionSide Player::Collision()
{
	int playerCenterPixels = position.position.x + (position.w / 2);

	switch (lastDirection)
	{
	case Animation::MOVE_UP:
		tile = mtdl::Rect(map[playerPositionOnGrid.x][playerPositionOnGrid.y - 1].position * SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE);
		if (mtdl::RectRectCollision(position, tile)) return CollisionSide::TOP;

		
		if (playerCenterPixels < tile.position.x + (tile.w / 2))
		{
			tile = mtdl::Rect(map[playerPositionOnGrid.x - 1][playerPositionOnGrid.y - 1].position * SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE);
			if (mtdl::RectRectCollision(position, tile)) return CollisionSide::TOP;
		}
		else if (playerCenterPixels < tile.position.x + tile.w)
		{
			tile = mtdl::Rect(map[playerPositionOnGrid.x + 1][playerPositionOnGrid.y - 1].position * SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE);
			if (mtdl::RectRectCollision(position, tile)) return CollisionSide::TOP;
		}
		break;

	case Animation::MOVE_DOWN:
		tile = mtdl::Rect(map[playerPositionOnGrid.x][playerPositionOnGrid.y + 1].position * SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE);
		if (mtdl::RectRectCollision(position, tile)) return CollisionSide::BOTTOM;
		break;

	case Animation::MOVE_LEFT:
		tile = mtdl::Rect(map[playerPositionOnGrid.x - 1][playerPositionOnGrid.y].position * SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE);
		if (mtdl::RectRectCollision(position, tile)) return CollisionSide::LEFT;
		break;

	case Animation::MOVE_RIGHT:
		tile = mtdl::Rect(map[playerPositionOnGrid.x + 1][playerPositionOnGrid.y].position * SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE);
		if (mtdl::RectRectCollision(position, tile)) return CollisionSide::RIGHT;
		break;
	}

	return CollisionSide::NONE;
}