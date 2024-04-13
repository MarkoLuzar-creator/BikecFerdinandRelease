#include "Leaderboard.h"

void Leaderboard::Insert(std::string name, int points)
{
    std::ofstream datao("temp.txt");
    std::ifstream datai(fileName);
    bool insert = false;
    if (datai.is_open())
    {
        std::string line;
        while (std::getline(datai, line))
        {
            std::istringstream iss(line);
            std::string existingName;
            int existingPoints;
            if (iss >> existingName >> existingPoints)
            {
                if (points >= existingPoints && !insert)
                {
                    datao << name << " " << points << std::endl;
                    insert = true;
                }
                datao << existingName << " " << existingPoints << std::endl;
            }
        }
    }
    if (!insert)
    {
        datao << name << " " << points << std::endl;
    }
    datao.close();
    datai.close();
    remove(fileName.c_str());
    bool b = rename("temp.txt", fileName.c_str());
}


void Leaderboard::Display(std::string font, int x, int y, int numberShown, int padding, int size, int r, int g, int b)
{
	std::ifstream datai(fileName);
	if (datai.is_open())
	{
		std::string s;
		int i = 0, off = 0;
		while (std::getline(datai, s) && i < numberShown)
		{
			int w, h;
			TextureHandler::GetInstance().GetTextSizeScaled(s, font, size, w, h);
			TextureHandler::GetInstance().DrawText(s, font, x - w / 2, y - h / 2 + off, size, r, g, b);
			off += h + padding;
			i++;
		}
		datai.close();
	}
}
