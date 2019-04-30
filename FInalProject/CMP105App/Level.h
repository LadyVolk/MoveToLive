#pragma once
#include "Vector.h"
#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "Stoper.h"
#include "Coin.h"
#include <iomanip>
#include <sstream>
#include <SFML/Audio.hpp>
using namespace std;
class Level{
private:

	sf::Clock relogio;
	sf::Time dt;
	sf::RenderWindow* window;
	sf::Font font;
	Player* player;
	vector<Enemy*> enemies;
	vector<Stoper*> stopers;
	sf::Sprite background;
	sf::Texture background_texture;
	float time_survived;
	vector <sf::Text> texts;
	bool game_over;
	bool paused;
	bool just_paused;
	sf::Music music;
	sf::SoundBuffer buffer;
	sf::Sound death_sfx;
	sf::SoundBuffer buffer_start;
	sf::Sound start_sfx;
	int initial_enemies;
	float enemy_spawn_time;
	float spawn_cooldown;
	sf::SoundBuffer buffer_chicken;
	sf::Sound chicken_sfx;
	int max_enemies;
	Coin* coin;

public:
	Level(sf::RenderWindow* hwnd);
	~Level();

	void handleInput();
	void update();
	void render();
	void updateDT();

	void checkCollisions();

	void drawBackground();

	sf::Vector2f randomPosition();

	void gameOver();

	void restartGame();

	void togglePause();

	void addEnemy();
};