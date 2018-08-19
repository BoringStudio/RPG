#include "InputAxis.h"

#include "Math.h"

InputAxis::InputAxis(const std::vector<KeyMapping>& mappings) :
	m_mappings(mappings), 
	m_sensitivity(1.0f), 
	m_gravity(1.0f), 
	m_value(0.0f),
	m_range(-1.0f, 1.0f),
	m_defaultValue(0.0f)
{
}

InputAxis::~InputAxis()
{
}

const std::vector<InputAxis::KeyMapping>& InputAxis::getMappings() const
{
	return m_mappings;
}

void InputAxis::setSensitivity(float sensitivity)
{
	m_sensitivity = sensitivity;
}

float InputAxis::getSensitivity() const
{
	return m_sensitivity;
}

void InputAxis::setGravity(float gravity)
{
	m_gravity = gravity;
}

float InputAxis::getGravity() const
{
	return m_gravity;
}

void InputAxis::setValue(float value)
{
	m_value = value;
}

float InputAxis::getValue() const
{
	return m_value;
}

void InputAxis::setRange(const sf::Vector2f & range)
{
	m_range = range;
	m_value = math::clamp(m_value, range.x, range.y);
}

sf::Vector2f InputAxis::getRange() const
{
	return m_range;
}

void InputAxis::setDefaultValue(float value)
{
	m_defaultValue = value;
}

float InputAxis::getDefaultValue() const
{
	return m_defaultValue;
}
