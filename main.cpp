#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
//#include "SFML/OpenGL.hpp";
#include <Windows.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>

#include "constants.h"
#include "Interface.h"
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "processingCollisions.h"
#include "message.h"
#include "sound.h"
#include "DataValidation.h"
//#include <gl/GL.h>

using namespace sf;
using namespace std;

bool startGame(int& mode)
{
	float ballLvlSpeed, paddleLvlSpeed, paddleLvlWidth;
	switch (mode)
	{
	case 1:
		ballLvlSpeed = ballSpeedLvl1;
		paddleLvlSpeed = paddleSpeed;
		paddleLvlWidth = paddleWidthLvl1;
		break;
	case 2:
		ballLvlSpeed = ballSpeedLvl2;
		paddleLvlSpeed = paddleSpeed;
		paddleLvlWidth = paddleWidthLvl2;
		break;
	case 3:
		ballLvlSpeed = ballSpeedLvl3;
		paddleLvlSpeed = paddleSpeedLvl3;
		paddleLvlWidth = paddleWidthLvl3;
		break;
	}
	vector<Block> blocks;
	for (int i = 0; i < countBlocksX; ++i)
		for (int j = 0; j < countBlocksY; ++j)
			blocks.emplace_back((i + 1)*(blockWidth + 3) + 22, (j + 2)*(blockHeight + 3));
	Ball ball(windowWidth / 2.f, 730.f);
	Paddle paddle(windowWidth / 2.f, 750.f, paddleLvlWidth);

	Interface::begin();

	RenderWindow window({ windowWidth, windowHeight }, "MyArkanoid   FPS: ");
	window.setFramerateLimit(60);

	int hp{ 3 };
	int points{ 0 };
	Message score("Score: " + to_string(points)+". Nice try though.", "sweet purple.ttf", 100, windowWidth / 2.f, windowHeight / 2.f - 50.f);
	Message again("Wanna restart?", "sweet purple.ttf", 100, windowWidth / 2.f, windowHeight / 2.f + 50.f);
	Message pressEsc1("<Press ESC to leave>", "sweet purple.ttf", 50, 300.f, windowHeight - 50.f);
	Message pressEsc2("<Press ESC to leave>", "sweet purple.ttf", 50, windowWidth / 2.f, windowHeight - 50.f);
	Message pressEnter("<Press ENTER to restart>", "sweet purple.ttf", 50, 700.f, windowHeight - 50.f);
	Message healpoints("Healpoints: " + to_string(hp), "sweet purple.ttf", 40, 160.f, windowHeight - 50.f);
	Message release("<Press SPACE to release the ball>", "sweet purple.ttf", 40, 700.f, windowHeight - 50.f);
	Message gg("Congrats! You are the champion!", "sweet purple.ttf", 100, windowWidth / 2.f, windowHeight / 2.f);

	Noise loss("roblox.wav");
	Music win;
	if (!win.openFromFile("victory.ogg"))
	{
		cout << "Error loading music file!";
		return -1;
	}
	

	bool continueGame = false, isGameRunning = false;

	Clock clock;
	while (window.isOpen())
	{
		Event event;
		if (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				Interface::end();
				return false;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
		{
			window.close();
			Interface::end();
			return false;
		}		

		processCollision(paddle, ball, ballLvlSpeed);
		for (auto& block : blocks)
			processCollision(block, ball, points, ballLvlSpeed);
		score.text.setString("Score: " + to_string(points) + ". Nice try though.");
		blocks.erase(remove_if(blocks.begin(), blocks.end(), [](const Block& block) {return block.destroyed; }), blocks.end());

		if (!blocks.size())
		{
			win.play();
			while (true)
			{
				window.clear(Color::Black);
				window.draw(gg.text);
				window.draw(pressEsc2.text);
				window.display();
			//	glFinish();
				if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
				{
					window.close();
					Interface::end();
					return false;
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::Space) && !isGameRunning)
		{
			continueGame = true;
			isGameRunning = true;
		}

		if (!ball.update(paddle, continueGame, ballLvlSpeed))
		{
			--hp;
			loss.sound.play();
			if (!hp)
			{
				while (true)
				{
					window.clear(Color::Black);
					window.draw(score.text);
					window.draw(again.text);
					window.draw(pressEnter.text);
					window.draw(pressEsc1.text);
					window.display();
			//		glFinish();
					if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
					{
						window.close();
						Interface::end();
						return false;
					}
					if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
					{
						system("cls");
						Interface::restart();
						return true;
					}
				}
			}
			healpoints.text.setString("Healpoints: " + to_string(hp));
			window.clear(Color::Black);
			ball.shape.setPosition(windowWidth / 2.f, 730.f);
			paddle.shape.setPosition(windowWidth / 2.f, 750.f);
			ball.speed.x = 0.f;
			ball.speed.y = 0.f;
			isGameRunning = false;
			continue;
		}
		paddle.update(paddleLvlSpeed);

		window.clear(Color::Black);
		window.draw(ball.shape);
		window.draw(paddle.shape);
		for (auto& block:blocks)
			window.draw(block.shape);
		window.draw(healpoints.text);

		window.display();
	//	glFinish();
		Time time = clock.getElapsedTime();
		window.setTitle("MyArkanoid   FPS: " + to_string(1.0f / time.asSeconds()));
		clock.restart().asSeconds();
	}
}

void gameRunning()
{
	cout << " +======================================+\n";
	cout << " |  ¹  | ÂÛÁÅÐÈÒÅ ÓÐÎÂÅÍÜ ÑËÎÆÍÎÑÒÈ     |\n";
	cout << " +======================================+\n";
	cout << " |  1  |         Noob                   |\n";
	cout << " +======================================+\n";
	cout << " |  2  |         Amateur                |\n";
	cout << " +======================================+\n";
	cout << " |  3  |         Mlg Pro League         |\n";
	cout << " +======================================+\n";
	int answer = choose(1, 3);
	if (startGame(answer)) { gameRunning(); }
}

int main()
{
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	bool flag = true;
	while (flag)
	{
		cout << " +=============================+\n";
		cout << " |  ¹  | ÂÛÁÅÐÈÒÅ ÄÅÉÑÒÂÈÅ     |\n";
		cout << " +=============================+\n";
		cout << " |  1  |    Íà÷àòü èãðó.       |\n";
		cout << " +=============================+\n";
		cout << " |  0  |    Âûéòè.             |\n";
		cout << " +=============================+\n";
		if (int answer = choose(0, 1))
		{
			system("cls");
			gameRunning();
		}
		else flag = false;
	}
	return 0;
}