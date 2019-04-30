#include "Coin.h"



Coin::Coin(sf::RenderWindow *_window, Player* player,
	string texture_path, sf::Vector2f _scale):Character(_window, 0, sf::Vector2f(), texture_path, _scale)
{
	invincible_time = 3;

	can_use = true;

	SafeRandomPosition(player);

	cooldown = 10;

	out_of_game = 0;
}


Coin::~Coin()
{
}

void Coin::Draw() {
	if (can_use) {
		icon.setPosition(getPosition());
		window->draw(icon);
	}
}

sf::Vector2f Coin::getSize() {
	return sf::Vector2f(icon.getGlobalBounds().width, icon.getGlobalBounds().height);
}

void Coin::Activate(Player* player) {
	can_use = false;
	SafeRandomPosition(player);
	out_of_game -= cooldown;
	
	player->modInvincibleTime(invincible_time);
}

bool Coin::getCanUse() {
	return can_use;
}

void Coin::SafeRandomPosition(Player* player) {
	sf::Vector2f random_position;

	bool works = false;

	while (!works) {
		random_position.x = rand() % (int)(window->getSize().x - getSize().x);
		random_position.y = rand() % (int)(window->getSize().y - getSize().y);

		setPosition(random_position.x, random_position.y);

		if (!rectWithRect(getCollisionShape(), player->getCollisionShape())) {
			works = true;
		}
	}
}

void Coin::Update(float dt) {
	if (out_of_game == 0) {
		return;
	}
	out_of_game += dt;
	if (out_of_game >= 0) {
		can_use = true;
		out_of_game = 0;
	}
}