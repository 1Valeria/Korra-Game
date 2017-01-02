#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

using namespace sf;

#define MAX_NUMBER_OF_ITEMS 4

class menu
{
public:
	menu(float width, float height);
	~menu();
	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text Menu[MAX_NUMBER_OF_ITEMS];

};

