#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "BulletHandler.h"
#include "Framerate.h"
#include "EnemyHandler.h"

static const float SCREENHEIGHT = 600.0f;
static const float SCREENWIDTH =  1200.0f;

void windowEventHandler(sf::RenderWindow& window, sf::View* view);

void Draw(sf::RenderWindow& window, sf::View& view, Player& player, Map& map, EnemyHandler& handler, sf::Text& text, BulletHandler& playerBulletHandler , BulletHandler& enemyBulletHandler);

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(static_cast<int>(SCREENWIDTH), static_cast<int>(SCREENHEIGHT)), "SFML Tutorial", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize, settings);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(SCREENWIDTH, SCREENHEIGHT));
	window.setFramerateLimit(144);
	Framerate framerate = Framerate();
	BulletHandler enemyBulletHandler = BulletHandler();
	BulletHandler playerBulletHandler = BulletHandler();
	Player player = Player(sf::Vector2f(0.0f, 0.0f), 135.f, 0, playerBulletHandler, window);
	EnemyHandler eHandler = EnemyHandler(enemyBulletHandler);
	eHandler.addEnemy(sf::Vector2f(-100.0f, -100.0f), 0.f, 0);
	eHandler.addEnemy(sf::Vector2f(-150.0f, -100.0f), 0.f, 1);
	eHandler.addEnemy(sf::Vector2f(-100.0f, -150.0f), 0.f, 1);
	eHandler.addEnemy(sf::Vector2f(-75.0f, -75.0f), 0.f, 2);
	Map map = Map();
	sf::FloatRect boundingBox = map.getBoundingBox();
	sf::Clock clock;


	float count = 0;
	while (window.isOpen())
	{
		framerate.timer();


		windowEventHandler(window, &view);
		enemyBulletHandler.update(window, boundingBox);
		enemyBulletHandler.hitDetection(&player);
		eHandler.update(&player);
		player.update();

		playerBulletHandler.update(window, boundingBox);
		playerBulletHandler.hitDetection(eHandler.getEnemyList());

		Draw(window, view, player, map, eHandler, framerate.text, playerBulletHandler, enemyBulletHandler);
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

void Draw(sf::RenderWindow& window, sf::View& view, Player& player, Map& map, EnemyHandler& handler, sf::Text& text, BulletHandler& playerBulletHandler, BulletHandler& enemyBulletHandler)
{
	view.setCenter(player.getPosition());
	window.setView(view);
	window.clear();
	map.draw(window);
	window.draw(player);
	playerBulletHandler.draw(window);
	handler.draw(window);
	enemyBulletHandler.draw(window);
	text.setPosition(window.mapPixelToCoords(sf::Vector2i(5, 5)));
	window.draw(text);
	window.display();
}


