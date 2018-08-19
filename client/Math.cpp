#include "Math.h"

bool math::inRange(float value, float min, float max)
{
	return value > min && value < max;
}

bool math::inRange(float value, const sf::Vector2f & range)
{
	return value > range.x && value < range.y;
}

float math::clamp(float value, float min, float max)
{
	if (value > max) {
		return max;
	}
	
	if (value < min) {
		return min;
	}

	return value;
}

float math::clamp(float value, const sf::Vector2f & range)
{
	if (value > range.y) {
		return range.y;
	}

	if (value < range.x) {
		return range.x;
	}

	return value;;
}

float math::clampMin(float value, float min)
{
	if (value < min) {
		return min;
	}

	return value;
}

float math::clampMax(float value, float max)
{
	if (value > max) {
		return max;
	}

	return value;
}
