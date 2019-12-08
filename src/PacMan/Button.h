#pragma once
#include "Renderer.h"
#include "../../dep/inc/mtdl/mtdl.h"

enum class ButtonAlignment {CENTER_CENTER};

class Button
{
private:
	std::string texture;
	std::string hoverTexture;
	mtdl::Rect rect;
	std::string textFont;
	mtdl::Color c_normal, c_hovered;
	bool isHover, isCentered;
	mtdl::Vector2 position;

public:
	Button();
	~Button();
	Button(std::string text, mtdl::Vector2 pos, mtdl::Color normal, mtdl::Color hovered, std::string font);
	Button(std::string text, mtdl::Vector2 pos, mtdl::Color normal, mtdl::Color hovered, std::string font, bool center);
	void Update(mtdl::Vector2 mousePosition);
	bool isPressed(mtdl::Vector2 mousePosition, bool p);
	void Draw();
	void UpdateText(std::string newText);
};

