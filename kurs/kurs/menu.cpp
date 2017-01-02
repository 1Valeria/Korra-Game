#include "menu.h"

menu::menu(float width, float height)
{
	if (!font.loadFromFile("ASIAN.ttf"))
	{
		// error
	}
	

	Menu[0].setFont(font);
	Menu[0].setColor(sf::Color::White);
	Menu[0].setCharacterSize(80);
	Menu[0].setString("PLAY");
	Menu[0].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	Menu[1].setFont(font);
	Menu[1].setColor(sf::Color::Cyan);
	Menu[1].setCharacterSize(80);
	Menu[1].setString("SETTINGS");
	Menu[1].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
	
	Menu[2].setFont(font);
	Menu[2].setColor(sf::Color::Cyan);
	Menu[2].setCharacterSize(80);
	Menu[2].setString("INFORMATION");
	Menu[2].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	
	Menu[3].setFont(font);
	Menu[3].setColor(sf::Color::Cyan);
	Menu[3].setCharacterSize(80);
	Menu[3].setString("EXIT");
	Menu[3].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS + 1) * 4));

	

	selectedItemIndex = 0;
}


menu::~menu()
{
}

void menu::draw(sf::RenderWindow &window)
{
	window.clear(sf::Color::Blue);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(Menu[i]);
	}
	
}

void menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		Menu[selectedItemIndex].setColor(sf::Color::Cyan);
		selectedItemIndex--;
		Menu[selectedItemIndex].setColor(sf::Color::White);
	}
}

void menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		Menu[selectedItemIndex].setColor(sf::Color::Cyan);
		selectedItemIndex++;
		Menu[selectedItemIndex].setColor(sf::Color::White);
	}
}