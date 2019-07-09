#pragma once

#include <vector>
#include <map>
#include <SFML\System\Vector2.hpp>

struct LevelSchema
{
	sf::Vector2i Cells;
	std::vector<char> ObjectIDs;
};

/*
	Level builder is responsible for loading levels from text and arranging a schema 
	for building in the default game environment
*/
class LevelBuilder
{
public:
	LevelBuilder();
	~LevelBuilder();

	void LoadLevel(std::string path);
	bool GetLevel(int index, LevelSchema& level);
	int GetLevelCount();

private:
	std::vector<LevelSchema> m_blueprints;
};

