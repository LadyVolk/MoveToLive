// Main
// Entry point of the application.
// Handles window creation and window events.
// Contains the game loop, updates input class and contains the level objects.
// @author Paul Robertson

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Level.h"
#include <stdlib.h>
#include <time.h>
#include "Menu.h"

void beginDraw(sf::RenderWindow* _window);
void endDraw(sf::RenderWindow* _window);


int main()
{
	string game_state = "menu";

	//randomize 
	srand(time(NULL));

	//Create the window
	sf::RenderWindow window(sf::VideoMode(1200, 800), "MoveToLive", sf::Style::Titlebar | sf::Style::Close);

	//initialise menu
	Menu menu(&window);

	// Initialise input and level objects.
	Level level(&window);

	// Game Loop
	while (window.isOpen())
	{
		// Handle window events.
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
				break;
			default:
				// don't handle other events
				break;
			}
		}

		if (game_state == "level") {
			//update of delta time
			level.updateDT();
			level.handleInput();
			level.update();
			beginDraw(&window);
			level.render();
			endDraw(&window);
		}
		else if(game_state == "menu") {
			game_state = menu.handleInput();
			if (game_state == "level") {
				level.restartGame();
				menu.stopMusic();
			}
			menu.update();
			beginDraw(&window);
			menu.render();
			endDraw(&window);
		}
	}

}
void beginDraw(sf::RenderWindow* _window)
{
	_window->clear(sf::Color(0, 0, 0));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void endDraw(sf::RenderWindow* _window)
{
	_window->display();
}

