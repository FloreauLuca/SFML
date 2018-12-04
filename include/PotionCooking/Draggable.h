#include <SFML/Graphics.hpp>
//#include <Box2D/Box2D.h>
#include <iostream>
#include<vector>

#ifndef DRAGGABLE_H
#define DRAGGABLE_H

class Draggable
{
public:
	Draggable(sf::RenderWindow * window, sf::Sprite sprite, sf::Texture texture, int posX, int posY);

	void update();

	void draw();

	bool dragging();

	void setDraggingBool(bool entry);

	sf::Sprite getSprite();

	void mousePressed(int x, int y);

	void mouseMove(int x, int y);

	void mouseReleased();

private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::RenderWindow * window;
	bool draggingBool;

	int mouseX;
	int mouseY;


	bool mouseClicked;
	bool mouseInsideRect;

	sf::Vector2f mouseRectOffset;

	int debugx;
	int debugy;
};

#endif
