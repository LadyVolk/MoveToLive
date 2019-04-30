#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include "Character.h"
class Player: public Character 
{
	//variables health
	float health;
	float max_health;
	float decay_speed;
	float heal_speed;
	float bar_wide;
	sf::RectangleShape health_bar;
	bool death;
	float invincible;

public:
	Player(sf::RenderWindow *_window, float _speed, sf::Vector2f _position,
		string texture_path, sf::Vector2f _scale);
	~Player();

	void Draw();
	void Update(float dt);
	void Move(float dx, float dy);
	float getSpeed();
	void drawHealthBar(sf::RenderWindow *window);
	void damagePerSec(sf::Time _dt);
	void healMove(sf::Time _dt);
	float getHealth();
	void kill();
	bool isDead();
	bool isInvincible();
	void modInvincibleTime(float time);
};

