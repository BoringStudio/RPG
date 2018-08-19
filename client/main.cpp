#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "InputManager.h"

int main()
{
	sf::Uint32 windowStyle = sf::Style::Titlebar | sf::Style::Close;
	sf::ContextSettings contextSettings;
	contextSettings.antialiasingLevel = 0;
	sf::RenderWindow window(sf::VideoMode(800, 600), "RPG client", windowStyle, contextSettings);
	window.setVerticalSyncEnabled(true);

	InputAxis axisX({
		{Key::W, 1.0f},
		{Key::S, -1.0f}
	});

	std::map<std::string, InputAxis> axes = {
		{"x", axisX}
	};

	InputManager inputManager(axes);

	sf::Clock timer;
	while (window.isOpen()) {
		float dt = timer.restart().asSeconds();
		
		inputManager.prepareStates();
		
		sf::Event e;
		while (window.pollEvent(e)) {
			inputManager.handleEvent(e);
		}

		inputManager.updateAxes(dt);

		window.clear(sf::Color(30, 30, 30));
		window.display();
	}

	return 0;
}