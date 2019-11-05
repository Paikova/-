#include <SFML/Graphics.hpp>
using namespace sf;

int menuPlayer(RenderWindow & window);
int menu(RenderWindow & window)
{
	Texture menuTextureChoicePlayer, menuTextureLaw, menuTextureExit, menuBackground;
	menuTextureChoicePlayer.loadFromFile("images/ChoicePlayer.png");
	menuTextureLaw.loadFromFile("images/Law.png");
	//menuTextureLaw.loadFromFile("images/фф.png");
	menuTextureExit.loadFromFile("images/Exit.png");
	//aboutTexture.loadFromFile("images/about.png");
	menuBackground.loadFromFile("images/BackGround.jpg");
	Sprite menuChoicePlayer(menuTextureChoicePlayer), menuLaw(menuTextureLaw), menuExit(menuTextureExit), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menuChoicePlayer.setPosition(100, 30);
	menuLaw.setPosition(100, 90);
	menuExit.setPosition(100, 150);
	menuBg.setPosition(345, 0);

	Texture menuTextureLawAbout;
	menuTextureLawAbout.loadFromFile("images/BackGroundMenu.jpg");
	Sprite menuLawAbout(menuTextureLawAbout);

	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menuChoicePlayer.setColor(Color::White);
		menuLaw.setColor(Color::White);
		menuExit.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));
		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menuChoicePlayer.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menuLaw.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menuExit.setColor(Color::Blue); menuNum = 3; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) {
				isMenu = false;
				//RenderWindow window(VideoMode(1200, 740), "Catch it if you can");
				int N = menuPlayer(window);
				return N;
				
			}//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.draw(menuLawAbout); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }
		}
		window.draw(menuBg);
		window.draw(menuChoicePlayer);
		window.draw(menuLaw);
		window.draw(menuExit);
		window.display();
	}
};

int menuPlayer(RenderWindow & window)
{
	std::cout << "aaa";
	Texture menuTexturePlayerBoy, menuTexturePlayerGirl;
	menuTexturePlayerBoy.loadFromFile("images/Boy1menu.png");
	menuTexturePlayerGirl.loadFromFile("images/GirlMenu.png");
	Sprite menuPlayerBoy(menuTexturePlayerBoy);
	Sprite menuPlayerGirl(menuTexturePlayerGirl);
	bool isMenuPlayer = true;
	int menuNumPlayer;
	menuPlayerBoy.setTextureRect(IntRect(0,0,300,385));
	menuPlayerGirl.setTextureRect(IntRect(0,0,256,256));
	menuPlayerBoy.setPosition(10, 10);
	menuPlayerGirl.setPosition(700, 10);


	int player;

	while (isMenuPlayer)
	{
		window.display();
		
		menuPlayerBoy.setColor(Color::White);
		menuPlayerGirl.setColor(Color::White);
		window.clear(Color(129, 181, 221));

		//std::cout << "menu";
		if (IntRect(10, 10, 330, 385).contains(Mouse::getPosition(window))) { menuPlayerBoy.setColor(Color::Blue); menuNumPlayer = 1; }
		if (IntRect(700, 10, 256, 256).contains(Mouse::getPosition(window))) { menuPlayerGirl.setColor(Color::Blue); menuNumPlayer = 2; }

		/*if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNumPlayer == 1) {
				isMenuPlayer = false;
				//RenderWindow window(VideoMode(1200, 740), "Catch it if you can");


			}//если нажали первую кнопку, то выходим из меню 
			if (menuNumPlayer == 2) { isMenuPlayer = false; }

		}*/
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNumPlayer == 1) {

				player = 1;
				isMenuPlayer = false;
				return player;
			}//если нажали первую кнопку, то выходим из меню 
			if (menuNumPlayer == 2) {
				player = 2;
				isMenuPlayer = false;

				return player;
			}

		}
		window.draw(menuPlayerBoy);
		window.draw(menuPlayerGirl);
		//window.display();
	}
	
};