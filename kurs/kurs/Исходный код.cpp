#include < SFML/Graphics.hpp >
#include <SFML/Audio.hpp>
#include <iostream>
#include "Player.h"

using namespace sf;
using namespace std;
int main()
{
	RenderWindow window(VideoMode(1360, 780), "Avatar: The Legend of Korra", Style::Fullscreen);
	
	Texture text;
	
	RectangleShape rectangle;

	// лемч
	Music menu;
	menu.openFromFile("Theme.ogg");

	Texture menu_texture0, menu_texture1, menu_texture2, menu_texture3, menu_texture4, about_texture, act_texture;
	menu_texture0.loadFromFile("images/header.jpg");
	menu_texture1.loadFromFile("images/111.png");
	menu_texture2.loadFromFile("images/222.png");
	menu_texture3.loadFromFile("images/333.png");
	menu_texture4.loadFromFile("images/444.png");
	about_texture.loadFromFile("images/inf.jpg");
	act_texture.loadFromFile("images/uprav.png");
	Sprite  menu0(menu_texture0), menu1(menu_texture1), menu2(menu_texture2), menu3(menu_texture3), menu4(menu_texture4), about(about_texture), act(act_texture);
	bool Menu = 1;
	int MenuNum = 0;

	menu0.setPosition(0, 0);
	menu1.setPosition(450, 100);
	menu2.setPosition(200, 600);
	menu3.setPosition(870, 590);
	menu4.setPosition(550, 600);
	
	menu.play();

	while (Menu)
	{
		menu1.setColor(Color::Black);
		menu2.setColor(Color::Black);
		menu3.setColor(Color::Black);
		menu4.setColor(Color::Black);
		MenuNum = 0;
		window.clear(Color(0, 0, 0));

		if (IntRect(450, 100, 500, 150).contains(Mouse::getPosition(window))) { menu1.setColor(Color::White); MenuNum = 1; }
		if (IntRect(200, 600, 250, 75).contains(Mouse::getPosition(window))) { menu2.setColor(Color::White); MenuNum = 2; }
		if (IntRect(870, 590, 250, 75).contains(Mouse::getPosition(window))) { menu3.setColor(Color::White); MenuNum = 3; }
		if (IntRect(550, 600, 250, 75).contains(Mouse::getPosition(window))) { menu4.setColor(Color::White); MenuNum = 4; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (MenuNum == 1) { menu.stop(); play(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); if (Menu) menu.play(); }
			if (MenuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (MenuNum == 3)  { window.close(); Menu = false;  }
			if (MenuNum == 4) { window.draw(act); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }

		}

		window.draw(menu0);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.draw(menu4);
		window.display();
	}
	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			window.clear();
			window.display();
			
			if (Event::Closed)
			{
				window.close();
			} 

			if (Keyboard::Escape)
			
				window.close();
			
		}
	}

	return 0;
}