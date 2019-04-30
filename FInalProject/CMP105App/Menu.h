#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
class Menu
{

	sf::RenderWindow* window;
	sf::Sprite intro_image;
	sf::Texture intro_texture;
	sf::Sprite logo_image;
	sf::Texture logo_texture;
	sf::Text start;
	sf::Font font;
	sf::Music music;

public:
	Menu(sf::RenderWindow* window);
	~Menu();


	string handleInput();
	void update();
	void render();

	void stopMusic();
};

