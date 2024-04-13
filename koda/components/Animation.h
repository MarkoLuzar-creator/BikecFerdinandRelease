#pragma once

class Animation
{
public:
	Animation() : spriteRow(0), frameCount(0), animationSpeed(0), spriteFrame(0) {}
	void SetProperties(int row, int numberOffFrames, int speed);
	void Update();
	int GetFrame();
	int GetRow();
private:
	int spriteRow, spriteFrame, animationSpeed, frameCount;
};

