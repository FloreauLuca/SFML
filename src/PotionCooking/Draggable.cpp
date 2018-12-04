#include <SFML/Graphics.hpp>
//#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include "PotionCooking/Draggable.h"

Draggable::Draggable(sf::RenderWindow * window, sf::Sprite sprite, sf::Texture texture, int posX, int posY) : window(window), sprite(sprite), texture(texture)
{
	sprite.setTexture(texture);
	sprite.setPosition(posX, posY);

	mouseX = 0;
	mouseY = 0;
	debugx = posX;
	debugy = posY;
	
	draggingBool = false;
	mouseClicked = false;
	mouseInsideRect = false;
}

void Draggable::update()
{

}

void Draggable::draw()
{
	window->draw(sprite);
}

bool Draggable::dragging()
{
	if (draggingBool)
	{
		sprite.setPosition(mouseX - mouseRectOffset.x, mouseY - mouseRectOffset.y);
	}
	return draggingBool;
}

void Draggable::setDraggingBool(bool entry)
{
	draggingBool = entry;
}

sf::Sprite Draggable::getSprite()
{
	return sprite;
}


void Draggable::mousePressed(int x, int y)
{
	mouseClicked = true;
	if (sprite.getGlobalBounds().contains(x,y))
	{
		draggingBool = true;
		mouseRectOffset.x = x - sprite.getGlobalBounds().left - sprite.getOrigin().x;
		mouseRectOffset.y = y - sprite.getGlobalBounds().top - sprite.getOrigin().y;
	}
}

void Draggable::mouseMove(int x, int y)
{
	
	mouseX = x;
	mouseY = y;
}

void Draggable::mouseReleased()
{
	mouseClicked = false;
	draggingBool = false;
}