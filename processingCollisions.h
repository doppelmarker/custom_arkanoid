#pragma once
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"

void processCollision(Paddle& paddle, Ball& ball, float& ballLvlSpeed);
void processCollision(Block& block, Ball& ball, int& points, float& ballLvlSpeed);