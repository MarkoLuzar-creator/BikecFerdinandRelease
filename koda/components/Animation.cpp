#include "Animation.h"
#include <SDL.h>


void Animation::SetProperties(int row, int numberOffFrames, int speed)
{
	spriteRow = row;
	frameCount = numberOffFrames;
	animationSpeed = speed;
}

void Animation::Update()
{
	spriteFrame = (SDL_GetTicks64() / animationSpeed) % frameCount;
}

int Animation::GetFrame()
{
	return spriteFrame;
}

int Animation::GetRow()
{
	return spriteRow;
}
