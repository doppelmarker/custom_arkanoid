#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "constants.h"
using namespace sf;

struct Ball
{
	CircleShape shape;
	//Vector2f speed{ -6.f, -6.f };
	Vector2f speed{ 0.f, 0.f };

	Ball(float x, float y)
	{
		shape.setPosition(x, y);
		shape.setRadius(radius);
		shape.setFillColor(Color::Green);
		shape.setOrigin(radius, radius);
	}
	bool update(Paddle& paddle, bool& continueGame, float& ballLvlSpeed)
	{
		shape.move(speed);

		if (!continueGame)
		{
			if (!speed.y)
				speed.x = paddle.speed.x;
		}
		else
		{
			speed.y = -ballLvlSpeed;
			if (shape.getPosition().x < windowWidth / 2.f)
				speed.x = -ballLvlSpeed;
			else speed.x = ballLvlSpeed;
			continueGame = false;
		}

		if (left() <= 0) speed.x = ballLvlSpeed;
		else if (right() >= windowWidth) speed.x = -ballLvlSpeed;
		if (top() <= 0) speed.y = ballLvlSpeed;
		else if (bottom() >= windowHeight) return false;
		return true;
	}
	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getRadius(); }
	float right() { return x() + shape.getRadius(); }
	float top() { return y() - shape.getRadius(); }
	float bottom() { return y() + shape.getRadius(); }
};