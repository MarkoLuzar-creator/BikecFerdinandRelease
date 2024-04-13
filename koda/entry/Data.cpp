#include "Data.h"
#include <fstream>

Data &Data::GetInstance()
{
	static Data instance;
	return instance;
}

void Data::Read()
{
	std::ifstream datai(DATA_PATH, std::ios::binary);
	if (datai.is_open())
	{
		GameConfig t;
		datai.read((char *)&t, sizeof(t));
		data = t;
	}
	datai.close();
}

void Data::Write()
{
	std::ofstream datao(DATA_PATH, std::ios::binary);
	datao.write((char *)&data, sizeof(data));
	datao.close();
}

GameConfig& Data::GetData()
{
	return data;
}
