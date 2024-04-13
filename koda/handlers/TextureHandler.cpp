#include "TextureHandler.h"

TextureHandler &TextureHandler::GetInstance()
{
	static TextureHandler instance;
	return instance;
}

TextureHandler::~TextureHandler()
{
	std::unordered_map<std::string, SDL_Texture *>::iterator it;
	for (it = textureMap.begin(); it != textureMap.end(); it++)
	{
		SDL_DestroyTexture(it->second);
	}
	textureMap.clear();
	SDL_DestroyRenderer(renderer);
}

void TextureHandler::SetRenderer(SDL_Renderer *&renderer, int screenWidth, int screenHeight)
{
	this->renderer = renderer;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}

void TextureHandler::LoadTexture(std::string path, std::string id)
{
	if (textureMap[id] == nullptr)
	{
		SDL_Surface *surface = IMG_Load(path.c_str());
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
		textureMap[id] = texture;
		SDL_FreeSurface(surface);
	}
}

void TextureHandler::DrawTexture(std::string id, int x, int y, int w, int h, SDL_RendererFlip flip, float size)
{
	SDL_Rect srcRect = { 0, 0, w, h };
	SDL_FRect destRect = { x, y, (w * size) / (1920.0f / screenWidth), (h * size) / (1080.0f / screenHeight) };
	SDL_RenderCopyExF(renderer, textureMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void TextureHandler::DrawAnimation(std::string id, int x, int y, int w, int h, int row, int frame, SDL_RendererFlip flip, float size)
{
	SDL_Rect srcRect = { w * frame, h * row, w, h };
	SDL_Rect destRect = { x, y, (w * size) / (1920.0f / screenWidth), (h * size) / (1080.0f / screenHeight) };
	SDL_RenderCopyEx(renderer, textureMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void TextureHandler::DrawText(std::string text, std::string font, int x, int y, int size, int r, int g, int b)
{
	TTF_Font *f;
	f = TTF_OpenFont(font.c_str(), size);
	SDL_Color c = { r, g, b };
	SDL_Surface *s = TTF_RenderText_Solid(f, text.c_str(), c);
	SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, s);
	int w, h;
	TTF_SizeText(f, text.c_str(), &w, &h);
	SDL_Rect srcRect = { 0, 0, w, h };
	SDL_FRect destRect = { x, y, w / (1920.0f / screenWidth), h / (1080.0f / screenHeight) };
	SDL_RenderCopyExF(renderer, tex, &srcRect, &destRect, 0, nullptr, SDL_FLIP_NONE);
	SDL_FreeSurface(s);
	SDL_DestroyTexture(tex);
	TTF_CloseFont(f);
}

void TextureHandler::GetTextSize(std::string text, std::string font, int size, int &w, int &h)
{
	TTF_Font *f;
	f = TTF_OpenFont(font.c_str(), size);
	TTF_SizeText(f, text.c_str(), &w, &h);
	TTF_CloseFont(f);
}

void TextureHandler::GetTextSizeScaled(std::string text, std::string font, int size, int &w, int &h)
{
	TTF_Font *f;
	f = TTF_OpenFont(font.c_str(), size);
	TTF_SizeText(f, text.c_str(), &w, &h);
	TTF_CloseFont(f);
	w /= (1920.0f / screenWidth);
	h /= (1080.0f / screenHeight);
}
