#include "Inky.h"

Inky::Inky()
{

}
Inky::Inky(mtdl::Vector2 pos, Tile** _map)
{
	map = _map;

	texture = "spritesheet";
	position = mtdl::Rect(pos.x, pos.y, SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE);

	// Time
	timer = ANIMATION_TIME;
	deltaTime = 0;
	lastTime = clock();

	// Animation
	key_frame = 0;
	animation = Animation::MOVE_RIGHT;
	breakAnimation = false;
	spritePosition = mtdl::Rect(2, 0, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);

	// Movement
	direction = mtdl::Vector2(0, 0);
	speed = 3;
}
Inky::~Inky()
{

}

void Inky::Draw()
{
	Renderer::Instance()->PushSprite(texture, spritePosition, position);
}
void Inky::Update(bool _up, bool _down, bool _left, bool _right)
{
	//Collision();
	MoveInky(_up, _down, _left, _right);
	Animate();
}

void Inky::MoveInky(bool _up, bool _down, bool _left, bool _right)
{
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

	// Update Last Direction
	lastDirection = animation;

	// Apply movement
	position.position.x += direction.x * speed;
	position.position.y += direction.y * speed;
}
void Inky::Animate()
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

CollisionSide Inky::Collision()
{
	int inkyCenterPixels = position.position.x + (position.w / 2);

	switch (lastDirection)
	{
	case Animation::MOVE_UP:
		tile = mtdl::Rect(map[inkyPositionOnGrid.x][inkyPositionOnGrid.y - 1].position * SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE);
		if (mtdl::RectRectCollision(position, tile)) return CollisionSide::TOP;


		if (inkyCenterPixels < tile.position.x + (tile.w / 2))
		{
			tile = mtdl::Rect(map[inkyPositionOnGrid.x - 1][inkyPositionOnGrid.y - 1].position * SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE);
			if (mtdl::RectRectCollision(position, tile)) return CollisionSide::TOP;
		}
		else if (inkyCenterPixels < tile.position.x + tile.w)
		{
			tile = mtdl::Rect(map[inkyPositionOnGrid.x + 1][inkyPositionOnGrid.y - 1].position * SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE);
			if (mtdl::RectRectCollision(position, tile)) return CollisionSide::TOP;
		}
		break;

	case Animation::MOVE_DOWN:
		tile = mtdl::Rect(map[inkyPositionOnGrid.x][inkyPositionOnGrid.y + 1].position * SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE);
		if (mtdl::RectRectCollision(position, tile)) return CollisionSide::BOTTOM;
		break;

	case Animation::MOVE_LEFT:
		tile = mtdl::Rect(map[inkyPositionOnGrid.x - 1][inkyPositionOnGrid.y].position * SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE);
		if (mtdl::RectRectCollision(position, tile)) return CollisionSide::LEFT;
		break;

	case Animation::MOVE_RIGHT:
		tile = mtdl::Rect(map[inkyPositionOnGrid.x + 1][inkyPositionOnGrid.y].position * SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE, SPRITE_PIXEL_SIZE);
		if (mtdl::RectRectCollision(position, tile)) return CollisionSide::RIGHT;
		break;
	}

	return CollisionSide::NONE;
}

