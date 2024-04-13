#pragma once
#include <SDL.h>
#include <string>

class EventHandler
{
public:
	static EventHandler &GetInstance();
	~EventHandler();
	EventHandler(EventHandler const &) = delete;
	void operator=(EventHandler const &) = delete;
	void Listen();
	bool GetKeyDown(SDL_Scancode key);
	bool GetKeyPressed(SDL_Scancode key);
	void GetMousePosition(int &x, int &y);
	bool GetMousePressed(Uint32 button);
	void GetTextBuffer(std::string &text);
	void ClearTextBuffer();
private:
	EventHandler() : keyState(SDL_GetKeyboardState(nullptr)), lastKeyPressed(SDL_SCANCODE_UNKNOWN),
	mouseState(SDL_GetMouseState(nullptr, nullptr)), textBuffer(""), mouseX(0), mouseY(0), lastMousePressed(0){}
	const Uint8* keyState;
	Uint8 mouseState, lastMousePressed;
	SDL_Scancode lastKeyPressed;
	int mouseX, mouseY;
	std::string textBuffer;

};

