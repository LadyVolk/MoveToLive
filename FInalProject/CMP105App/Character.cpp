#include "Character.h"
#include <string>
#include <iostream>
using namespace std;

Character::Character(sf::RenderWindow *_window, float _speed, sf::Vector2f _position, 
	string texture_path, sf::Vector2f _scale)
{

	window = _window;

	speed = _speed;

	position = _position;

	if (!texture.loadFromFile(texture_path)) {
		cout << "error loading " << texture_path << endl;;
	}

	icon.setTexture(texture);

	icon.setScale(_scale.x, _scale.y);

	icon.setColor(sf::Color(255, 255, 255));

	animation_speed = 10;

	animation_timer.restart();

	animation_frame = 0;

	frame_size = 32;

	min_speed = 50;
}


Character::~Character()
{
}

sf::Vector2f Character::getSize() {

	sf::Vector2f rectangle_sizes, scale;

	scale = icon.getScale();

	rectangle_sizes.x = scale.x * frame_size;
	rectangle_sizes.y = scale.y * frame_size;

	return rectangle_sizes;
}

sf::Rect <float> Character::getCollisionShape() {
	sf::Vector2f w_h = getSize();
	return sf::Rect <float>(position.x, position.y, w_h.x, w_h.y);
}

void Character::updateAnimation() {
	if (1.0/animation_speed <= animation_timer.getElapsedTime().asSeconds()) {
		animation_frame = (animation_frame + 1) % 3;
		animation_timer.restart();
	}
}

float Character::getSpeed() {
	return speed;
}

void Character::setSpeed(float _speed) {
	speed = _speed;
}

sf::Vector2f Character::getPosition() {
	return position;
}

void Character::setPosition(float x, float y) {
	position.x = x;
	position.y = y;
}
