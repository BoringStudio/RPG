#include "InputManager.h"

#include "Math.h"

InputManager::InputManager()
{
}

InputManager::InputManager(std::map<std::string, InputAxis>& axes) :
	m_axes(axes)
{
}

InputManager::~InputManager()
{
}

void InputManager::prepareStates()
{
	m_lastKeyStates = m_currentKeyStates;
	m_lastMouseButtonStates = m_currentMouseButtonStates;
	m_lastMousePosition = m_currentMousePosition;
}

void InputManager::handleEvent(const sf::Event & e)
{
	switch (e.type) {
	case sf::Event::MouseMoved:
		m_currentMousePosition.x = e.mouseMove.x;
		m_currentMousePosition.y = e.mouseMove.y;
		break;

	case sf::Event::KeyPressed:
		if (e.key.code > Key::Unknown && e.key.code < Key::KeyCount) {
			m_currentKeyStates.set(e.key.code, true);
		}
		break;

	case sf::Event::KeyReleased:
		if (e.key.code > Key::Unknown && e.key.code < Key::KeyCount) {
			m_currentKeyStates.set(e.key.code, false);
		}
		break;

	case sf::Event::MouseButtonPressed:
		if (e.mouseButton.button < MouseButton::ButtonCount) {
			m_currentMouseButtonStates.set(e.mouseButton.button, true);
		}
		break;

	case sf::Event::MouseButtonReleased:
		if (e.mouseButton.button < MouseButton::ButtonCount) {
			m_currentMouseButtonStates.set(e.mouseButton.button, false);
		}
		break;
	default:
		break;
	}
}

void InputManager::updateAxes(float dt)
{
	for (auto& it : m_axes) {
		InputAxis& axis = it.second;

		bool pressed = false;
		const float axisValue = axis.getValue();

		for (const auto& mapping : axis.getMappings()) {
			if (!getKey(mapping.first)) continue;

			pressed = true;

			if (math::inRange(axisValue, axis.getRange())) {
				float delta = dt * axis.getSensitivity() * mapping.second;
				axis.setValue(math::clamp(axisValue + delta, axis.getRange()));
			}
		}

		const float defaultValue = axis.getDefaultValue();
		if (!pressed && axisValue != defaultValue) {
			if (axisValue > defaultValue) {
				axis.setValue(math::clampMin(axisValue - dt * axis.getGravity(), defaultValue));
			}
			else {
				axis.setValue(math::clampMax(axisValue + dt * axis.getGravity(), defaultValue));
			}
		}
	}
}

bool InputManager::getKeyDown(Key key)
{
	if (key > Key::Unknown && key < Key::KeyCount) {
		return !m_lastKeyStates.test(static_cast<size_t>(key)) &&
			m_currentKeyStates.test(static_cast<size_t>(key));
	}
	else {
		return false;
	}
}

bool InputManager::getKeyUp(Key key)
{
	if (key > Key::Unknown && key < Key::KeyCount) {
		return m_lastKeyStates.test(static_cast<size_t>(key)) &&
			!m_currentKeyStates.test(static_cast<size_t>(key));
	}
	else {
		return false;
	}
}

bool InputManager::getKey(Key key)
{
	if (key > Key::Unknown && key < Key::KeyCount) {
		return m_currentKeyStates.test(static_cast<size_t>(key));
	}
	else {
		return false;
	}
}

bool InputManager::getAnyKeyDown()
{
	return !m_lastKeyStates.any() && m_currentKeyStates.any();
}

bool InputManager::getAnyKeyUp()
{
	return m_lastKeyStates.any() && !m_currentKeyStates.any();
}

bool InputManager::getAnyKey()
{
	return m_currentKeyStates.any();
}

float InputManager::getAxis(const std::string & name)
{
	const auto it = m_axes.find(name);
	if (it == m_axes.end()) {
		return 0.0f;
	}
	else {
		return it->second.getValue();
	}
}

bool InputManager::getMouseButtonDown(MouseButton button)
{
	return !m_lastMouseButtonStates.test(static_cast<size_t>(button)) &&
		m_currentMouseButtonStates.test(static_cast<size_t>(button));
}

bool InputManager::getMouseButtonUp(MouseButton button)
{
	return m_lastMouseButtonStates.test(static_cast<size_t>(button)) &&
		m_currentMouseButtonStates.test(static_cast<size_t>(button));
}

bool InputManager::getMouseButton(MouseButton button)
{
	return m_currentMouseButtonStates.test(static_cast<size_t>(button));
}

sf::Vector2i InputManager::getMousePosition() const
{
	return m_currentMousePosition;
}

sf::Vector2i InputManager::getMousePositionDelta() const
{
	return m_currentMousePosition - m_lastMousePosition;
}
