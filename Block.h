#pragma once
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "colorGenerator.h"

using namespace sf;

struct Block
{
	RectangleShape shape;
	bool destroyed{ false };
	Block(float x, float y)
	{
		shape.setPosition(x, y);
		shape.setSize({ blockWidth, blockHeight });
		shape.setFillColor(colorGenerator());
		shape.setOrigin(blockWidth / 2, blockHeight / 2);
	}
	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getSize().x / 2; }
	float right() { return x() + shape.getSize().x / 2; }
	float top() { return y() - shape.getSize().y / 2; }
	float bottom() { return y() + shape.getSize().y / 2; }
};