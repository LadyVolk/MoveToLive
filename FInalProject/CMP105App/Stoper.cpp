#include "Stoper.h"
#include "Character.h"
#include <stdlib.h>

Stoper::Stoper(sf::RenderWindow *_window, sf::Vector2f _position,
	string texture_path, sf::Vector2f _scale):Character(_window, 0, _position, texture_path, _scale)
{
	times_activated = 0;
	speed_decrease = 150;

	//inicialize stoper sfx
	if (!buffer.loadFromFile("Assets/Music/stoper.ogg")) {
		cout << "error loading stoper sfx" << endl;
	}
	stoper_sfx.setBuffer(buffer);
	stoper_sfx.setVolume(80);
}


Stoper::~Stoper()
{
}

void Stoper::Draw() {
	icon.setPosition(getPosition());
	window->draw(icon);
}

sf::Vector2f Stoper::getSize() {
	return sf::Vector2f(icon.getGlobalBounds().width, icon.getGlobalBounds().height);
}

void Stoper::Activate(vector<Enemy*> enemies) {
	int i;
	Enemy* e;
	times_activated++;
	stoper_sfx.play();
	for (i = 0; i < enemies.size(); i++) {
		e = enemies[i];
		e->setSpeed(e->getSpeed()-speed_decrease);
		if (e->getSpeed() < min_speed) {
			e->setSpeed(min_speed);
		}
	}
	setPosition(rand() % (int)(window->getSize().x - getSize().x),
		rand() % (int)(window->getSize().y - getSize().y));
}

int Stoper::getActivations() {
	return times_activated;
}