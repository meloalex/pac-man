#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string.h>
#include <unordered_map>
#include "../../dep/inc/mtdl/mtdl.h"

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 700

#define SPRITESHEET_RECT_SIZE 128
#define SPRITE_PIXEL_SIZE 35
#define POSITION_TO_PIXEL_OFFSET 1

class Renderer {

private:
	SDL_Renderer *m_renderer = nullptr;
	SDL_Window *m_window = nullptr;
	std::unordered_map<std::string, SDL_Texture*> m_textureData;
	std::unordered_map<std::string, TTF_Font*> m_fontData;
	static Renderer *renderer;
	Renderer();

public:
	static Renderer *Instance()
	{
		if (renderer == nullptr) { renderer = new Renderer; }
		return renderer;
	};

	~Renderer();
	 void Clear()  ;
	 void Render() ;
	 void LoadFont(mtdl::Font font);
	 void LoadTexture(const std::string &id, const std::string &path);
	 void LoadTextureText(const std::string &fontId, mtdl::Text text);
	 mtdl::Vector2 GetTextureSize(const std::string &id);
	 void PushImage(const std::string &id,const mtdl::Rect &rect);
	 void PushSprite(const std::string &id,const mtdl::Rect &rectSprite,const mtdl::Rect &rectPos);
	 void PushRotatedSprite(const std::string &id, const mtdl::Rect &rectSprite, const mtdl::Rect &rectPos, float angle);
	 void SetRendreDrawColor(int r, int g, int b);	 
};


