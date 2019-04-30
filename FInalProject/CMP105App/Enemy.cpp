#include "Enemy.h"
#include "Vector.h"
#include <iostream>
using namespace std;
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define DEBUG false

Enemy::Enemy(sf::RenderWindow *_window, float _speed, sf::Vector2f _position,
	string texture_path, sf::Vector2f _scale):Character(_window, _speed, _position, texture_path, _scale)
{
	speed_increase = 70;
	direction = RandomVectorN();

	if (abs(direction.y) > abs(direction.x)) {
		if (direction.y < 0) {
			animation_direction = UP;
		}
		else {
			animation_direction = DOWN;
		}
	}
	else  {
		if (direction.x < 0) {
			animation_direction = LEFT;
		}
		else {
			animation_direction = RIGHT;
		}
	}
	
}


Enemy::~Enemy()
{
}

void Enemy::Draw() {

	sf::Rect <float> hit_box;

	sf::RectangleShape hit_box_object;


	icon.setTextureRect(sf::IntRect(frame_size*animation_frame, frame_size * animation_direction,
		frame_size, frame_size));
	window->draw(icon);
	
	if (DEBUG) {
		hit_box = getCollisionShape();

		hit_box_object.setSize(sf::Vector2f(hit_box.width, hit_box.height));
		hit_box_object.setPosition(hit_box.left, hit_box.top);
		hit_box_object.setFillColor(sf::Color(200, 100, 100, 200));

		window->draw(hit_box_object);
	}
}

void Enemy::Update(float _dt) {
	
	speed += speed_increase * _dt;

	position.x += direction.x * speed * _dt;
	position.y += direction.y * speed * _dt;

	//hits top wall
	if (position.y < 0) {
		position.y = 0;
		direction.y = -direction.y;
		animation_direction = DOWN;
	}
	//hits bottom wall
	if (position.y > window->getSize().y - getSize().y) {
		position.y = window->getSize().y - getSize().y;
		direction.y = -direction.y;
		animation_direction = UP;
	}
	//hits left wall
	if (position.x < 0) {
		position.x = 0;
		direction.x = -direction.x;
		animation_direction = RIGHT;
	}
	//hits right wall
	if (position.x > window->getSize().x - getSize().x) {
		position.x = window->getSize().x - getSize().x;
		direction.x = -direction.x;
		animation_direction = LEFT;
	}
	icon.setPosition(position.x, position.y);

	updateAnimation();
}

//create hitbox smaller than sprite of chicken
sf::Rect <float> Enemy::getCollisionShape() {
	float scale = 0.5;
	float x_hitbox, y_hitbox;
	sf::Vector2f w_h = getSize();
	x_hitbox = position.x + (w_h.x - (w_h.x*scale)) / 2;
	y_hitbox = position.y + (w_h.y - (w_h.y*scale)) / 2;
	return sf::Rect <float>(x_hitbox, y_hitbox, w_h.x*scale, w_h.y*scale);
}