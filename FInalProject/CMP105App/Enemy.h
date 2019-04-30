#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "Character.h"
class Enemy: public Character 
{
private:
	
	sf::Vector2f direction;

	float speed_increase;


public:
	Enemy(sf::RenderWindow *_window, float _speed, sf::Vector2f _position,
		string texture_path, sf::Vector2f _scale);
	~Enemy();

	void Draw();
	void Update(float _dt);
	
	sf::Rect <float> getCollisionShape();
};

