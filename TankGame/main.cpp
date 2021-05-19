#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "BulletHandler.h"

static const float SCREENHEIGHT = 512.0f;
static const float SCREENWIDTH =  512.0f;

static const float M_PI = 3.14159265358979f;

void windowEventHandler(sf::RenderWindow& window, sf::View* view);

void Draw(sf::RenderWindow& window, sf::View& view, Player& player, Map& map, BulletHandler& handler);

int main()
{
	sf::RenderWindow window(sf::VideoMode(static_cast<int>(SCREENHEIGHT), static_cast<int>(SCREENWIDTH)), "SFML Tutorial", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(SCREENHEIGHT, SCREENHEIGHT));

	Player player = Player();
	BulletHandler handler = BulletHandler();
	Map map = Map();

	handler.addBullet(sf::Vector2f(0.0f, 0.0f), 0.f);

	while (window.isOpen())
	{
		windowEventHandler(window, &view);
		handler.update();
		player.update(window);

		Draw(window, view, player, map, handler);
	}

	return 0;
}

void windowEventHandler(sf::RenderWindow& window, sf::View* view) {
	sf::Event evnt;
	while (window.pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::Resized:
			view->setSize(static_cast<float>(evnt.size.width), static_cast<float>(evnt.size.height));
			break;
		case sf::Event::TextEntered:
			//do nothing
			break;
		default:
			break;
		}
	}
}

void Draw(sf::RenderWindow& window, sf::View& view, Player& player, Map& map, BulletHandler& handler)
{
	view.setCenter(player.getPosition());
	window.setView(view);
	window.clear();
	map.draw(window);
	player.draw(window);
	handler.draw(window);
	window.display();
}


