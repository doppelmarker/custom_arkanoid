#pragma once
#include <iostream>
using namespace std;

class Interface
{
public:
	static void begin()
	{
		cout << "\n ���� ��������!\n\n";
	}
	static void end()
	{
		system("cls");
		cout << "\n ���� �����������!\n\n";
	}
	static void restart()
	{
		system("cls");
		cout << "\n ���� ������������!\n\n";
	}
};