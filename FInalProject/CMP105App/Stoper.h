#pragma once
#include "Character.h"
#include "Enemy.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;
class Stoper:public Character
{

private:

	int times_activated;
	float speed_decrease;
	sf::SoundBuffer buffer;
	sf::Sound stoper_sfx;

public:
	Stoper(sf::RenderWindow *_window, sf::Vector2f _position,
		string texture_path, sf::Vector2f _scale);
	~Stoper();

	void Draw();
	void Activate(vector<Enemy*> enemies);

	sf::Vector2f getSize();

	int getActivations();
};

