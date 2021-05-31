#include "Framerate.h"
#include <string>
#include <iomanip>
#include <sstream>

Framerate::Framerate()
{
	font.loadFromFile("Fonts/sansation.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::Red);
	text.setCharacterSize(24);
	text.setString("help");
}

Framerate::~Framerate()
{
}

void Framerate::timer()
{
	temp = clock.restart();
	time_3 = time_2;
	time_2 = time_1;
	time_1 = temp.asMicroseconds();
	average = (time_1 + time_2 + time_3) / 3;

	framerate = 1000000.0 / static_cast<double>(average);
	displayCounter += average;
	if (displayCounter > displayTime) {
		std::ostringstream streamObj;
		streamObj << std::fixed;
		streamObj << std::setprecision(1);
		streamObj << framerate;
		text.setString(streamObj.str());
		displayCounter -= displayTime;
	}
	
}

void Framerate::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(text);
}

void Framerate::setTextPos(sf::RenderWindow & window)
{
	text.setPosition(window.mapPixelToCoords(sf::Vector2i(5, 5)));
}
