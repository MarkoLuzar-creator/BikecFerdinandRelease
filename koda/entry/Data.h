#pragma once
#include <string>
const std::string DATA_PATH = "data/Config.bin";

struct GameConfig
{
	struct UserConfig
	{
		int screen_width = 1920, screen_height = 1080;
	} user_config;
	struct Values
	{
		int player_position_x = 1920 / 2, player_position_y = 1920 / 2;
		int level = 0, points = 0, hp = 100, arena1_count = 10, arena2_count = 15;
		std::string player_name = "Krneki";
		int leaderboard_insert = false;
	} values;
};

class Data
{
public:
	static Data &GetInstance();
	void Read();
	void Write();
	GameConfig& GetData();
private:
	GameConfig data;
};

