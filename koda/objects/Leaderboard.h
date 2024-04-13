#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include "../handlers/TextureHandler.h"


class Leaderboard
{
public:
	Leaderboard(std::string fileName) : fileName(fileName){}
	void Insert(std::string name, int points);
	void Display(std::string font, int x, int y, int numberShown, int padding, int size, int r, int g, int b);
private:
	std::string fileName;
};

