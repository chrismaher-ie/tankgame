#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

static const float SCREENHEIGHT = 512.0f;
static const float SCREENWIDTH =  512.0f;

# define M_PI           3.14159265358979f;

int main()
{
	sf::RenderWindow window(sf::VideoMode(static_cast<int>(SCREENHEIGHT), static_cast<int>(SCREENWIDTH)), "SFML Tutorial", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(SCREENHEIGHT, SCREENHEIGHT));

	Player player = Player();

	sf::RectangleShape map(sf::Vector2f(1200.f, 2000.f));
	map.setPosition(0.f, 0.f);
	map.setOrigin(600.0f, 1200.0f);

	sf::Texture mapTexture;
	mapTexture.loadFromFile("Textures/road.jpg");
	map.setTexture(&mapTexture);

	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				view.setSize(evnt.size.width, evnt.size.height);
				break;
			case sf::Event::TextEntered:
				//do nothing
				break;
			default:
				break;
			}
		}
		
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

		player.update(worldPos);

		view.setCenter(player.getPosition());
		window.setView(view);
		window.clear();
		window.draw(map);
		player.draw(window);
		window.display();
	}

	return 0;
}