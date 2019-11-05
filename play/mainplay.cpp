#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <list>
#include <vector>
#include "menu.h"


using namespace sf;
using namespace std;

class Basic
{
public:
	float x,y,w, h, dx, dy, speed, moveTimer;
	float xMap=500, yMap=550, xMapa = 0, yMapa = 50;;
	bool life;
	int dir=0;

	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	String name;
	Basic(Image image, float X, float Y, float W, float H)
	{
		x = X;
		y = Y;
		w = W;
		h = H;
		
		moveTimer = 0;
		speed = 0;
		dx = 0;
		dy = 0;
		life = true;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
		
	}
	virtual void update (float time)=0;
	
};



class Player : public Basic
{
public:
	Player(Image image, float X, float Y, float W, float H):Basic(image, X, Y, W, H)
	{
		sprite.setPosition(xMap, yMap);

		sprite.setTextureRect(IntRect(x, y, w, h));
		
		
	}
	float dressSprite = 0;
	int point = 0;
	void control(float time)
	{
		if (Keyboard::isKeyPressed) 
		{
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				dir = 1;
				speed = 0.2;
				sprite.setScale(1, 1);
				dressSprite += 0.009*time;
				if (dressSprite > 3)
					dressSprite -=3;
				sprite.setTextureRect(IntRect(int(dressSprite)*w, y, w, h));
			}
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				dir = 2;
				speed = 0.2;
				sprite.setScale(-1, 1);
				dressSprite += 0.009*time;
				if (dressSprite > 3)
					dressSprite -= 3;
				sprite.setTextureRect(IntRect(w*int(dressSprite), y, w, h));
			}
		}
		
	}
	void update(float time)
	{
		control(time);
		
		if (dir == 1)
		{
			dx = speed;
			
			
		}
		if (dir == 2)
		{
			dx = -speed;
			
		}
		xMap += dx * time;
		if (xMap < 0)
			xMap = 0;
		else if (xMap > 1200)
			xMap = 1200;
		//y += dy * time;
		//sprite.setPosition(xMap + w / 2, y + h / 2);
		sprite.setPosition(xMap , yMap);
		//dir = 0;
		speed = 0;
		dx = 0;




	}

};
class Enemy :public Basic
{
public:
	Enemy(Image &image, float X, float Y, int W, int H) :Basic(image, X, Y, W, H)
	{
		xMapa = 20 + rand() % (1161), yMapa = 50;
		sprite.setPosition(xMapa, yMapa);
		sprite.setTextureRect(IntRect(0, 0, w, h));
		dy = 0.09;
	}
	void update(float time)
	{
		yMapa += dy * time;
		if (yMapa > 650)
		{
			yMapa = 650;
			//sprite.setColor(Color(255, 255, 255, 0));
			life = false;
		}
		sprite.setPosition(xMapa + w / 2, yMapa+ h / 2);
	}
	void color()
	{
		sprite.setColor(Color(255, 255, 255, 0));
	}
};




int main()
{
	RenderWindow window(VideoMode(1200, 700), "Catch it if you can");
	int NumberPlayer;
	NumberPlayer = menu(window);
	std::cout << NumberPlayer;
	Clock clock;
	Clock ClockLife;

	Font font; 
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 50);
	//text.setColor(Color(237, 28, 36, 255));
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	Image ImagePlayer;
	int x = 0, y = 0, w = 200, h = 100;


	if (NumberPlayer == 1)
	{
		ImagePlayer.loadFromFile("images/boy(1).png");
		x = 0;
		y = 0;
		w = 267;
		h = 333;

	}
	else
	{
		if (NumberPlayer == 2)
		{
			ImagePlayer.loadFromFile("images/girl(1).png");
			x = 0;
			y = 0;
			w = 259;
			h = 255;

		}
	}
	//ImagePlayer.loadFromFile("images/Boy3.png");
	Player player(ImagePlayer, x, y, w, h);
	Image imageEnemy;
	imageEnemy.loadFromFile("images/cat(1).png");
	
	vector<Enemy*> vectorEnemy(5);
	for (auto& unit : vectorEnemy)
		unit = new Enemy(imageEnemy, 0, 0, 49, 35);

	 
	

	/*Enemy enemy1(imageEnemy, 0, 0, 49, 35);
	Enemy enemy2(imageEnemy, 0, 0, 49, 35);
	Enemy enemy3(imageEnemy, 0, 0, 49, 35);
	Enemy enemy4(imageEnemy, 0, 0, 49, 35);
	Enemy enemy5(imageEnemy, 0, 0, 49, 35);*/
	
	Texture texFon;
	texFon.loadFromFile("images/BackGroundPlay.jpg");
	Sprite spriteFon(texFon);
	

	

	int N = 0;
	int i = 0;
	int nenado=0;
	while (window.isOpen())
	{
		window.clear();
		window.draw(spriteFon);
		float time = clock.getElapsedTime().asMicroseconds();
		float timeEnemy = ClockLife.getElapsedTime().asMicroseconds();
		//cout << timeEnemy<<endl;
		clock.restart();

		time = time / 800;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Tab))
		{
			menu(window);

		};
		
	
		
		player.update(time);
		

		
		window.draw(player.sprite);
		

		

		if (int(timeEnemy) > 1 && int(timeEnemy) < 15)
		{
			vectorEnemy[i]->update(time);
			window.draw(vectorEnemy[i]->sprite);
			if ((vectorEnemy[i]->yMapa > (player.yMap - (player.h) / 2)) && (vectorEnemy[i]->yMapa < (player.yMap + (player.h) / 2)) && (vectorEnemy[i]->xMapa > (player.xMap - (player.w) / 2)) && (vectorEnemy[i]->xMapa < (player.xMap + (player.w) / 2)))
			{
				vectorEnemy[i]->color();
				if (vectorEnemy[i]->life)
				{
					player.point++;
					vectorEnemy[i]->life = false;
				}

			}
			
		}
		if (timeEnemy == 5.0)
		{
			i++;
			timeEnemy = 0;
		}
	

		N++;
		
		
		ostringstream playerPointString;    // объ€вили переменную
		playerPointString << player.point;
		text.setString("ќчки: "+ playerPointString.str());
		text.setPosition(50, 50);
		window.draw(text);
			
		window.display();
	}


	return 0;
}

/*for (int i = 0;i < vectorEnemy.size();i++) {
			if (timeEnemy > 1)
			{
				window.draw(vectorEnemy[i]->sprite);
				timeEnemy = 0;
			}//рисуем entities объекты (сейчас это только враги)
		}*/

