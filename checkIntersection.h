#pragma once
#include "Paddle.h"
#include "Ball.h"

template <class T1, class T2> bool isIntersecting(T1& obj1, T2& obj2);

void processCollision(Paddle& paddle, Ball& ball);