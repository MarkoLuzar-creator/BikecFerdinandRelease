#include "EventHandler.h"
#include <iostream>

EventHandler &EventHandler::GetInstance()
{
	static EventHandler instance;
	return instance;
}

EventHandler::~EventHandler()
{
    
}

void EventHandler::Listen()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN: SDL_GetKeyboardState(nullptr); if (event.key.keysym.sym == SDLK_BACKSPACE) { if (textBuffer != "")textBuffer.pop_back(); }; break;
        case SDL_KEYUP: SDL_GetKeyboardState(nullptr); break;
        case SDL_QUIT: exit(0); break;
        case SDL_TEXTINPUT: textBuffer += event.text.text; break;
        }
    }
    mouseState = SDL_GetMouseState(&mouseX, &mouseY);
}

bool EventHandler::GetKeyDown(SDL_Scancode key)
{
    return keyState[key] == 1;
}

bool EventHandler::GetKeyPressed(SDL_Scancode key)
{
    if (keyState[key] && lastKeyPressed != key)
    {
        lastKeyPressed = key;
        return true;
    }
    else if (!keyState[key] && lastKeyPressed == key)
    {
        lastKeyPressed = SDL_SCANCODE_UNKNOWN;
    }
    return false;
}

void EventHandler::GetMousePosition(int &x, int &y)
{
    x = mouseX;
    y = mouseY;
}

bool EventHandler::GetMousePressed(Uint32 button)
{
    if ((mouseState & SDL_BUTTON(button)) && (lastMousePressed != button))
    {
        lastMousePressed = button;
        return true;
    }
    else if (!(mouseState & SDL_BUTTON(button)) && (lastMousePressed == button))
    {
        lastMousePressed = 0;
    }
    return false;
}

void EventHandler::GetTextBuffer(std::string &text)
{
    text = textBuffer;
}

void EventHandler::ClearTextBuffer()
{
    textBuffer = "";
}
