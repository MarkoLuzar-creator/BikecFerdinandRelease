#pragma once
#include "../objects/Leaderboard.h"
#include "../objects/Player.h"
#include "../objects/Farm.h"
#include "../objects/Enemy.h"
#include "../objects/StaticButton.h"
#include "../objects/DynamicButton.h"
#include "../objects/Door.h"
#include "../objects/Arena.h"
#include "../objects/Bikec.h"

#include "../handlers/TimeHandler.h"
#include "../handlers/TextureHandler.h"
#include "../handlers/CameraHandler.h"
#include "../handlers/EventHandler.h"

#include "Data.h"

const std::string RESOURCES_PATH = "../resources/";

enum class LEVELS
{
	MENU = 0,
	GAMEOVER = 2,

	LEVEL1 = 11,
	LEVEL2 = 12,

	EXIT = 21,
	OPTIONS = 22,
	PLAY = 23,
	NAMESELECTER = 24,
	LEADERBOARD = 25,
	REPLAY = 26,
	RESOLUTION = 27
};

class Game
{
public:
	Game() : isRunning(true), renderer(nullptr), replayBits(0) {}
	void Init();
	void Update();
	void Cleanup();
	bool isRunning;
private:
	Leaderboard leaderboard{ "data/leaderboard_data.txt" };
	DynamicButton backButton{ "BACK", RESOURCES_PATH + "best.ttf", "", "blue", Data::GetInstance().GetData().user_config.screen_width / 2.0f, 100, 100, 0, 0, 0 };
	StaticButton startButton{ "START", RESOURCES_PATH + "best.ttf", "blue", "orange", Data::GetInstance().GetData().user_config.screen_width / 2.0f, Data::GetInstance().GetData().user_config.screen_height / 2 - (150 / (1080.0f / Data::GetInstance().GetData().user_config.screen_height)), 100, 0, 0, 0, (int)LEVELS::NAMESELECTER },
				 optionsButton{ "OPTIONS", RESOURCES_PATH + "best.ttf", "blue", "orange", Data::GetInstance().GetData().user_config.screen_width / 2.0f, Data::GetInstance().GetData().user_config.screen_height / 2.0f, 100, 0, 0, 0, (int)LEVELS::OPTIONS },
				 exitButton{ "EXIT", RESOURCES_PATH + "best.ttf", "blue", "orange", Data::GetInstance().GetData().user_config.screen_width / 2.0f, Data::GetInstance().GetData().user_config.screen_height / 2 + (150 / (1080.0f / Data::GetInstance().GetData().user_config.screen_height)), 100, 0, 0, 0, (int)LEVELS::EXIT},
				 resolutionButton{ "RESOLUTION", RESOURCES_PATH + "best.ttf", "blue", "orange", Data::GetInstance().GetData().user_config.screen_width / 2.0f, Data::GetInstance().GetData().user_config.screen_height / 2.0f, 100, 0, 0, 0, (int)LEVELS::RESOLUTION },
				 replayButton{ "REPLAY", RESOURCES_PATH + "best.ttf", "blue", "orange", Data::GetInstance().GetData().user_config.screen_width / 2.0f, Data::GetInstance().GetData().user_config.screen_height / 2.0f, 100, 0, 0, 0, (int)LEVELS::REPLAY},
				 leaderboardButton{ "LEADERBOARD", RESOURCES_PATH + "best.ttf", "blue", "orange", Data::GetInstance().GetData().user_config.screen_width / 2.0f, Data::GetInstance().GetData().user_config.screen_height / 2.0f - (150 / (1080.0f / Data::GetInstance().GetData().user_config.screen_height)), 100, 0, 0, 0, (int)LEVELS::LEADERBOARD };
	Player character{ Data::GetInstance().GetData().values.player_position_x,  Data::GetInstance().GetData().values.player_position_y, Data::GetInstance().GetData().values.hp };
	Farm farm{ Data::GetInstance().GetData().user_config.screen_width / 2, Data::GetInstance().GetData().user_config.screen_height / 2 };
	Door vrata1{ rand() % (Data::GetInstance().GetData().user_config.screen_width), rand() % (Data::GetInstance().GetData().user_config.screen_height), (int)LEVELS::LEVEL2 },
		 vrata2{ rand() % (Data::GetInstance().GetData().user_config.screen_width), rand() % (Data::GetInstance().GetData().user_config.screen_height), (int)LEVELS::GAMEOVER };
	Arena arena1{ rand() % (Data::GetInstance().GetData().user_config.screen_width), rand() % (Data::GetInstance().GetData().user_config.screen_height), 10 },
		  arena2{ rand() % (Data::GetInstance().GetData().user_config.screen_width), rand() % (Data::GetInstance().GetData().user_config.screen_height), 15 };
	std::vector<Bikec> bikec1, bikec2;
	std::vector<Enemy> enemy1, enemy2;
	int replayBits;
	Animation animation;
	SDL_Renderer *renderer;
};

