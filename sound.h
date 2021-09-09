#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
using namespace sf;
using namespace std;

struct Noise
{
	SoundBuffer buf;
	Sound sound;
	Noise(string text)
	{
		if (!buf.loadFromFile(text))
		{
			cout << " Error loading sound file!";
			system("pause");
		}
		sound.setBuffer(buf);
	}
};

