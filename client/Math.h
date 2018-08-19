#pragma once

#include <SFML/System/Vector2.hpp>

namespace math
{
	bool inRange(float value, float min, float max);
	bool inRange(float value, const sf::Vector2f& range);

	float clamp(float value, float min = 0.0f, float max = 1.0f);
	float clamp(float value, const sf::Vector2f& range);

	float clampMin(float value, float min);
	float clampMax(float value, float max);
}