#pragma once
#include <SDL.h>

class TimeHandler{
public:
	static TimeHandler &GetInstance();
	~TimeHandler();
	TimeHandler(TimeHandler const &) = delete;
	void operator=(TimeHandler const &) = delete;
	void Tick();
	float GetDeltaTime();
private:
	TimeHandler() : deltaTime(0), lastTime(0){}
	float deltaTime;
	float lastTime;
};

