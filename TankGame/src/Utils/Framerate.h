#pragma once
#include <SFML/Graphics.hpp>


class Framerate : public sf::Drawable
{
	public:
		sf::Text text;
		sf::Clock clock;
		Framerate();
		~Framerate();

		void timer();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void setTextPos(sf::RenderWindow & window);

	private:

		sf::Font font;
		sf::Time temp;
		sf::Int64 displayCounter = 0;
		sf::Int64 displayTime = 100000;
		sf::Int64 time_1 = 1000;
		sf::Int64 time_2 = 1000;
		sf::Int64 time_3 = 1000;
		sf::Int64 average = 1000;
		double framerate = 144.0;
};

