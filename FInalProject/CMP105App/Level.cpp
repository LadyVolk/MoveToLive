#include "Level.h"
#include "Intersection.h"
#include <iostream>
#include <SFML/System/Vector2.hpp>
using namespace std;

Level::Level(sf::RenderWindow* hwnd)
{

	window = hwnd;

	paused = false;

	just_paused = false;

	initial_enemies = 5;

	spawn_cooldown = 5;

	max_enemies = 15;

	//inialize music
	if (!music.openFromFile("Assets/Music/pentatonic.ogg")) {
		cout << "error loading music" << endl;
	}
	music.setVolume(40);

	//inicialize player death because he dies too fast to work on player script
	if (!buffer.loadFromFile("Assets/Music/die.ogg")) {
		cout << "error loading die sfx" << endl;
	}
	death_sfx.setBuffer(buffer);
	death_sfx.setVolume(50);

	//inicialize chicken sound
	if (!buffer_chicken.loadFromFile("Assets/Music/crow.wav")) {
		cout << "error loading chicken sfx" << endl;
	}
	chicken_sfx.setBuffer(buffer_chicken);
	chicken_sfx.setVolume(100);

	//start/restart sfx
	if (!buffer_start.loadFromFile("Assets/Music/start.wav")) {
		cout << "error loading start sfx" << endl;
	}
	start_sfx.setBuffer(buffer_start);
	start_sfx.setVolume(50);

	// initialise game objects
	if (!font.loadFromFile("font/arial.ttf"))
	{
		cout << "error loading font" << endl;
	}

	//using a vector to store all texts on the game
	//first is the counter
	texts.push_back(sf::Text());

	texts[0].setFont(font);
	texts[0].setCharacterSize(50);
	texts[0].setFillColor(sf::Color::Red);
	texts[0].setString("0");

	//second is the gameover text
	texts.push_back(sf::Text());

	texts[1].setFont(font);
	texts[1].setCharacterSize(100);
	texts[1].setFillColor(sf::Color::Red);

	background_texture.loadFromFile("Assets/grass.png");
	background.setTexture(background_texture);
	background.setColor(sf::Color(255, 255, 255));
	background.setScale(0.1, 0.1);

	//third is stopers activatrion counter
	texts.push_back(sf::Text());

	texts[2].setFont(font);
	texts[2].setCharacterSize(50);
	texts[2].setFillColor(sf::Color::Blue);
	texts[2].setString("");

	//forth is texts to restart game
	texts.push_back(sf::Text());

	texts[3].setFont(font);
	texts[3].setCharacterSize(50);
	texts[3].setFillColor(sf::Color(0, 100, 100));
	texts[3].setString("");

	//fifth is paused game
	texts.push_back(sf::Text());

	texts[4].setFont(font);
	texts[4].setCharacterSize(50);
	texts[4].setFillColor(sf::Color(0, 100, 100));
	texts[4].setString("");

}

Level::~Level()
{
}

// handle user input

void Level::handleInput()
{
	float damage = 0;
	float speed;

	if (player != nullptr) {

		sf::Vector2f move_vector(0, 0);
		speed = player->getSpeed();

		if (!paused) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				move_vector += sf::Vector2f(0, -1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				move_vector += sf::Vector2f(0, 1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				move_vector += sf::Vector2f(-1, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				move_vector += sf::Vector2f(1, 0);
			}
		}
		//pausing game
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && !just_paused) {
			togglePause();
			//avoid game pausing/unpausing due to key being hold
			just_paused = true;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			just_paused = false;
		}

		//normalize vector
		move_vector = Normalize(move_vector);
		
		//heal or decay
		if (move_vector.x == 0 && move_vector.y == 0 && !paused) {
			player->damagePerSec(dt);
		}
		else if(!paused) {
			player->healMove(dt);
		}
		player->Move(move_vector.x * speed * dt.asSeconds(), move_vector.y * speed * dt.asSeconds());
	}

	if (game_over) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			restartGame();
		}
	}
}

