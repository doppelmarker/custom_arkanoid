#include "colorGenerator.h"

Color colorArray[6] = { Color::White, Color::Red, Color::Green, Color::Blue, Color::Magenta, Color::Cyan };

Color& colorGenerator()
{
	return colorArray[rand() % 5];
}
