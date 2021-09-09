#include "DataValidation.h"

bool isNumberNumeric()
{
	if (cin.get() == '\n') return true;
	else
	{
		cin.clear();
		cin.ignore(256, '\n');
		return false;
	}
}

bool isNumberRangeCorrect(int number, int left_range, int right_range)
{
	if ((number >= left_range) && (number <= right_range)) return true;
	else return false;
}

int choose(int left_range, int right_range)
{
	int number;
	while (true)
	{
		cout << "  Ваш ввод: ";
		cin >> number;
		if (isNumberNumeric() && isNumberRangeCorrect(number, left_range, right_range))
			return number;
		else
		{
			cout << "\n Исключение: Введены некорректные данные!\n";
		}
	}
}