// Update game objects
void Level::update()
{
	int i;
	double centerx;
	stringstream sstream, sstream_stopers;

	if (!paused) {

		if (!game_over) {

			time_survived += dt.asSeconds();

			enemy_spawn_time += dt.asSeconds();

			//adding time to a string, not as easy was i expected
			sstream << fixed << setprecision(4) << time_survived;
			texts[0].setString(sstream.str());
			centerx = window->getSize().x / 2.0;
			texts[0].setPosition(centerx - texts[0].getGlobalBounds().width / 2.0, 5);

			//enemy spawn over time
			while (enemy_spawn_time >= spawn_cooldown && enemies.size() < max_enemies) {
				enemy_spawn_time -= spawn_cooldown;
				addEnemy();
				chicken_sfx.play();
			}
			coin->Update(dt.asSeconds());
		}

		//death by not moving
		if (player != nullptr && player->getHealth() <= 0) {
			gameOver();
		}
		if (player != nullptr) {
			player->Update(dt.asSeconds());
		}
		//update all enemies
		for (i = 0; i < enemies.size(); i++) {
			enemies[i]->Update(dt.asSeconds());
		}
		//check collisions
		if (player != nullptr) {
			checkCollisions();
		}
	}	
}

// Render level
void Level::render()
{
	int i;

	drawBackground();

	//drawing stopers
	for (i = 0; i < stopers.size(); i++) {
		stopers[i]->Draw();
	}
	//drawing coin
	if (coin != nullptr) {
		coin->Draw();
	}
	//drawing enemies
	for (i = 0; i < enemies.size(); i++) {
		enemies[i]->Draw();
	}
	//drawing player
	if (player != nullptr) {
		player->Draw();
	}
	//drawing text
	for (i = 0; i < texts.size(); i++) {
		window->draw(texts[i]);
	}
}


void Level::updateDT() {
	dt = relogio.restart();
}

void Level::checkCollisions() {
	int i;

	//stoper collision
	for (i = 0; i < stopers.size(); i++) {
		if (rectWithRect(stopers[i]->getCollisionShape(), player->getCollisionShape())) {
			stopers[i]->Activate(enemies);
		}
	}
	//coin collision
	if (coin->getCanUse() &&
		rectWithRect(coin->getCollisionShape(), player->getCollisionShape())) {
		coin->Activate(player);
	}
	//enemies collision
	for (i = 0; i < enemies.size(); i++) {
		if (rectWithRect(enemies[i]->getCollisionShape(), player->getCollisionShape()) &&
			!player->isInvincible()) {
			gameOver();
			break;
		}
	}
}

void Level::drawBackground() {
	float x = 0, y = 0;
	//tiling the background with several copies of the same sprite
	while (y < window->getSize().y) {
		background.setPosition(x, y);
		window->draw(background);
		x += background.getGlobalBounds().width;
		if (x > window->getSize().x) {
			y += background.getGlobalBounds().height;
			x = 0;
		}
	}
}

sf::Vector2f Level::randomPosition() {
	bool works = false;
	float random_number_x, random_number_y;
	sf::Vector2f random_vector;

	while (!works) {
		
		random_number_x = rand() % window->getSize().x;
		random_number_y = rand() % window->getSize().y;

		random_vector.x = 0;
		random_vector.y = 0;

		if (random_number_x > window->getSize().x - 200 || random_number_x < 200) {
			random_vector.x = random_number_x;
		}
		if (random_number_y > window->getSize().y - 200 || random_number_y < 200) {
			random_vector.y = random_number_y;
		}
		if (random_vector.x != 0 && random_vector.y != 0) {
			works = true;
			return random_vector;
		}
	}
}

