#include "TimeHandler.h"

TimeHandler &TimeHandler::GetInstance()
{
	static TimeHandler instance;
	return instance;
}

TimeHandler::~TimeHandler()
{
}

void TimeHandler::Tick()
{
	deltaTime = (SDL_GetTicks() - lastTime) * (144 / 1000.0f);
	lastTime = SDL_GetTicks();
}

float TimeHandler::GetDeltaTime()
{
	return deltaTime;
}
