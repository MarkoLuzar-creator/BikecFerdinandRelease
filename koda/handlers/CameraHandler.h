#pragma once

class CameraHandler
{
public:
	static CameraHandler &GetInstance();
	~CameraHandler();
	CameraHandler(CameraHandler const &) = delete;
	void operator=(CameraHandler const &) = delete;
	void SetScreenSize(int screenWidth, int screenHeight);
	void Update(int targetX, int targetY, int sizeX, int sizeY);
	void GetPosition(int &x, int &y);
private:
	CameraHandler() : x(0), y(0), screenWidth(1920), screenHeight(1080){}
	int x, y, screenWidth, screenHeight;
};

