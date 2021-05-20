#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "BulletHandler.h"
#include "Framerate.h"

static const float SCREENHEIGHT = 512.0f;
static const float SCREENWIDTH =  512.0f;

static const float M_PI = 3.14159265358979f;

void windowEventHandler(sf::RenderWindow& window, sf::View* view);

void Draw(sf::RenderWindow& window, sf::View& view, Player& player, Map& map, BulletHandler& handler, sf::Text& text);

int main()
{
	sf::RenderWindow window(sf::VideoMode(static_cast<int>(SCREENHEIGHT), static_cast<int>(SCREENWIDTH)), "SFML Tutorial", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(SCREENHEIGHT, SCREENHEIGHT));
	window.setFramerateLimit(144);
	Framerate framerate = Framerate();

	Player player = Player();
	BulletHandler handler = BulletHandler();
	//for (int i = 0; i < 5000; i++) {
	//	handler.addBullet(sf::Vector2f(0.0f, 0.0f), static_cast<float>(i));
	//	if (i % 100 == 0)printf("%i\n", i);
	//}
	Map map = Map();
	sf::FloatRect boundingBox = map.getBoundingBox();
	sf::Clock clock;


	float count = 0;
	while (window.isOpen())
	{
		framerate.timer();

		if (count < 10000) {
			handler.addBullet(sf::Vector2f(0.0f, 0.0f), count );
			count++;
		}
		else {
			handler.deleteBulletList();
			count = 0;
		}
		windowEventHandler(window, &view);
		handler.update(boundingBox);
		handler.hitDetection(&player);
		player.update(window);
		player.getBulletHandler()->update(boundingBox);

		Draw(window, view, player, map, handler, framerate.text);
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

void Draw(sf::RenderWindow& window, sf::View& view, Player& player, Map& map, BulletHandler& handler, sf::Text& text)
{
	view.setCenter(player.getPosition());
	window.setView(view);
	window.clear();
	map.draw(window);
	player.draw(window);
	player.getBulletHandler()->draw(window);
	handler.draw(window);
	text.setPosition(window.mapPixelToCoords(sf::Vector2i(5, 5)));
	window.draw(text);
	window.display();
}


