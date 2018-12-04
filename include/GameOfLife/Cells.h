#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#ifndef CELL_H
#define CELL_H
class Map;
class Cell
{
public:
	Cell(sf::Vector2i position, Map * map);

	void Draw(sf::RenderWindow& window);

	void FindNearbyCreature();
	void FindNewCreature();
	sf::Vector2i GetPosition();

	void SetPosition(sf::Vector2i position);

	bool IsObjectDestroyed();
	void Destroy();
	void Update();
	sf::RectangleShape rect;

private:
	sf::Color color;
	sf::RenderWindow window;
	sf::Vector2i position;
	Map * map;
	bool isDestroyed;
};

#endif