#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

struct Message
{
	Text text;
	Font font;
	FloatRect textRect;
	Message(string text, string fontName, unsigned int size, float x, float y)
	{
		if (!font.loadFromFile(fontName))
		{
			cout << "Error loading font file." << endl;
			system("pause");
		}
		this->text.setFont(font);

		this->text.setString(text);
		this->text.setCharacterSize(size);

		textRect = this->text.getLocalBounds();
		this->text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
		this->text.setPosition({ x, y });
	}
};
