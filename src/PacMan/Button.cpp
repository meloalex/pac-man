#include "Button.h"

Button::Button()
{
}


Button::~Button()
{

}

Button::Button(std::string text, mtdl::Vector2 pos, mtdl::Color normal, mtdl::Color hovered, std::string font)
{
	// Load Text Textures
	Renderer::Instance()->LoadTextureText(font, mtdl::Text(text, normal, text + "_button"));
	Renderer::Instance()->LoadTextureText(font, mtdl::Text(text, hovered, text + "_button_hover"));

	texture = text + "_button";
	hoverTexture = text + "_button_hover";

	// Create Rectangle
	mtdl::Vector2 textureSize = Renderer::Instance()->GetTextureSize(text + "_button");
	rect = mtdl::Rect(position, textureSize);

	isHover = false;
}

Button::Button(std::string text, mtdl::Vector2 pos, mtdl::Color normal, mtdl::Color hovered, std::string font, bool center)
{
	// Save Data
	textFont = font;
	c_normal = normal;
	c_hovered = hovered;
	isCentered = center;
	position = pos;

	// Load Text Textures
	Renderer::Instance()->LoadTextureText(font, mtdl::Text(text, normal, text + "_button"));
	Renderer::Instance()->LoadTextureText(font, mtdl::Text(text, hovered, text + "_button_hover"));

	texture = text + "_button";
	hoverTexture = text + "_button_hover";

	// Create Rectangle
	mtdl::Vector2 textureSize = Renderer::Instance()->GetTextureSize(text + "_button");
	if (isCentered) rect = mtdl::Rect(mtdl::Vector2(SCREEN_WIDTH / 2 - textureSize.x / 2, position.y), textureSize);
	else rect = mtdl::Rect(position, textureSize);

	isHover = false;
}

void Button::Update(mtdl::Vector2 mousePosition)
{
	if (mtdl::VectorRectCollision(mousePosition, rect)) isHover = true;
	else isHover = false;
}

void Button::Draw()
{
	if (isHover) Renderer::Instance()->PushImage(hoverTexture, rect);
	else Renderer::Instance()->PushImage(texture, rect);
}

bool Button::isPressed(mtdl::Vector2 mousePosition, bool p) {
	return mtdl::VectorRectCollision(mousePosition, rect) && p;
}

void Button::UpdateText(std::string newText)
{
	// Load Text Textures
	texture = newText + "_button";
	hoverTexture = newText + "_button_hover";

	Renderer::Instance()->LoadTextureText(textFont, mtdl::Text(newText, c_normal, texture));
	Renderer::Instance()->LoadTextureText(textFont, mtdl::Text(newText, c_hovered, hoverTexture));

	// Create Rectangle
	mtdl::Vector2 textureSize = Renderer::Instance()->GetTextureSize(texture);
	if (isCentered) rect = mtdl::Rect(mtdl::Vector2(SCREEN_WIDTH / 2 - textureSize.x / 2, position.y), textureSize);
	else rect = mtdl::Rect(position, textureSize);

	isHover = false;
}