void Level::gameOver() {

	double centerx, centery, gap, height0, height1, height2, height3, y;

	string score, activations;
	
	int i;

	//removing player
	player->kill();
	delete player;
	player = nullptr;

	game_over = true;

	//player death sound
	death_sfx.play();
	
	//text for all the game over
	texts[1].setString("YOU LOST, KIDDO");

	texts[3].setString("Press 'r' to start again");

	score = "Your score is: ";
	score.append(texts[0].getString());
	texts[0].setString(score);

	activations = " Times you activated the stop sign: ";
	activations.append(to_string(stopers[0]->getActivations()));
	texts[2].setString(activations);

	centerx = window->getSize().x / 2.0;
	centery = window->getSize().y / 2.0;

	//getting the height of texts
	height0 = texts[0].getGlobalBounds().height;
	height1 = texts[1].getGlobalBounds().height;
	height2 = texts[2].getGlobalBounds().height;
	height3 = texts[3].getGlobalBounds().height;
	gap = 20;
	y = centery - ((height1 + height0 + height2 + height3 + 3*gap) / 2.0);

	texts[1].setPosition(centerx - texts[1].getGlobalBounds().width / 2.0, y);

	//setting counter text for end game
	y += height1 + gap;
	texts[0].setPosition(centerx - texts[0].getGlobalBounds().width / 2.0, y);
	
	//set stopers texts position
	y += height2 + gap;
	texts[2].setPosition(centerx - texts[2].getGlobalBounds().width / 2.0, y);

	//texts about restarting game
	y += height3 + gap;
	texts[3].setPosition(centerx - texts[3].getGlobalBounds().width / 2.0, y);

	//clear the enemies from game
	for (i = 0; i < enemies.size(); i++) {
		delete enemies[i];
	}
	enemies.clear();

	//clear stopers from game
	for (i = 0; i < enemies.size(); i++) {
		delete stopers[i];
	}

	stopers.clear();

	delete coin;
	coin = nullptr;

	music.stop();
}

void Level::restartGame() {
	int i;

	double centerx;

	game_over = false;

	//used to draw time alive on top
	time_survived = 0;

	relogio.restart();

	enemy_spawn_time = 0;

	music.play();
	start_sfx.play();

	//initialize player
	player = new Player(window, 600, sf::Vector2f(550, 400),
		"Assets/pug.png", sf::Vector2f(1.5, 1.5));

	//initialize coin
	coin = new Coin(window, player, "Assets/coin.png", sf::Vector2f(1, 1));

	for (i = 0; i < initial_enemies; i++) {
		addEnemy();
	}

	stopers.push_back(new Stoper(window, sf::Vector2f(600, 600), "Assets/stop.png",
		sf::Vector2f(1.5, 1.5)));

	centerx = window->getSize().x / 2.0;
	texts[0].setPosition(centerx - texts[0].getGlobalBounds().width / 2.0, 5);

	//reset the game over text
	for (i = 1; i != texts.size(); i++) {
		texts[i].setString("");
	}
}

void Level::togglePause() {
	double centerx, centery;

	paused = !paused;
	if (paused) {
		centerx = window->getSize().x / 2.0;
		centery = window->getSize().y / 2.0;

		music.pause();

		texts[4].setString("Game is paused, Kiddo");
		texts[4].setPosition(centerx - texts[4].getGlobalBounds().width / 2.0, 
			centery - texts[4].getGlobalBounds().height / 2.0);
	}
	else {

		music.play();

		texts[4].setString("");
	}
}

void Level::addEnemy() {
	Enemy* proto_enemy;
	bool works = false;
	//create enemy and check if it doesnt collisides with player on inicial position
	while (!works) {
		proto_enemy = new Enemy(window, 100, randomPosition(), "Assets/chicken.png", sf::Vector2f(2, 2));
		if (!rectWithRect(proto_enemy->getCollisionShape(), player->getCollisionShape())) {
			works = true;
		}
	}
	enemies.push_back(proto_enemy);
}