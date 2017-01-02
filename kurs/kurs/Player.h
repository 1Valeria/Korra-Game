#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Map.h"

using namespace sf;

int ground = 10400;
float offsetX = 0, offsetY = 0;

class ENEMY
{

public:
	float dx, dy;
	FloatRect rect;
	Sprite sprite;
	float currentFrame;
	bool life;


	void set(Texture &image, int x, int y)
	{
		sprite.setTexture(image);
		rect = FloatRect(x, y, 65, 108);

		dx = 0.05;
		currentFrame = 0;
		life = true;
	}

	void update(float time)
	{
		rect.left += dx * time;

		Collision();

		currentFrame += time * 0.005;
		if (currentFrame > 2) currentFrame -= 2;

		sprite.setTextureRect(IntRect(60 * int(currentFrame), 0, 65, 108));

		if (!life) 
			sprite.setTextureRect(IntRect(132, 0, 65, 108));


		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

	}


	void Collision()
	{

		for (int i = rect.top / 32; i<(rect.top + rect.height) / 32; i++)
			for (int j = rect.left / 32; j<(rect.left + rect.width) / 32; j++)
				if (TileMap[i][j] == 'A')
				{
			if (dx>0)
			{
				rect.left = j * 32 - rect.width; dx *= -1;
			}
			else if (dx<0)
			{
				rect.left = j * 32 + 32;  dx *= -1;
			}

				}
	}

};

class PLAYER {
public:

	float dx, dy, d0;
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	int counter;
	float currentFrame;

	PLAYER(Texture & image)
	{
		sprite.setTexture(image);

		sprite.setTextureRect(IntRect(0, 0, 65, 108));
		rect = FloatRect(100, 1400, 65, 108);

		dx = dy = d0 = 0;
		currentFrame = 0;
	}
	void update(float time)
	{
		rect.left += dx * time;

		Collision(0);

		if (!onGround) dy = dy + 0.0009 * time;

		rect.top += dy*time;
		onGround = false;

		Collision(1);

		if (rect.top>ground){ rect.top = ground; dy = 0; onGround = true; }

		currentFrame += 0.005*time;
		if (currentFrame>5) currentFrame -= 5;

		if (dx > 0)
			sprite.setTextureRect(IntRect(87 * int(currentFrame), 113, 87, 113));
		else if (dx < 0)
			sprite.setTextureRect(IntRect(87 * int(currentFrame) + 88, 113, -87, 113));
		else if (d0 >= 0)
			sprite.setTextureRect(IntRect(64 * int(currentFrame), 0, 64, 108));

		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

		dx = 0;
	}
	void Collision(int dir)
	{
		for (int i = rect.top / 32; i<(rect.top + 110) / 32; i++)
			for (int j = rect.left / 32; j<(rect.left + 50) / 32; j++)
			{
			if ((TileMap[i][j] == 'B') || (TileMap[i][j] == 'A'))
			{
				if ((dx>0) && (dir == 0))rect.left = j * 32 - 50;
				if ((dx<0) && (dir == 0))rect.left = j * 32 + 32;
				if ((dy>0) && (dir == 1)){ rect.top = i * 32 - 110; dy = 0; onGround = true; }
				if ((dy<0) && (dir == 1)){ rect.top = i * 32 + 32; dy = 0; }
			}
			if ((TileMap[i][j] == '1')||(TileMap[i][j] == '2')||(TileMap[i][j] == '3')||(TileMap[i][j] == '4'))
			{
				
				TileMap[i][j] = ' ';
				counter++;
			}
			}
	}

};

int play()
{
	RenderWindow window(VideoMode(1360, 780), "Avatar: The Legend of Korra", Style::Fullscreen);

	Texture t;
	t.loadFromFile("korra.png");

	Texture tileSet;
	tileSet.loadFromFile("TileList.png");
	Sprite tile(tileSet);

	Texture tileSet2;
	tileSet2.loadFromFile("equalist.png");		

	PLAYER p(t);
	ENEMY  enemy;
	enemy.set(tileSet2, 1100, 1400);
	enemy.set(tileSet2, 1100, 1400);

	float currentFrame = 0;
	Clock clock;
	RectangleShape rectangle;

	Music music;
	music.openFromFile("Korra.ogg");
	music.play();

	SoundBuffer buffer;
	buffer.loadFromFile("Jump.ogg");
	Sound sound(buffer);

	int dir, playerScore;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 650;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			p.dx = -0.3;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			p.dx = 0.3;
		}

		if (p.onGround)
			p.d0 = 0.1;

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (p.onGround)
			{
				p.dy = -0.5;
				p.onGround = false;
				sound.play();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		p.update(time);
		enemy.update(time);


		if (p.rect.intersects(enemy.rect))
		{
			if (enemy.life) {
				if (p.dy>0) { enemy.dx = 0; p.dy = -0.2; enemy.life = false; }
				else p.sprite.setColor(Color::Black);
			}
		}
				
		if (p.rect.left > 680)
			offsetX = p.rect.left - 680;
		if (p.rect.top > 390 )
			offsetY = p.rect.top - 490;
		

		window.clear(Color::White);
		rectangle.setSize(Vector2f(32, 32));

		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
			if (TileMap[i][j] == 'R') tile.setTextureRect(IntRect(0, 100, 2680, 1536));
			if (TileMap[i][j] == 'A') tile.setTextureRect(IntRect(0, 32, 32, 32));
			if (TileMap[i][j] == 'B') tile.setTextureRect(IntRect(0, 0, 32, 32));
			if (TileMap[i][j] == '1') tile.setTextureRect(IntRect(32, 0, 32, 32));
			if (TileMap[i][j] == '2') tile.setTextureRect(IntRect(64, 0, 32, 32));
			if (TileMap[i][j] == '3') tile.setTextureRect(IntRect(96, 0, 32, 32));
			if (TileMap[i][j] == '4') tile.setTextureRect(IntRect(128, 0, 32, 32));
			if (TileMap[i][j] == ' ') continue;

			tile.setPosition(j * 32 - offsetX, i * 32 - offsetY);
			window.draw(tile);
			}

		Font font;//шрифт 
		font.loadFromFile("ARIAL.TTF");//передаем нашему шрифту файл шрифта
		Text text("cool", font, 200);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
		text.setColor(Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый

		window.draw(p.sprite);
		window.draw(enemy.sprite);
		window.display();
	}
	return 0;
}