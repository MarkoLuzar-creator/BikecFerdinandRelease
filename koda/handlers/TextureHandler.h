#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <unordered_map>

class TextureHandler
{
public:
	static TextureHandler &GetInstance();
	~TextureHandler();
	TextureHandler(TextureHandler const&) = delete;
    void operator=(TextureHandler const&) = delete;
	void SetRenderer(SDL_Renderer *&renderer, int screenWidth, int screenHeight);
	void LoadTexture(std::string path, std::string id);
	void DrawTexture(std::string id, int x, int y, int w, int h, SDL_RendererFlip flip, float size);
	void DrawAnimation(std::string id, int x, int y, int w, int h, int row, int frame, SDL_RendererFlip flip, float size);
	void DrawText(std::string text, std::string font, int x, int y, int size, int r, int g, int b);
	void GetTextSize(std::string text, std::string font, int size, int &w, int &h);
	void GetTextSizeScaled(std::string text, std::string font, int size, int &w, int &h);
private:
	TextureHandler() : renderer(nullptr), id(""), screenWidth(1920), screenHeight(1080) {}
	std::unordered_map<std::string, SDL_Texture *> textureMap;
	SDL_Renderer *renderer;
	std::string id;
	int screenWidth, screenHeight;
};

