#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include  <cmath>
#include <list>
#include <random>
#include <chrono>

std::default_random_engine seed(std::chrono::system_clock::now().time_since_epoch().count());



enum class Color {
	WHITE,
	BLACK,
	RED,
	BLUE,
	GREEN,
};
enum class AnimPerso {
	PERSOFACE1,
	PERSOFACE2,
	PERSOBACK1,
	PERSOBACK2,
	PERSORIGHT1,
	PERSORIGHT2,
	PERSOLEFT1,
	PERSOLEFT2,
};


int getValueRandom(int min, int max) {
	std::uniform_int_distribution<int> distribution(min, max);
	int randomValue = distribution(seed);
	return randomValue;
}


class Obstacle
{
public:
	sf::FloatRect boundingBox;
	sf::RectangleShape obstacle;
	sf::Color color;
	Obstacle(int xstart, int ystart, int xend,int yend)
	{
		
		color = sf::Color(getValueRandom(0, 255), getValueRandom(0, 255), getValueRandom(0, 255));
		
		obstacle.setFillColor(color);
		obstacle.setPosition(xstart, ystart);
		obstacle.setSize(sf::Vector2f(abs(xstart-xend), abs(ystart - yend)));
		boundingBox = obstacle.getGlobalBounds();
	}
	

private:
	
	

};

Obstacle * isCollisionWithObstacle (sf::FloatRect playerHitBox, std::list<Obstacle> & listObstacle)
{
	for (auto & obstacle : listObstacle)
	{
		if (playerHitBox.intersects(obstacle.boundingBox))
		{
			return &obstacle;
		}
	}
	return nullptr;
}


