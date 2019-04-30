#pragma once
#include "Character.h"
#include "Player.h"
#include "Intersection.h"
class Coin:public Character
{
private:

	float invincible_time;

	bool can_use;

	sf::Texture texture;

	float cooldown;

	float out_of_game;

public:
	Coin(sf::RenderWindow *_window, Player* player,
		string texture_path, sf::Vector2f _scale);
	~Coin();

	sf::Vector2f getSize();

	void Draw();

	void Activate(Player* player);

	bool getCanUse();

	void SafeRandomPosition(Player* player);

	void Update(float dt);
};

