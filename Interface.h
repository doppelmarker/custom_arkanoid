#pragma once
#include <iostream>
using namespace std;

class Interface
{
public:
	static void begin()
	{
		cout << "\n Игра началась!\n\n";
	}
	static void end()
	{
		system("cls");
		cout << "\n Игра завершилась!\n\n";
	}
	static void restart()
	{
		system("cls");
		cout << "\n Игра перезапущена!\n\n";
	}
};