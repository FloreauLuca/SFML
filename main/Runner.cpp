#include <Box2D/Box2D.h>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

const int PPM = 30;


struct body
{
	b2BodyDef DEF;
	b2PolygonShape SHAPE;
	b2FixtureDef FIX;
	b2Body * BOD;
	sf::RectangleShape RECT;
};

int main ()
{
	b2World world(b2Vec2(0.0f, 9.81f)); // initialise gravité
	sf::RenderWindow window(sf::VideoMode(800.0f, 600.0f), "Thomas_was_around");
	body ground;
	ground.DEF.position.Set(400.0f / PPM, 600.0f / PPM);
	ground.RECT = sf::RectangleShape(sf::Vector2f(8000, 25));
	ground.RECT.SetOrigin(4000, 25);
	ground.RECT.SetFillColor(sf::Color(200, 75, 20, 255));
	ground.SHAPE.SetAsBox(4000.0f / PPM, 25.0f / PPM);
	ground.BOD = world.CreateBody(&ground.DEF);
	ground.FIX.shape = &ground.SHAPE;

	window.setFramerateLimit(60u);
	sf::Clock clock;
	sf::Vector2f velocity = sf::Vector2f(0.0f, 100.0f);

	sf::Sprite spriteTest;
	sf::Texture texturePersoFace1;
	if (!texturePersoFace1.loadFromFile("data/PersoFace1.png"))
	{
		return EXIT_FAILURE;
	}
	//PlayerCharacter player();

	spriteTest.setTexture(texturePersoFace1);

	while (window.isOpen())
	{
		window.draw(rect);
	}


	return EXIT_SUCCESS;


}