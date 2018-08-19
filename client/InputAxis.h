#pragma once

#include <string>
#include <vector>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

using Key = sf::Keyboard::Key;
using MouseButton = sf::Mouse::Button;

class InputAxis
{
public:
	using KeyMapping = std::pair<Key, float>;

	InputAxis(const std::vector<KeyMapping>& mappings);
	~InputAxis();

	const std::vector<KeyMapping>& getMappings() const;

	void setSensitivity(float sensitivity);
	float getSensitivity() const;

	void setGravity(float gravity);
	float getGravity() const;

	void setValue(float value);
	float getValue() const;

	void setRange(const sf::Vector2f& range);
	sf::Vector2f getRange() const;

	void setDefaultValue(float value);
	float getDefaultValue() const;

private:
	std::vector<KeyMapping> m_mappings;

	float m_sensitivity;
	float m_gravity;
	float m_value;

	sf::Vector2f m_range;
	float m_defaultValue;
};