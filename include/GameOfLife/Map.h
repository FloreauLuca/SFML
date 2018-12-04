#include <array>
#include <list>
#include <memory>
#include "GameOfLife/Cells.h"

#ifndef MAP_H
#define MAP_H

const int MAP_SIZE = 10;

class Map
{
public:
	Map(sf::RenderWindow * window);

	void AddGameObjectAt(sf::Vector2i position);

	template<typename T> bool CheckObjectOfTypeExistAt(sf::Vector2i position);

	bool RemoveObjectAt(sf::Vector2i position);

	void Update();

	void DisplayMap();

	int CountCellsInMap();

private:
	std::array<std::array<std::shared_ptr<Cell>, MAP_SIZE>, MAP_SIZE> map;
	std::list<Cell*> cellsForUpdate;
	sf::RenderWindow * window;
};

template<typename T> bool Map::CheckObjectOfTypeExistAt(sf::Vector2i position) {
	if (map[position.x][position.y] == nullptr) {
		return false;
	}
	auto * cell = dynamic_cast<T*>(map[position.x][position.y].get());

	return cell != nullptr;
}

#endif