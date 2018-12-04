#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <random>
#include <chrono>
//#include "GameOfLife/Cells.h"
//#include "GameOfLife/Map.h"
#include <list>
#include <vector>
#include <array>

/*
std::default_random_engine seed(std::chrono::system_clock::now().time_since_epoch().count());

int getValueRandom(int min, int max) {
	std::uniform_int_distribution<int> distribution(min, max);
	int randomValue = distribution(seed);
	return randomValue;
}

void Cell::Draw(sf::RenderWindow & window)
{
	rect.setPosition(position.x*50.0f, position.y*50.0f);
	window.draw(rect);
}

int main()
{
	sf::err().rdbuf(NULL);
	sf::RenderWindow window(sf::VideoMode(1000.0f, 1000.0f), "Game Of Life");
	sf::Clock clock;
	Map map(&window);
	map.AddGameObjectAt(sf::Vector2i(4, 5));
	map.AddGameObjectAt(sf::Vector2i(5, 5));
	map.AddGameObjectAt(sf::Vector2i(6, 5));
	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{

			}

			if (event.type == sf::Event::Closed)
				window.close();
		}
		map.Update();
		map.DisplayMap();
		window.display();
	}

	return EXIT_SUCCESS;
}
*/
const int MAP_SIZE = 10;

class Cell
{
public:
	Cell::Cell(sf::Vector2i position) : position(position)
	{
		
		color = sf::Color(255, 255, 255);
		rect.setFillColor(color);
		rect.setPosition(position.x*50.0f, position.y*50.0f);
		rect.setOrigin(sf::Vector2f(0, 0));
		rect.setSize(sf::Vector2f(50.0f, 50.0f));
	}

	void Draw(sf::RenderWindow & window)
	{
		rect.setPosition(position.x*50.0f, position.y*50.0f);
		window.draw(rect);
	}
private:
	sf::Color color;
	sf::RectangleShape rect;
	sf::Vector2i position;

};

class Map
{
public:
	Map(sf::RenderWindow window): window(window)
	{

	}

	bool CheckObjectOfTypeExistAt(sf::Vector2i position)
	{

	}

	void NewCell(sf::Vector2i position)
	{
		map[position.x][position.y] = std::make_unique<Cell>(position);
	}

	void DisplayMap() {
		system("cls");
		for (int i = 0; i < MAP_SIZE; i++)
		{
			for (int j = 0; j < MAP_SIZE; j++)
			{
				map[i][j]->Draw(window);
			}
		}
		system("Pause");
	}

private:
	std::array<std::array<std::unique_ptr<Cell>, MAP_SIZE>, MAP_SIZE> map;
	sf::RenderWindow window;
};


int main()
{
	sf::err().rdbuf(NULL);
	sf::RenderWindow window(sf::VideoMode(1000.0f, 1000.0f), "Game Of Life");
	sf::Clock clock;
	Map map(window);
	map.NewCell(sf::Vector2i(2, 2));
	while (window.isOpen())
	{

	sf::Time dt = clock.restart();
	// check all the window's events that were triggered since the last iteration of the loop
	sf::Event event{};
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
	
		}
	
		if (event.type == sf::Event::Closed)
			window.close();
	}
	map.DisplayMap();
	window.display();
	}

	return EXIT_SUCCESS;
}