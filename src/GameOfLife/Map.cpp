#include "GameOfLife/Map.h"
#include <iostream>


Map::Map(sf::RenderWindow * window) {


}

void Map::AddGameObjectAt(sf::Vector2i position) {

	if (map[position.x][position.y] == nullptr)
	{
		auto cell = std::make_shared<Cell>(position, this);
		cell->SetPosition(position);
		cellsForUpdate.push_back(cell.get());
		map[position.x][position.y] = std::move(cell);
		return;
	}

	return;
}


bool Map::RemoveObjectAt(sf::Vector2i position) {
	if (map[position.x][position.y] != nullptr)
	{
		map[position.x][position.y] = nullptr;
		return true;
	}
	return false;
}


void Map::Update() {
	for (auto & cell : cellsForUpdate) {
		cell->Update();
	}
	//Destroy element 

	//Destroy map elements 
	for (auto & gameObject : cellsForUpdate) {
		if (gameObject->IsObjectDestroyed()) {
			RemoveObjectAt(gameObject->GetPosition());
		}
	}
	cellsForUpdate.remove_if([](Cell * cell) {return cell->IsObjectDestroyed(); });

	//Destroy updates elements 
}

void Map::DisplayMap() {
	system("cls");
	for (auto& cell : cellsForUpdate)
	{
		cell->Draw(*window);
	}
	system("Pause");
}

int Map::CountCellsInMap() {
	int counter = 0;
	for (int x = 0; x < map.size(); x++) {
		for (int y = 0; y < map[x].size(); y++) {
			if (CheckObjectOfTypeExistAt<Cell>(sf::Vector2i(x, y))) {
				counter++;
			}
		}

	}

	return counter;
}