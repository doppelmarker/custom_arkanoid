#pragma once
#include <SFML/Graphics.hpp>
#include "constants.h"
using namespace sf;

struct Paddle
{
	RectangleShape shape;
	Vector2f speed;
	Paddle(float x, float y, float paddleLvlWidth)
	{
		shape.setPosition(x, y);
		shape.setSize({ paddleLvlWidth, paddleHeight });
		shape.setFillColor(Color::Yellow);
		shape.setOrigin(paddleLvlWidth / 2, paddleHeight / 2);
	}
	void update(float& paddleLvlSpeed)
	{
		shape.move(speed);
		
		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() >= 0) speed.x = -paddleLvlSpeed;
		else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && right() <= windowWidth) speed.x = paddleLvlSpeed;
		else speed.x = 0;
	}
	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getSize().x / 2; }
	float right() { return x() + shape.getSize().x / 2; }
	float top() { return y() - shape.getSize().y / 2; }
	float bottom() { return y() + shape.getSize().y / 2; }
};