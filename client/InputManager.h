#pragma once

#include <string>
#include <bitset>
#include <map>

#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>

#include "InputAxis.h"

class InputManager
{
public:
	InputManager();
	InputManager(std::map<std::string, InputAxis>& axes);
	~InputManager();

	// Removes delta between last and current state
	void prepareStates();

	// Changes current input state
	// @param e - sfml window event
	void handleEvent(const sf::Event& e);

	// Updates axes values
	// @param dt - frame delta time
	void updateAxes(float dt);


	// @param key
	// @return - if key was pressed since last frame
	bool getKeyDown(Key key);

	// @param key
	// @return - if key was released since last frame
	bool getKeyUp(Key key);

	// @param key
	// @return - if key is currently pressed
	bool getKey(Key key);


	// @return - if any key was pressed since last frame
	bool getAnyKeyDown();

	// @return - if any key was released since last frame
	bool getAnyKeyUp();

	// @return - if any key is currently pressed
	bool getAnyKey();


	// @param name - axis name
	// @return - current axis value
	float getAxis(const std::string& name);


	// @param button - mouse button
	// @return - if mouse button was pressed since last frame
	bool getMouseButtonDown(MouseButton button);

	// @param button - mouse button
	// @return - if mouse button was released since last frame
	bool getMouseButtonUp(MouseButton button);

	// @param button - mouse button
	// @return - if mouse button is currently pressed
	bool getMouseButton(MouseButton button);


	// @return mouse position
	sf::Vector2i getMousePosition() const;

	// @return mouse position delta since last frame
	sf::Vector2i getMousePositionDelta() const;

private:
	std::bitset<Key::KeyCount> m_lastKeyStates;
	std::bitset<Key::KeyCount> m_currentKeyStates;

	std::bitset<MouseButton::ButtonCount> m_lastMouseButtonStates;
	std::bitset<MouseButton::ButtonCount> m_currentMouseButtonStates;

	sf::Vector2i m_lastMousePosition;
	sf::Vector2i m_currentMousePosition;

	std::map<std::string, InputAxis> m_axes;
};
