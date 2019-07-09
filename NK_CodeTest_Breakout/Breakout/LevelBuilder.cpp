#include "LevelBuilder.h"

#include <fstream>
#include <iostream>
#include <sstream>

LevelBuilder::LevelBuilder()
{
}

LevelBuilder::~LevelBuilder()
{
}

void LevelBuilder::LoadLevel(std::string filename)
{
	std::string line;
	std::ifstream file;
	std::string path = "Content/Maps/";
	file.open(path + filename);


	if (file.is_open())
	{
		LevelSchema blueprint;


		
		// TODO: remove hard-code
		int width = 16;
		int height = 24;

		while (file.good())
		{
			std::getline(file, line);
			std::cout << line << std::endl;

			for (int i = 0; i < line.size(); i++)
			{
				char c = line.at(i);
				blueprint.ObjectIDs.push_back(c);
			}
		}

		blueprint.Cells.x = width;
		blueprint.Cells.y = height;

		m_blueprints.push_back(blueprint);
		file.close();
	}
	else
		std::cout << "failed to load" << std::endl;
}

bool LevelBuilder::GetLevel(int index, LevelSchema & level)
{
	if (index > m_blueprints.size())
		return false;
	else
		level = m_blueprints[index];
	return true;
}

int LevelBuilder::GetLevelCount()
{
	return m_blueprints.size();
}
