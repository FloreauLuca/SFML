#include "GameOfLife/Cells.h"
#include "GameOfLife/Map.h"

Cell::Cell(sf::Vector2i position, Map * map): position(position), map(map)
{
	isDestroyed = false;
	color = sf::Color(255, 255, 255);
	rect.setFillColor(color);
	rect.setPosition(position.x*50.0f, position.y*50.0f);
	rect.setOrigin(sf::Vector2f(0, 0));
	rect.setSize(sf::Vector2f(50.0f, 50.0f));
}

void Cell::FindNearbyCreature() {
	sf::Vector2i positionCentral = position;
	int cellNearby = 0;
	for (int x = positionCentral.x - 1; x < positionCentral.x + 2; x++) {
		if (x < 0 || x >= MAP_SIZE) {
			continue;
		}
		for (int y = positionCentral.y; y < positionCentral.y + 2; y++) {
			if (y < 0 || y >= MAP_SIZE) {
				continue;
			}
			sf::Vector2i currentPosition(x, y);
			if (map->CheckObjectOfTypeExistAt<Cell>(currentPosition)) {
				cellNearby++;
			}
		}
	}
	//REGLE IMPLEMENTATION HERE
	if (cellNearby < 2 || cellNearby >3)
	{
		map->RemoveObjectAt(position);
	}
	if (cellNearby == 3)
	{
		map->AddGameObjectAt(position);
	}

}

void Cell::FindNewCreature() {
	sf::Vector2i positionCentral = position;
	int cellNearby = 0;
	for (int x = positionCentral.x - 1; x < positionCentral.x + 3; x++) {
		if (x < 0 || x >= MAP_SIZE) {
			continue;
		}
		for (int y = positionCentral.y; y < positionCentral.y + 3; y++) {
			if (y < 0 || y >= MAP_SIZE) {
				continue;
			}
			sf::Vector2i currentPosition(x, y);
			if (map->CheckObjectOfTypeExistAt<Cell>(currentPosition)) {
			}
			else
			{
				FindNearbyCreature();
			}
		}
	}
}

sf::Vector2i Cell::GetPosition()
{
	return position;
}

void Cell::SetPosition(sf::Vector2i position)
{
	this->position = position;
	
}

bool Cell::IsObjectDestroyed()
{
	return isDestroyed;
}

void Cell::Destroy()
{
	isDestroyed = true;
}

void Cell::Update()
{
	if (isDestroyed)
	{
		return;
	}
	FindNearbyCreature();
	FindNewCreature();
}

