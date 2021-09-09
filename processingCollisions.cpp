#include "processingCollisions.h"
#include "checkIntersection.cpp"
#include "sound.h"

void processCollision(Paddle& paddle, Ball& ball, float& ballLvlSpeed)
{
	if (!isIntersecting(paddle, ball)) return;
	//if (ball.x() < paddle.x()) ball.speed.x = -ballSpeedLvl2;
	//else ball.speed.x = ballSpeedLvl2;
	Noise rebound("rebound.wav");
	rebound.sound.play();
	ball.speed.y = -ballLvlSpeed;
}

void processCollision(Block& block, Ball& ball, int& points, float& ballLvlSpeed)
{
	if (!isIntersecting(block, ball)) return;
	++points;
	block.destroyed = true;

	float overlapLeft{ ball.right() - block.left() };
	float overlapRight{ block.right() - ball.left() };
	float overlapTop{ ball.bottom() - block.top() };
	float overlapBottom{ block.bottom() - ball.top() };

	//”знаЄм, в какую четверть пр€моугольника попадЄт шарик.
	bool ballFromLeft{ overlapLeft < overlapRight };
	bool ballFromTop{ overlapTop < overlapBottom };
	//”знаЄм, горизонтально или вертикально м€ч попадает в эту четверть пр€моугольника.
	bool ballHorizontal{float(ballFromLeft ? overlapLeft : overlapRight) < float(ballFromTop ? overlapTop : overlapBottom)};

	if (ballHorizontal)
		ball.speed.x = ballFromLeft ? -ballLvlSpeed : ballLvlSpeed;
	else
		ball.speed.y = ballFromTop ? -ballLvlSpeed : ballLvlSpeed;
}