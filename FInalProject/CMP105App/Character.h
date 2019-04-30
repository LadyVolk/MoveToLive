#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
class Character
{
protected:
	sf::Sprite icon;
	sf::RenderWindow *window;
	sf::Texture texture;
	sf::Vector2f position;
	float speed;
	sf::Clock animation_timer;
	float animation_speed;
	int animation_frame;
	int frame_size;
	float min_speed;
	int animation_direction;

public:
	Character(sf::RenderWindow *_window, float _speed, sf::Vector2f _position,
		string texture_path, sf::Vector2f _scale);
	~Character();

	sf::Vector2f getSize();

	sf::Rect <float> getCollisionShape();

	void updateAnimation();

	float getSpeed();

	void setSpeed(float _speed);
	
	sf::Vector2f getPosition();

	void setPosition(float x, float y);
};

