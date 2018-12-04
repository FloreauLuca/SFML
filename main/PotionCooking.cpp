#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
//#include <Box2D/Box2D.h>
#include <vector>
#include <iostream>
#include "PotionCooking/Draggable.h"

enum class WindowType {
	HOME,
	INGREDIENT,
	BAKING,
	PRESENTATION,
};

int main()
{
	
	sf::RenderWindow window(sf::VideoMode(750.0f, 500.0f), "Potion Cooking");
	sf::Clock clock;
	sf::View view1;
	view1.setCenter(sf::Vector2f(375, 250));
	view1.setSize(sf::Vector2f(750, 500));
	sf::Sprite spriteBackGround;
	sf::Texture textureBackGround;
	sf::Sprite spriteBones;
	sf::Texture textureBones;
	sf::Sprite spriteCauldron;
	sf::Texture textureCauldron;
	sf::Sprite spriteLadle;
	sf::Texture textureLadle;
	sf::Sprite spriteCup;
	sf::Texture textureCup;
	if (!textureBackGround.loadFromFile("data/PotionCooking/forest.png") || !textureBones.loadFromFile("data/PotionCooking/Os.png") || !textureCauldron.loadFromFile("data/PotionCooking/Chaudron.png") || !textureLadle.loadFromFile("data/PotionCooking/Louche.png") || !textureCup.loadFromFile("data/PotionCooking/Gobelet.png"))
	{
		return EXIT_FAILURE;
	}

	std::vector<Draggable> draggable;
	draggable.push_back(Draggable(&window, spriteBones, textureBones, 900, 100));
	draggable.push_back(Draggable(&window, spriteLadle, textureLadle, 1875, 300));

	spriteBackGround.setTexture(textureBackGround);
	spriteCauldron.setTexture(textureCauldron);
	spriteCup.setTexture(textureCup);
	//spriteLadle.setTexture(textureLadle);
	//spriteLadle.setPosition(1875, 300);
	spriteCup.setPosition(2500, 300);
	spriteCauldron.setOrigin(textureCauldron.getSize().x /2, textureCauldron.getSize().y /2);
	spriteCauldron.setPosition(1875, 400);
	spriteCauldron.scale(4, 4);
	WindowType currentWindow = WindowType::HOME;


	int viewX = 0;


	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{

					std::cout << "space" << std::endl;

					switch (currentWindow)
					{
					case WindowType::HOME:
					{
						currentWindow = WindowType::INGREDIENT;
						std::cout << "INGRE" << std::endl;
						viewX = 750;
						break;
					}
					case WindowType::INGREDIENT:
					{
						currentWindow = WindowType::BAKING;
						std::cout << "BAKE" << std::endl;
						viewX = 1500;
						break;
					}
					case WindowType::BAKING:
					{
						currentWindow = WindowType::PRESENTATION;
						std::cout << "PRE" << std::endl;
						viewX = 2250;
						break;
					}
					case WindowType::PRESENTATION:
					{
						currentWindow = WindowType::HOME;
						std::cout << "HOME" << std::endl;
						viewX = 0;
						break;
					}
					}
				}


			}


			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				for (auto & drag : draggable)
				{
					drag.mousePressed(event.mouseMove.x + viewX, event.mouseMove.y);
				}
			}

			//LMB released
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{

				for (auto & drag : draggable)
				{
					drag.mouseReleased();
				}
			}

			//Mouse Moved in window
			if (event.type == sf::Event::MouseMoved)
			{
				for (auto & drag : draggable)
				{
					drag.mouseMove(event.mouseMove.x + viewX, event.mouseMove.y);
				}

			}



			if (event.type == sf::Event::Closed)
				window.close();
		}

		//LOGIC
		for (auto& drag : draggable)
		{
			if (drag.dragging())
			{
				/*int maxX = window.getSize().x;
				int maxY = window.getSize().y;

				int mX = sf::Mouse::getPosition(window).x;
				int mY = sf::Mouse::getPosition(window).y;

				if (mX < 0 || mY < 0 || mX > maxX || mY > maxY)
				{
					if (mX < 0)
						mX = 0;
					else if (mX > maxX)
						mX = maxX;

					if (mY < 0)
						mY = 0;
					else if (mY > maxY)
						mY = maxY;

					sf::Mouse::setPosition(sf::Vector2i(mX, mY), window);
				}*/

				int maxX = window.getSize().x;
				int maxY = window.getSize().y;

				int mX = sf::Mouse::getPosition(window).x;
				int mY = sf::Mouse::getPosition(window).y;

				if (mX < 0 || mY < 0 || mX > maxX || mY > maxY)
				{
					if (mX < 0)
					{
						mX = maxX;
						switch (currentWindow)
						{
						case WindowType::HOME:
						{
							currentWindow = WindowType::PRESENTATION;
							std::cout << "PRESENTATION" << std::endl;
							viewX = 2250;
							break;
						}
						case WindowType::INGREDIENT:
						{
							currentWindow = WindowType::HOME;
							std::cout << "HOME" << std::endl;
							viewX = 0;
							break;
						}
						case WindowType::BAKING:
						{
							currentWindow = WindowType::INGREDIENT;
							std::cout << "INGREDIENT" << std::endl;
							viewX = 750;
							break;
						}
						case WindowType::PRESENTATION:
						{
							currentWindow = WindowType::BAKING;
							std::cout << "BAKING" << std::endl;
							viewX = 1500;
							break;
						}
						}
					}

					else if (mX > maxX)
					{
						mX = 0;
						switch (currentWindow)
						{
						case WindowType::HOME:
						{
							currentWindow = WindowType::INGREDIENT;
							std::cout << "INGRE" << std::endl;
							viewX = 750;
							break;
						}
						case WindowType::INGREDIENT:
						{
							currentWindow = WindowType::BAKING;
							std::cout << "BAKE" << std::endl;
							viewX = 1500;
							break;
						}
						case WindowType::BAKING:
						{
							currentWindow = WindowType::PRESENTATION;
							std::cout << "PRE" << std::endl;
							viewX = 2250;
							break;
						}
						case WindowType::PRESENTATION:
						{
							currentWindow = WindowType::HOME;
							std::cout << "HOME" << std::endl;
							viewX = 0;
							break;
						}
						}
					}


					if (mY < 0)
						mY = maxY;
					else if (mY > maxY)
						mY = 0;

					sf::Mouse::setPosition(sf::Vector2i(mX, mY), window);

				}
			}
		}
		
		
		view1.setCenter(sf::Vector2f((viewX+375), 250));
		window.setView(view1);
		//std::cout << view1.getCenter().x << std::endl;
		window.draw(spriteBackGround);
		for(auto & drag : draggable)
		{
			drag.draw();
		}
		
		window.draw(spriteCauldron);
		window.display();
	}

	return EXIT_SUCCESS;
}
