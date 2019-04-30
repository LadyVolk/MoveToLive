#include "Menu.h"

Menu::Menu(sf::RenderWindow* _window)
{
	window = _window;

	//inialize music
	if (!music.openFromFile("Assets/Music/ubermensch.wav")) {
		cout << "error loading music" << endl;
	}
	music.setVolume(40);
	music.play();

	logo_texture.loadFromFile("Assets/logo.png");
	logo_image.setTexture(logo_texture);
	logo_image.setScale(0.8, 0.8);
	logo_image.setColor(sf::Color(255, 255, 255));
	logo_image.setPosition(window->getSize().x / 2 - logo_image.getGlobalBounds().width / 2, 20);

	intro_texture.loadFromFile("Assets/intro.png");
	intro_image.setTexture(intro_texture);
	intro_image.setScale(0.8, 0.8);
	intro_image.setColor(sf::Color(255, 255, 255));
	intro_image.setPosition(window->getSize().x / 2 - intro_image.getGlobalBounds().width / 2, 
		logo_image.getGlobalBounds().height + 50);

	//icinialize font
	if (!font.loadFromFile("font/arial.ttf"))
	{
		cout << "error loading font" << endl;
	}

	start.setFont(font);
	start.setCharacterSize(50);
	start.setFillColor(sf::Color(0, 100, 100));
	start.setString("Press enter to start");
	start.setPosition(window->getSize().x / 2 - start.getGlobalBounds().width / 2,
		window->getSize().y - start.getGlobalBounds().height - 50);
}


Menu::~Menu()
{
}

string Menu::handleInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		return "level";
	}
	return "menu";
}

void Menu::update(){

}

void Menu::render(){
	window->draw(intro_image);
	window->draw(logo_image);
	window->draw(start);
}

void Menu::stopMusic() {
	music.stop();
}