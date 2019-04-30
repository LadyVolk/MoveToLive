#include "Player.h"
#include <iostream>
#include <SFML/System/Vector2.hpp>
using namespace std;
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3


Player::Player(sf::RenderWindow *_window, float _speed, sf::Vector2f _position,
	string texture_path, sf::Vector2f _scale) :Character(_window, _speed, _position, texture_path, _scale)
{	

	max_health = 100;
	health = max_health;
	bar_wide = getSize().x;
	decay_speed = 50;
	heal_speed = 55;

	invincible = 0;

	death = false;

	animation_direction = RIGHT;

	//health bar
	health_bar.setFillColor(sf::Color(0, 0, 255));
	health_bar.setSize(sf::Vector2f(getSize().x, getSize().y/3));
	
}


Player::~Player()
{
}

void Player::Draw() {
	if (death)
		return;
	if (isInvincible()) {
		icon.setColor(sf::Color(255, 0, 0));
	}
	else {
		icon.setColor(sf::Color(255, 255, 255));
	}
	icon.setTextureRect(sf::IntRect(frame_size*animation_frame, frame_size*animation_direction, frame_size, frame_size));
	window->draw(icon);
	drawHealthBar(window);
}

void Player::Update(float dt) {
	if (death)
		return;
	icon.setPosition(position.x, position.y);
	updateAnimation();
	if (invincible < 0) {
		invincible += dt;
		if (invincible >= 0) {
			invincible = 0;
		}
	}
}

//change player position
void Player::Move(float dx, float dy) {
	position.x += dx;
	position.y += dy;

	if (position.y < 0) {
		position.y = 0;
	}
	if (position.y > window->getSize().y - getSize().y) {
		position.y = window->getSize().y - getSize().y;
	}
	if (position.x < 0) {
		position.x = 0;
	}
	if (position.x > window->getSize().x - getSize().x) {
		position.x = window->getSize().x - getSize().x;
	}

	if (abs(dy) > abs(dx)) {
		if (dy < 0) {
			animation_direction = UP;
		}
		else {
			animation_direction = DOWN;
		}
	}
	else  {
		if (dx < 0) {
			animation_direction = LEFT;
		}
		else {
			animation_direction = RIGHT;
		}
	}
}

float Player::getSpeed() {
	return speed;
}


// health bar
void Player::drawHealthBar(sf::RenderWindow *window) {
	health_bar.setPosition(position.x, position.y - health_bar.getSize().y - 5);
	health_bar.setSize(sf::Vector2f(bar_wide*(health/max_health), health_bar.getSize().y));
	window->draw(health_bar);
}

void Player::damagePerSec(sf::Time _dt) {
	float decay = decay_speed * _dt.asSeconds();
	health -= decay;
	if (health < 0) {
		health = 0;
	}
}

void Player::healMove(sf::Time _dt) {
	float heal = heal_speed * _dt.asSeconds();
	health += heal;
	if (health > max_health) {
		health = max_health;
	}
}

float Player::getHealth() {
	return health;
}

//dying
void Player::kill() {
	if (death)
		return;
	death = true;
}

bool Player::isDead() {
	return death;
}

//invinsibility
bool Player::isInvincible() {
	if (invincible != 0) {
		return true;
	}
	else
		return false;
}

void Player::modInvincibleTime(float time) {
	invincible -= time;
}