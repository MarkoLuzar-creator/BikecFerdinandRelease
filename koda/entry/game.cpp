#pragma once
#include "Game.h"

void Game::Init()
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	TTF_Init();

	SDL_Window *window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Data::GetInstance().GetData().user_config.screen_width,Data::GetInstance().GetData().user_config.screen_height, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	TextureHandler::GetInstance().SetRenderer(renderer, Data::GetInstance().GetData().user_config.screen_width, Data::GetInstance().GetData().user_config.screen_height);
	CameraHandler::GetInstance().SetScreenSize(Data::GetInstance().GetData().user_config.screen_width, Data::GetInstance().GetData().user_config.screen_height);
	std::string icon_path = RESOURCES_PATH + "window_icon.png";
	SDL_Surface *icon = IMG_Load(icon_path.c_str());
	SDL_SetWindowIcon(window, icon);
	SDL_RenderClear(renderer);
	int w, h;
	TextureHandler::GetInstance().GetTextSizeScaled("Initializing", RESOURCES_PATH + "best.ttf", 100, w, h);
	TextureHandler::GetInstance().DrawText("Initializing", RESOURCES_PATH + "best.ttf", (Data::GetInstance().GetData().user_config.screen_width / 2 - w / 2) * (1920 / Data::GetInstance().GetData().user_config.screen_width), (Data::GetInstance().GetData().user_config.screen_height / 2 - h / 2) * (1080 / Data::GetInstance().GetData().user_config.screen_height), 100, 255, 255, 255);
	SDL_RenderPresent(renderer);

	TextureHandler::GetInstance().LoadTexture(RESOURCES_PATH + "arena.png", "arena");
	TextureHandler::GetInstance().LoadTexture(RESOURCES_PATH + "Door.png", "door");
	TextureHandler::GetInstance().LoadTexture(RESOURCES_PATH + "enemy.png", "enemy");
	TextureHandler::GetInstance().LoadTexture(RESOURCES_PATH + "player.png", "player");
	TextureHandler::GetInstance().LoadTexture(RESOURCES_PATH + "blu.png", "blue");
	TextureHandler::GetInstance().LoadTexture(RESOURCES_PATH + "Barn.png", "Barn");
	TextureHandler::GetInstance().LoadTexture(RESOURCES_PATH + "crni_bikec.png", "crni_bikec");
	TextureHandler::GetInstance().LoadTexture(RESOURCES_PATH + "mesani_bikec.png", "mesani_bikec");
	TextureHandler::GetInstance().LoadTexture(RESOURCES_PATH + "rjavi_bikec.png", "rjavi_bikec");
	TextureHandler::GetInstance().LoadTexture(RESOURCES_PATH + "beli_bikec.png", "beli_bikec");
	TextureHandler::GetInstance().LoadTexture(RESOURCES_PATH + "bk.jpg", "bk");
	TextureHandler::GetInstance().LoadTexture(RESOURCES_PATH + "ozadje.png", "ozadje");
	TextureHandler::GetInstance().LoadTexture(RESOURCES_PATH + "orange.png", "orange");
	TextureHandler::GetInstance().LoadTexture(RESOURCES_PATH + "levels.png", "levels");
	for (int i = 0; i < 5; i++)
	{
		Enemy temp(rand() % (Data::GetInstance().GetData().user_config.screen_width), rand() % (Data::GetInstance().GetData().user_config.screen_height));
		enemy1.push_back(temp);
	}
	for (int i = 0; i < 5; i++)
	{
		Bikec temp(rand() % (Data::GetInstance().GetData().user_config.screen_width), rand() % (Data::GetInstance().GetData().user_config.screen_height));
		bikec1.push_back(temp);
	}
	for (int i = 0; i < 10; i++)
	{
		Enemy temp(rand() % (Data::GetInstance().GetData().user_config.screen_width), rand() % (Data::GetInstance().GetData().user_config.screen_height));
		enemy2.push_back(temp);
	}
	for (int i = 0; i < 5; i++)
	{
		Bikec temp(rand() % (Data::GetInstance().GetData().user_config.screen_width), rand() % (Data::GetInstance().GetData().user_config.screen_height));
		bikec2.push_back(temp);
	}
}
void Game::Update()
{
	TimeHandler::GetInstance().Tick();
	EventHandler::GetInstance().Listen();
	float deltaTime = TimeHandler::GetInstance().GetDeltaTime();

	SDL_RenderClear(renderer);
	switch ((Data::GetInstance().GetData().values.level))
	{
		case (int)LEVELS::MENU:
	{
		SDL_SetRenderDrawColor(renderer, 255, 208, 141, 255);

		animation.SetProperties(0, 8, 200);
		animation.Update();
		TextureHandler::GetInstance().DrawAnimation("ozadje", 0, -300, 1920, 2000, animation.GetRow(), animation.GetFrame(), SDL_FLIP_NONE, 1);
		Data::GetInstance().GetData().values.level = startButton.Update(Data::GetInstance().GetData().values.level);
		Data::GetInstance().GetData().values.level = optionsButton.Update(Data::GetInstance().GetData().values.level);
		Data::GetInstance().GetData().values.level = exitButton.Update(Data::GetInstance().GetData().values.level);

		EventHandler::GetInstance().ClearTextBuffer();
		break;
	}
		case (int)LEVELS::NAMESELECTER:
	{
		SDL_SetRenderDrawColor(renderer, 255, 208, 141, 255);
		int x1, y1, x2, y2;
		std::string playerName;
		EventHandler::GetInstance().GetTextBuffer(playerName);

		TextureHandler::GetInstance().GetTextSizeScaled("Vnesite ime", RESOURCES_PATH + "best.ttf", 100, x1, y1);
		TextureHandler::GetInstance().GetTextSizeScaled(playerName, RESOURCES_PATH + "best.ttf", 100, x2, y2);
		TextureHandler::GetInstance().DrawText("Vnesite ime", RESOURCES_PATH + "best.ttf", Data::GetInstance().GetData().user_config.screen_width / 2 - x1 / 2, 100, 100, 0, 0, 0);
		TextureHandler::GetInstance().DrawText(playerName, RESOURCES_PATH + "best.ttf", Data::GetInstance().GetData().user_config.screen_width / 2 - x2 / 2, Data::GetInstance().GetData().user_config.screen_height / 2, 100, 0, 0, 0);

		if (EventHandler::GetInstance().GetKeyDown(SDL_SCANCODE_RETURN))
		{
			Data::GetInstance().GetData().values.level = (int)LEVELS::LEVEL1;
			Data::GetInstance().GetData().values.player_name = playerName;
			EventHandler::GetInstance().ClearTextBuffer();
		}
		break;
	}
		case (int)LEVELS::OPTIONS:
	{
		SDL_SetRenderDrawColor(renderer, 255, 208, 141, 255);
		Data::GetInstance().GetData().values.level = resolutionButton.Update(Data::GetInstance().GetData().values.level);
		Data::GetInstance().GetData().values.level = backButton.Update(Data::GetInstance().GetData().values.level, (int)LEVELS::MENU);
		break;
	}
		case (int)LEVELS::RESOLUTION:
	{
		Data::GetInstance().GetData().user_config.screen_width -= 200;
		Data::GetInstance().GetData().user_config.screen_height -= 100;
		if (Data::GetInstance().GetData().user_config.screen_width < 1100)
		{
			Data::GetInstance().GetData().user_config.screen_width = 1920;
			Data::GetInstance().GetData().user_config.screen_height = 1080;
		}

		Data::GetInstance().GetData().values.level = (int)LEVELS::OPTIONS;
		Data::GetInstance().Write();
		system("start bikec_ferdinand.exe");
		SDL_Quit();
		IMG_Quit();
		TTF_Quit();
		exit(0);
		break;
	}
		case (int)LEVELS::EXIT:
	{
		remove(DATA_PATH.c_str());
		remove("data/replay.txt");
		SDL_Quit();
		IMG_Quit();
		TTF_Quit();
		exit(0);
		break;
	}
		case (int)LEVELS::LEVEL1:
	{
		SDL_SetRenderDrawColor(renderer, 53, 94, 59, 255);
		int cx, cy;
		CameraHandler::GetInstance().GetPosition(cx, cy);
		TextureHandler::GetInstance().DrawTexture("levels", -1000 - cx, -600 - cy, 6000, 4000, SDL_FLIP_NONE, 1);
		farm.Update();
		character.Update(deltaTime);
		Data::GetInstance().GetData().values.points += farm.GetPoints();
		Data::GetInstance().GetData().values.points += arena1.Update(character.GetPosition().first, character.GetPosition().second, character.GetSize().first, character.GetSize().second);

		std::pair<int, bool> v = vrata1.Update(arena1.OpenDoor(), character.GetPosition().first, character.GetPosition().second, character.GetSize().first, character.GetSize().second, Data::GetInstance().GetData().values.level);
		if (v.second == true)
		{
			SDL_SetRenderDrawColor(renderer,0, 0, 0, 0);
			SDL_RenderClear(renderer);
			int w, h;
			TextureHandler::GetInstance().GetTextSizeScaled("Level completed 1", RESOURCES_PATH + "best.ttf", 100, w, h);
			TextureHandler::GetInstance().DrawText("Level completed 1", RESOURCES_PATH + "best.ttf", (Data::GetInstance().GetData().user_config.screen_width / 2 - w / 2) * (1920 / Data::GetInstance().GetData().user_config.screen_width), (Data::GetInstance().GetData().user_config.screen_height / 2 - h / 2) * (1080 / Data::GetInstance().GetData().user_config.screen_height), 100, 255, 255, 255);
			SDL_RenderPresent(renderer);
			SDL_Delay(3000);
		}
		Data::GetInstance().GetData().values.level = v.first;

		for (std::vector<Bikec>::iterator it = bikec1.begin(); it != bikec1.end(); it++)
		{
			it->Update(deltaTime, character.GetPosition().first, character.GetPosition().second);
		}
		for (std::vector<Enemy>::iterator it = enemy1.begin(); it != enemy1.end(); it++)
		{
			for (std::vector<Bikec>::iterator itb = bikec1.begin(); itb != bikec1.end(); itb++)
			{
				it->Update(deltaTime, character.GetPosition().first, character.GetPosition().second, itb->GetPosition().first, itb->GetPosition().second, character.GetAttack());
				it->UpdateCollision2(itb->GetPosition().first, itb->GetPosition().second, itb->GetSize().first, itb->GetSize().second);
				itb->CollisionUpdate(it->GetAttack2(), farm.CheckCollisions(itb->GetPosition().first, itb->GetPosition().second, itb->GetSize().first, itb->GetSize().second));
			}
			it->UpdateCollision1(character.GetPosition().first, character.GetPosition().second, character.GetSize().first, character.GetSize().second);
			character.EnemyAttackUpdate(it->GetAttack1());
		}
		if (character.GetHP() <= 0)
		{
			Data::GetInstance().GetData().values.level = (int)LEVELS::GAMEOVER;
		}

		int w, h;
		std::string points = std::to_string(Data::GetInstance().GetData().values.points);
		TextureHandler::GetInstance().GetTextSizeScaled(points, RESOURCES_PATH + "best.ttf", 50, w, h);
		TextureHandler::GetInstance().DrawText(points, RESOURCES_PATH + "best.ttf", 0, (Data::GetInstance().GetData().user_config.screen_height - h) * (1080 / Data::GetInstance().GetData().user_config.screen_height), 50, 255, 255, 255);

		if (!arena1.OpenDoor())
		{
			std::string arene = "Stevilo aren: " + std::to_string(arena1.GetCount());
			TextureHandler::GetInstance().GetTextSizeScaled(arene, RESOURCES_PATH + "best.ttf", 50, w, h);
			TextureHandler::GetInstance().DrawText(arene, RESOURCES_PATH + "best.ttf", (Data::GetInstance().GetData().user_config.screen_width / 2 - w / 2) *(1920 / Data::GetInstance().GetData().user_config.screen_width), 0, 50, 255, 255, 255);
		}

		std::ofstream datao("data/replay.txt", std::ios::app);
		datao << character.GetPosition().first << " " << character.GetPosition().second << std::endl;
		datao.close();
		break;
	}
		case (int)LEVELS::LEVEL2:
	{
			SDL_SetRenderDrawColor(renderer, 53, 94, 59, 255);
			int cx, cy;
			CameraHandler::GetInstance().GetPosition(cx, cy);
			TextureHandler::GetInstance().DrawTexture("levels", -1000 - cx, -600 - cy, 6000, 4000, SDL_FLIP_NONE, 1);
			farm.Update();
			character.Update(deltaTime);
			Data::GetInstance().GetData().values.points += farm.GetPoints();
			Data::GetInstance().GetData().values.points += arena2.Update(character.GetPosition().first, character.GetPosition().second, character.GetSize().first, character.GetSize().second);
			std::pair<int, bool> v = vrata2.Update(arena2.OpenDoor(), character.GetPosition().first, character.GetPosition().second, character.GetSize().first, character.GetSize().second, Data::GetInstance().GetData().values.level);
			if (v.second == true)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
				SDL_RenderClear(renderer);
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				int w, h;
				TextureHandler::GetInstance().GetTextSizeScaled("Level completed 2", RESOURCES_PATH + "best.ttf", 100, w, h);
				TextureHandler::GetInstance().DrawText("Level completed 2", RESOURCES_PATH + "best.ttf", (Data::GetInstance().GetData().user_config.screen_width / 2 - w / 2) * (1920 / Data::GetInstance().GetData().user_config.screen_width), (Data::GetInstance().GetData().user_config.screen_height / 2 - h / 2) * (1080 / Data::GetInstance().GetData().user_config.screen_height), 100, 255, 255, 255);
				SDL_RenderPresent(renderer);
				SDL_Delay(3000);
			}
			Data::GetInstance().GetData().values.level = v.first;

			for (std::vector<Bikec>::iterator it = bikec2.begin(); it != bikec2.end(); it++)
			{
				it->Update(deltaTime, character.GetPosition().first, character.GetPosition().second);
			}
			for (std::vector<Enemy>::iterator it = enemy2.begin(); it != enemy2.end(); it++)
			{
				for (std::vector<Bikec>::iterator itb = bikec2.begin(); itb != bikec2.end(); itb++)
				{
					it->Update(deltaTime, character.GetPosition().first, character.GetPosition().second, itb->GetPosition().first, itb->GetPosition().second, character.GetAttack());
					it->UpdateCollision2(itb->GetPosition().first, itb->GetPosition().second, itb->GetSize().first, itb->GetSize().second);
					itb->CollisionUpdate(it->GetAttack2(), farm.CheckCollisions(itb->GetPosition().first, itb->GetPosition().second, itb->GetSize().first, itb->GetSize().second));
				}
				it->UpdateCollision1(character.GetPosition().first, character.GetPosition().second, character.GetSize().first, character.GetSize().second);
				character.EnemyAttackUpdate(it->GetAttack1());
			}
			if (character.GetHP() <= 0)
			{
				Data::GetInstance().GetData().values.level = (int)LEVELS::GAMEOVER;
			}

			int w, h;
			std::string points = std::to_string(Data::GetInstance().GetData().values.points);
			TextureHandler::GetInstance().GetTextSizeScaled(points, RESOURCES_PATH + "best.ttf", 50, w, h);
			TextureHandler::GetInstance().DrawText(points, RESOURCES_PATH + "best.ttf", 0, (Data::GetInstance().GetData().user_config.screen_height - h) * (1080 / Data::GetInstance().GetData().user_config.screen_height), 50, 255, 255, 255);

			if (!arena2.OpenDoor())
			{
				std::string arene = "Stevilo aren: " + std::to_string(arena2.GetCount());
				TextureHandler::GetInstance().GetTextSizeScaled(arene, RESOURCES_PATH + "best.ttf", 50, w, h);
				TextureHandler::GetInstance().DrawText(arene, RESOURCES_PATH + "best.ttf", (Data::GetInstance().GetData().user_config.screen_width / 2 - w / 2) *(1920 / Data::GetInstance().GetData().user_config.screen_width), 0, 50, 255, 255, 255);
			}

			std::ofstream datao("data/replay.txt", std::ios::app);
			datao << character.GetPosition().first << " " << character.GetPosition().second << std::endl;
			datao.close();
		break;
	}
		case (int)LEVELS::GAMEOVER:
	{
		if (Data::GetInstance().GetData().values.leaderboard_insert == false)
		{
			leaderboard.Insert(Data::GetInstance().GetData().values.player_name, Data::GetInstance().GetData().values.points);
			Data::GetInstance().GetData().values.leaderboard_insert = true;
		}
		SDL_SetRenderDrawColor(renderer, 255, 208, 141, 255);
		Data::GetInstance().GetData().values.level = leaderboardButton.Update(Data::GetInstance().GetData().values.level);
		Data::GetInstance().GetData().values.level = replayButton.Update(Data::GetInstance().GetData().values.level);
		Data::GetInstance().GetData().values.level = exitButton.Update(Data::GetInstance().GetData().values.level);
		break;
	}
		case (int)LEVELS::LEADERBOARD:
	{
		SDL_SetRenderDrawColor(renderer, 211, 211, 211, 255);
		leaderboard.Display(RESOURCES_PATH + "best.ttf", Data::GetInstance().GetData().user_config.screen_width / 2,
		Data::GetInstance().GetData().user_config.screen_height / 2, 5, 20, 60, 0, 0, 0);
		Data::GetInstance().GetData().values.level = backButton.Update(Data::GetInstance().GetData().values.level, (int)LEVELS::GAMEOVER);
		break;
	}
		case (int)LEVELS::REPLAY:
	{
		SDL_SetRenderDrawColor(renderer, 211, 211, 211, 255);
		std::ifstream datai("data/replay.txt");
		if (datai.is_open())
		{
			std::string buf1, buf2;
			char c;
			bool next = 0;
			datai.seekg(replayBits, std::ios::beg);
			while (datai >> std::noskipws >> c)
			{
				if (c == ' ')
				{
					next = 1;
				}
				else if (c == '\n')
				{
					int x = (Data::GetInstance().GetData().user_config.screen_width / 2 - std::stoi(buf1)) * ((Data::GetInstance().GetData().user_config.screen_width / 1920.0f) * 0.4);
					int y = (Data::GetInstance().GetData().user_config.screen_height / 2 - std::stoi(buf2)) * ((Data::GetInstance().GetData().user_config.screen_height / 1080.0f) * 0.4);
					animation.SetProperties(0, 5, 50);
					animation.Update();
					TextureHandler::GetInstance().DrawAnimation("player", Data::GetInstance().GetData().user_config.screen_width / 2 - x, Data::GetInstance().GetData().user_config.screen_height / 2 - y, 64, 64, animation.GetRow(), animation.GetFrame(), SDL_FLIP_NONE, 2);
					buf1 = "";
					buf2 = "";
					break;
				}

				if (next == 0)
				{
					buf1 += c;
				}
				else
				{
					buf2 += c;
				}
			}
			replayBits = datai.tellg();
			if (datai.eof())
			{
				replayBits = 0;
			}
			datai.close();
		}
		Data::GetInstance().GetData().values.level = backButton.Update(Data::GetInstance().GetData().values.level, (int)LEVELS::GAMEOVER);
		break;
	}
	}
	if (EventHandler::GetInstance().GetKeyDown(SDL_SCANCODE_ESCAPE))
	{
		isRunning = false;
	}
	if (EventHandler::GetInstance().GetKeyDown(SDL_SCANCODE_DELETE))
	{
		remove(DATA_PATH.c_str());
		remove("data/replay.txt");
		SDL_Quit();
		IMG_Quit();
		TTF_Quit();
		exit(0);
	}
	Data::GetInstance().GetData().values.player_position_x = character.GetPosition().first;
	Data::GetInstance().GetData().values.player_position_y = character.GetPosition().second;
	SDL_RenderPresent(renderer);
}
void Game::Cleanup()
{
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}
