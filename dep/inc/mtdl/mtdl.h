#pragma once
#include <string>

namespace mtdl {

	/*---TYPES---*/
	#pragma region Types

	struct Vector2 {		//Vector 2D
		int x;
		int y;

		Vector2() {}
		Vector2(int _x, int _y) {
			x = _x;
			y = _y;
		}

		bool operator==(const Vector2 a)
		{
			return (x == a.x && y == a.y);
		}

		Vector2 operator*(const int e)
		{
			x *= e;
			y *= e;

			return Vector2(x, y);
		}
	};

	struct Rect {			//Rectangle
		Vector2 position;
		int w;
		int h;

		Rect() {}
		Rect(int _x, int _y, int _w, int _h) {
			position.x = _x;
			position.y = _y;
			w = _w;
			h = _h;
		}
		Rect(Vector2 r, int _w, int _h) {
			position.x = r.x;
			position.y = r.y;
			w = _w;
			h = _h;
		}
		Rect(int _x, int _y, Vector2 r) {
			position.x = _x;
			position.y = _y;
			w = r.x;
			h = r.y;
		}
		Rect(Vector2 e, Vector2 r) {
			position.x = e.x;
			position.y = e.y;
			w = r.x;
			h = r.y;
		}
	};

	struct Color			//Color
	{
		int r;
		int g;
		int b;
		int a;

		Color() {}
		Color(int _r, int _g, int _b, int _a) {
			r = _r;
			g = _g;
			b = _b;
			a = _a;
		}
	};

	struct Font				//Font
	{
		std::string path;
		int size;
		std::string id;

		Font() {}
		Font(std::string _path, int _size, std::string _id) {
			path = _path;
			size = _size;
			id = _id;
		}
	};

	struct Text				//Text
	{
		std::string text;
		Color color;
		std::string id;

		Text() {}
		Text(std::string _text, Color _color, std::string _id) {
			text = _text;
			color = _color;
			id = _id;
		}
	};

	struct PlayerRanking
	{
		std::string name;
		int score;

		PlayerRanking() {};
		PlayerRanking(std::string n, int s) {
			name = n;
			score = s;
		}
	};

	struct AudioFile
	{
		std::string name;
		std::string path;

		AudioFile(std::string n, std::string p) {
			name = n;
			path = p;
		}
	};
	#pragma endregion

	/*---FUNCTIONS---*/
	#pragma region Functions
	inline bool VectorRectCollision(mtdl::Vector2 v, mtdl::Rect r) {
		return (v.x >= r.position.x) && (v.x <= (r.position.x + r.w)) && (v.y >= r.position.y) && (v.y <= (r.position.y + r.h));
	}

	inline bool RectRectCollision(Rect r, Rect t) {
		Vector2 topRight(r.position.x + r.w, r.position.y);
		Vector2 botLeft(r.position.x, r.position.y + r.h);
		Vector2 botRight(r.position.x + r.w, r.position.y + r.h);
		return VectorRectCollision(r.position, t) || VectorRectCollision(topRight, t) || VectorRectCollision(botLeft, t) || VectorRectCollision(botRight, t);
	}

	inline bool RectRectHorizontalCollision(Rect r, Rect t) {
		Vector2 topRight(r.position.x + r.w, r.position.y);
		Vector2 botLeft(r.position.x, r.position.y + r.h);
		Vector2 botRight(r.position.x + r.w, r.position.y + r.h);
		return ((VectorRectCollision(topRight, t) || VectorRectCollision(r.position, t)) && !(VectorRectCollision(botLeft, t) || VectorRectCollision(botRight, t))) || (!(VectorRectCollision(topRight, t) || VectorRectCollision(r.position, t)) && (VectorRectCollision(botLeft, t) || VectorRectCollision(botRight, t)));
	}

	inline bool RectRectVerticalCollision(Rect r, Rect t) {
		Vector2 topRight(r.position.x + r.w, r.position.y);
		Vector2 botLeft(r.position.x, r.position.y + r.h);
		Vector2 botRight(r.position.x + r.w, r.position.y + r.h);
		return ((VectorRectCollision(topRight, t) || VectorRectCollision(botRight, t)) && !(VectorRectCollision(botLeft, t) || VectorRectCollision(r.position, t))) || (!(VectorRectCollision(topRight, t) || VectorRectCollision(botRight, t)) && (VectorRectCollision(botLeft, t) || VectorRectCollision(r.position, t)));
	}

	inline mtdl::Rect RotateRect90(Rect r) {
		mtdl::Rect t;
		t.position = r.position;
		t.w = r.h;
		t.h = r.w;
		return t;
	}
	#pragma endregion
}