int main()
{
	std::list<Obstacle> listObstacle;
	
	std::uniform_int_distribution<int> distribution(0, 255);

    sf::RenderWindow window(sf::VideoMode(1820,920), "WT Window");

	window.setFramerateLimit(60u);
	sf::Clock clock;
	sf::Vector2f velocity = sf::Vector2f(0.0f, 100.0f);

	sf::Sprite spriteTest;
	sf::Sprite spriteTest2;
	sf::Texture texturePersoFace1;
	sf::Texture texturePersoFace2;
	sf::Texture texturePersoBack1;
	sf::Texture texturePersoBack2;
	sf::Texture texturePersoRight1;
	sf::Texture texturePersoRight2;
	sf::Texture texturePersoLeft1;
	sf::Texture texturePersoLeft2;
	sf::Texture texturePersoBaron;
	sf::Texture currentTexture;
	std::default_random_engine random;
	
	if ((!texturePersoFace1.loadFromFile("data/PersoFace1.png")) || (!texturePersoFace2.loadFromFile("data/PersoFace2.png")) || (!texturePersoBack1.loadFromFile("data/PersoBack1.png")) || (!texturePersoBack2.loadFromFile("data/PersoBack2.png")) || (!texturePersoRight1.loadFromFile("data/PersoRight1.png")) || (!texturePersoRight2.loadFromFile("data/PersoRight2.png")) || (!texturePersoLeft1.loadFromFile("data/PersoLeft1.png")) || (!texturePersoLeft2.loadFromFile("data/PersoLeft2.png")) || (!texturePersoBaron.loadFromFile("data/Baron.png")))
	{
		return EXIT_FAILURE;
	}
	
	spriteTest.setTexture(texturePersoFace1);
	currentTexture = texturePersoFace1;
	spriteTest.setScale(5,5);
	Obstacle block = Obstacle(100, 100, 200, 200);
	listObstacle.push_back(block);
	Obstacle borderUp = Obstacle(0, -10, window.getSize().x, 0);
	listObstacle.push_back(borderUp);
	Obstacle borderDown = Obstacle(0, window.getSize().y, window.getSize().x, window.getSize().y-10);
	listObstacle.push_back(borderDown);
	Obstacle borderRight = Obstacle(window.getSize().x, 0, window.getSize().x+10, window.getSize().y);
	listObstacle.push_back(borderRight);
	Obstacle borderLeft = Obstacle(-10, 0, -20, window.getSize().y);
	listObstacle.push_back(borderLeft);

	Obstacle block2 = Obstacle(200, 100, 300, 200);
	listObstacle.push_back(block2);
	Obstacle block3 = Obstacle(400, 100, 500, 200);
	listObstacle.push_back(block3);
	Obstacle block4 = Obstacle(200, 400, 300, 500);
	listObstacle.push_back(block4);

	sf::FloatRect playerHitBox = spriteTest.getGlobalBounds();
	Color currentColor = Color::WHITE;
	AnimPerso currentAnim = AnimPerso::PERSOFACE1;

	sf::Vector2f direction(0, 0);
    // run the program as long as the window is open
    while (window.isOpen())
    {
		sf::Time dt = clock.restart();
        
        sf::Event event{};
		while (window.pollEvent(event))
		{
			//std::cout << "y " << window.getSize().y << std::endl;
			//std::cout << "x " << window.getSize().x << std::endl;
			// "close requested" event: we close the window
			
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
			{
				direction = sf::Vector2f(-10, 0);	
			} else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
			{
				direction = sf::Vector2f(10, 0);
			} else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
			{
				direction = sf::Vector2f(0, 10);
			} else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
			{
				direction = sf::Vector2f(0, -10);
			}

			if (event.type == sf::Event::KeyReleased)
			{
				direction = sf::Vector2f(0, 0);
			}

			if (direction == sf::Vector2f(-10, 0))
			{
				switch (currentAnim)
				{
				case AnimPerso::PERSOLEFT1:
				{
					currentAnim = AnimPerso::PERSOLEFT2;
					currentTexture = texturePersoLeft2;
					break;
				}
				case AnimPerso::PERSOLEFT2:
				{
					currentAnim = AnimPerso::PERSOLEFT1;
					currentTexture = texturePersoLeft1;
					break;
				}
				default:
				{
					currentAnim = AnimPerso::PERSOLEFT1;
					currentTexture = texturePersoLeft1;
					break;
				}
				}
			} else if (direction == sf::Vector2f(10, 0))
			{
				switch (currentAnim)
				{
				case AnimPerso::PERSORIGHT1:
				{
					currentAnim = AnimPerso::PERSORIGHT2;
					currentTexture = texturePersoRight2;
					break;
				}
				case AnimPerso::PERSORIGHT2:
				{
					currentAnim = AnimPerso::PERSORIGHT1;
					currentTexture = texturePersoRight1;
					break;
				}
				default:
				{
					currentAnim = AnimPerso::PERSORIGHT1;
					currentTexture = texturePersoRight1;
					break;
				}
				}
			} else if (direction == sf::Vector2f(0, 10))
			{
				switch (currentAnim)
				{
				case AnimPerso::PERSOFACE1:
				{
					currentAnim = AnimPerso::PERSOFACE2;
					currentTexture = texturePersoFace2;
					break;
				}
				case AnimPerso::PERSOFACE2:
				{
					currentAnim = AnimPerso::PERSOFACE1;
					currentTexture = texturePersoFace1;
					break;
				}
				default:
				{
					currentAnim = AnimPerso::PERSOFACE1;
					currentTexture = texturePersoFace1;
					break;
				}
				}
			} else if (direction == sf::Vector2f(0, -10))
			{
				switch (currentAnim)
				{
				case AnimPerso::PERSOBACK1:
				{
					currentAnim = AnimPerso::PERSOBACK2;
					currentTexture = texturePersoBack2;
					break;
				}
				case AnimPerso::PERSOBACK2:
				{
					currentAnim = AnimPerso::PERSOBACK1;
					currentTexture = texturePersoBack1;
					break;
				}
				default:
				{
					currentAnim = AnimPerso::PERSOBACK1;
					currentTexture = texturePersoBack1;
					break;
				}
				}
			}


			
			if (isCollisionWithObstacle(playerHitBox, listObstacle) != nullptr)
			{
				spriteTest.setColor(isCollisionWithObstacle(playerHitBox, listObstacle)->color);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				std::cout << "space" << std::endl;
				switch (currentColor)
				{
				case Color::WHITE:
				{
					currentColor = Color::BLACK;
					spriteTest.setColor(sf::Color(255, 255, 255));
					break;
				}
				case Color::BLACK:
				{
					currentColor = Color::BLUE;
					spriteTest.setColor(sf::Color(0, 0, 255));
					break;
				}
				case Color::BLUE:
				{
					currentColor = Color::GREEN;
					spriteTest.setColor(sf::Color(0, 255, 0));
					break;
				}
				case Color::GREEN:
				{
					currentColor = Color::RED;
					spriteTest.setColor(sf::Color(255, 0, 0));
					break;
				}
				case Color::RED:
				{
					currentColor = Color::WHITE;
					spriteTest.setColor(sf::Color(0, 0, 0));
					break;
				}
				}
				//currentTexture = texturePersoBaron;
				
			}
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		spriteTest.move(direction);
		playerHitBox = spriteTest.getGlobalBounds();
		if (isCollisionWithObstacle(playerHitBox, listObstacle))
		{
			spriteTest.move(-direction);
		}
		/*spriteTest.setPosition(spriteTest.getPosition() + velocity * dt.asSeconds());
		playerHitBox = spriteTest.getGlobalBounds();
		if (isCollisionWithObstacle(playerHitBox))
		{
			spriteTest.setPosition(spriteTest.getPosition() + velocity * dt.asSeconds() *(-1.0f));
		}*/

		spriteTest.setTextureRect(sf::IntRect(0, 0, currentTexture.getSize().x, currentTexture.getSize().y));
		spriteTest.setScale(5, 5);
		spriteTest.setTexture(currentTexture);
		window.clear(sf::Color::White);
		window.draw(spriteTest);
		for (auto & obstacle : listObstacle)
		{
			window.draw(obstacle.obstacle);
		}
		window.display();
        

		
    }


    return EXIT_SUCCESS;


}
